/*
 *  Author: Ireoluwa 
 * Created on October 29, 2024, 12:19 PM 
 * modified for csc_17_c 
 * Date:    May 2, 2024 
 * Purpose: blackjack 
 */ 

//System Libraries 
#include <iostream> 
#include <cstdlib> 
#include <ctime> 

// STL Containers
#include <vector>     // Sequence container
#include <list>       // Sequence container
#include <map>        // Associative container
#include <set>        // Associative container
#include <stack>      // Container adaptor
#include <queue>      // Container adaptor

// User Libraries 
#include "Card.h"
#include "Save.h"
#include "Deck.h"
#include "Gameplay.h"
#include "Menu.h"
#include "UserMgr.h"
#include "AVLTree.h"
#include "Graph.h"
#include "PlyrHsh.h"

using namespace std; 

// Function prototypes for main game flow
void setup(Save&, string&, map<int, int>&, set<Card>&, 
           queue<string>&, AVLTree&, Graph&);
void round(vector<Card>&, int&, list<int>&, list<int>&, 
           int&, int&, Save&, string&, map<int, int>&, 
           set<Card>&, queue<string>&, stack<int>&, AVLTree&, Graph&);
bool endRnd(Save&, list<int>&, list<int>&, int&, map<int, int>&, 
            set<Card>&, queue<string>&, Graph&);
void reset(list<int>&, list<int>&, int&, queue<string>&);
bool askRul(bool&);

//Execution Begins here 
int main(int argc, char** argv) { 
    
    //Setting the random number seed 
    srand(time(0)); 
    
    //Declaring Variables using STL containers
    vector<Card> deck(SIZE);            // Create deck using vector
    list<int> pHand;                    // Player's hand using list
    list<int> dHand;                    // Dealer's hand using list
    int nCards = SIZE;                  // Number of cards in deck 
    int pSum = 0, dSum = 0;             // Player and dealer totals 
    Save user;                          // User profile data 
    string fname;                       // Save file name 
    
    // STL containers for game statistics and tracking
    map<int, int> cStat;                // Maps card value to count
    set<Card> uCard;                    // Tracks unique cards
    queue<string> aHist;                // Records game actions
    stack<int> betHist;                 // Records betting history
    
    // Game systems
    AVLTree strategy;                   // Strategy tree
    Graph cardGraph;                    // Card relationship graph
    
    // Initialize game systems
    strategy.bldStrt();                 // Build strategy tree
    initGph(cardGraph);                 // Initialize graph
    
    // Initialize the game
    setup(user, fname, cStat, uCard, aHist, strategy, cardGraph);
    
    // Main game loop
    do {
        round(deck, nCards, pHand, dHand, pSum, dSum, 
              user, fname, cStat, uCard, aHist, betHist, strategy, cardGraph);
    } while (endRnd(user, pHand, dHand, nCards, cStat, 
                    uCard, aHist, cardGraph));
    
    return 0; 
}

// Game setup and initialization
void setup(Save& user, string& fname, map<int, int>& cStat, set<Card>& uCard, 
        queue<string>& AcnHtry, AVLTree& strategy, Graph& cardGraph) {
    // Display welcome message
    cout << "\n WELCOME TO BLACKJACK \n";
       
    // Use hash-based player selection
    user = selplyr();  
    fname = string(user.name);  // Set filename from selected user
    
    // Add some card relationships to the graph
    addEdge(cardGraph, 1, 10, 2);  // Ace and 10 are closely related
    addEdge(cardGraph, 2, 3, 1);   // Sequential cards
    addEdge(cardGraph, 3, 4, 1);
    addEdge(cardGraph, 4, 5, 1);
    addEdge(cardGraph, 5, 6, 1);
    addEdge(cardGraph, 6, 7, 1);
    addEdge(cardGraph, 7, 8, 1);
    addEdge(cardGraph, 8, 9, 1);
    addEdge(cardGraph, 9, 10, 1);
    addEdge(cardGraph, 10, 11, 2); // 10-value cards
    addEdge(cardGraph, 10, 12, 2);
    addEdge(cardGraph, 10, 13, 2);
}

// Show rules once at start if requested
bool askRul(bool& rlsShwn) {
    if (rlsShwn) return false;
    
    string input;
    
    while (true) {
        cout << "Would you like to see the game rules? (y/n): ";
        
        getline(cin, input);
        
        if (input.length() == 1) {
            char shwRles = tolower(input[0]);
            if (shwRles == 'y') {
                clrBuf();
                help();
                rlsShwn = true;
                return true;
            } else if (shwRles == 'n') {
                clrBuf();
                rlsShwn = true;
                return false;
            }
        }
        cout << "Please enter 'y' for yes or 'n' for no.\n";
    }
}

// Play a single round of blackjack
void round(vector<Card>& deck, int& nCards, list<int>& PlyrHnd, 
           list<int>& DlrHand, int& pSum, int& dSum, Save& user, 
           string& fname, map<int, int>& cStat, set<Card>& uCard,
           queue<string>& AcnHtry, stack<int>& btHstry, AVLTree& strategy,
                    Graph& cardGraph) {
    
    // Setup new round
    init(deck, nCards);             // Initialize deck 
    shuf(deck);                     // Shuffle deck using STL algorithm
    
    // Static variable to track if rules have been shown
    static bool rlsShwn = false;
    
    // Ask if player wants to see rules only on first round
    askRul(rlsShwn);
    
    // Betting phase
    int bet = getBet(user);        // Get player's bet
    btHstry.push(bet);           // Record bet in history
    
    // Clear hands using STL container methods
    PlyrHnd.clear();             // O(1) operation for list
    DlrHand.clear();             // O(1) operation for list
    
    // Initial deal phase
    deal(deck, PlyrHnd, DlrHand);  // Deal initial cards 
    show(PlyrHnd, DlrHand, deck);  // Show initial hands 
    
    // Record action in history
    AcnHtry.push("Initial deal");
    pTurn(deck, PlyrHnd, pSum, user, bet, strategy, cardGraph); // Player's turn 
    // Record action in history
    AcnHtry.push("Player turn complete");
    // Dealer's turn if player didn't bust 
    if (pSum <= 21) { 
        dTurn(deck, DlrHand, dSum);
        AcnHtry.push("Dealer turn complete");
    } 
    
    // Outcome determination and statistics update
    result(user, bet, pSum, dSum);         // Handle outcome 
    save(user, fname);                      // Save game state 
    udtplyr(user);                          //updates hash table
    
    // Update card statistics
    for (auto it = PlyrHnd.begin(); it != PlyrHnd.end(); ++it) {
        cStat[*it]++;
        // Create a Card struct to add to the set
        Card c;
        c.val = *it;
        c.suit = HEART; // HEART as a placeholder for uniqueness tracking
        uCard.insert(c);
    }
}

// Reset for new round
void reset(list<int>& pHand, list<int>& dHand, int& nCards, 
           queue<string>& aHist) {
    pHand.clear();
    dHand.clear();
    nCards = SIZE;
    
    while (!aHist.empty()) {
        aHist.pop();
    }
}

// End of round and check for continue
bool endRnd(Save& user, list<int>& pHand, list<int>& dHand, 
            int& nCards, map<int, int>& cStat, set<Card>& uCard,
            queue<string>& aHist, Graph& cardGph) {
    
    if (!canPlay(user)) return false;
    
    char choice = getMenu(cStat, uCard, aHist, cardGph, user);
    
    if (choice == 'n') {
        cout << "Thanks for playing! Goodbye!\n";
        return false;
    }
    
    reset(pHand, dHand, nCards, aHist);
    return true;
}