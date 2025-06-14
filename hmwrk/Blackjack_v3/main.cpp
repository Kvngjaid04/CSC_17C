/*
 * Author: Ireoluwa 
 * Created: October 29, 2024
 * Modified for CSC_17_C 
 * Purpose: Blackjack Game
 */ 

// System Libraries 
#include <iostream> 
#include <cstdlib> 
#include <ctime> 
#include <vector>
#include <list>
#include <map>
#include <set>
#include <stack>
#include <queue>

// User Libraries 
#include "Card.h"
#include "Save.h"
#include "Deck.h"
#include "Play.h"
#include "Menu.h"
#include "UserMgr.h"
#include "AVL.h"
//#include "Graph.h"
#include "Hash.h"

using namespace std; 

// Function prototypes for main game flow
void setup(Save&, string&, map<int, int>&, set<Card>&, 
           queue<string>&, AVL&);
void round(vector<Card>&, int&, list<Card>&, list<Card>&, 
           int&, int&, Save&, string&, map<int, int>&, 
           set<Card>&, queue<string>&, stack<int>&, AVL&);
bool endRnd(Save&, list<Card>&, list<Card>&, int&, map<int, int>&, 
            set<Card>&, queue<string>&);
void reset(list<Card>&, list<Card>&, int&, queue<string>&);
bool askRul(bool&);

// Main execution
int main(int argc, char** argv) { 
    srand(time(0)); 
    
    // Game containers
    vector<Card> deck(SIZE);
    list<Card> pHand;
    list<Card> dHand;
    int nCards = SIZE;
    int pSum = 0, dSum = 0;
    Save user;
    string fname;
    
    // STL containers for stats
    map<int, int> cStat;
    set<Card> uCard;
    queue<string> aHist;
    stack<int> betHist;
    
    // Game systems
    AVL strat;
    
    // Initialize systems
    strat.bldStr();
    
    // Setup game
    setup(user, fname, cStat, uCard, aHist, strat);
    
    // Main game loop
    do {
        round(deck, nCards, pHand, dHand, pSum, dSum, 
              user, fname, cStat, uCard, aHist, betHist, strat);
    } while (endRnd(user, pHand, dHand, nCards, cStat, 
                    uCard, aHist));
    
    return 0; 
}

// Game setup and initialization
void setup(Save& user, string& fname, map<int, int>& cStat, 
           set<Card>& uCard, queue<string>& aHist, AVL& strat) {
    cout << "\n WELCOME TO BLACKJACK \n";
       
    user = selPlyr();  
    fname = string(user.name);
}

// Show rules once at start
bool askRul(bool& shown) {
    if (shown) return false;
    
    string input;
    
    while (true) {
        cout << "See game rules? (y/n): ";
        
        cin >> input;
        
        if (input.length() == 1) {
            char shwRles = tolower(input[0]);
            if (shwRles == 'y') {
                clrBuf();
                help();
                shown = true;
                return true;
            } else if (shwRles == 'n') {
                clrBuf();
                shown = true;
                return false;
            }
        }
        cout << "Please enter 'y' or 'n'.\n";
    }
}

// Play a single round
void round(vector<Card>& deck, int& nCards, list<Card>& pHand,list<Card>& dHand,
          int& pSum, int& dSum, Save& user, string& fname, map<int, int>& cStat, 
        set<Card>& uCard,queue<string>& aHist, stack<int>& betHist, AVL& strat){
    
    // Setup new round
    init(deck, nCards);
    shuf(deck);
    
    static bool shown = false;
    askRul(shown);
    
    // Betting phase
    int bet = getBet(user);
    betHist.push(bet);
    
    // Clear hands
    pHand.clear();
    dHand.clear();
    
    // Deal cards
    deal(deck, pHand, dHand);
    show(pHand, dHand, deck);
    
    aHist.push("Initial deal");
    pTurn(deck, pHand, pSum, user, bet, strat);
    aHist.push("Player turn complete");
    
    // Dealer turn if player didn't bust
    if (pSum <= 21) { 
        dTurn(deck, dHand, dSum);
        aHist.push("Dealer turn complete");
    } 
    
    // Handle outcome
    result(user, bet, pSum, dSum);
    save(user, fname);
    updPlyr(user);
    
    // Update card statistics using Card objects
    for (auto it = pHand.begin(); it != pHand.end(); ++it) {
        int val = it->val > 10 ? 10 : it->val;
        cStat[val]++;
        uCard.insert(*it);
    }
}

// Reset for new round
void reset(list<Card>& pHand, list<Card>& dHand, int& nCards, 
           queue<string>& aHist) {
    pHand.clear();
    dHand.clear();
    nCards = SIZE;
    
    while (!aHist.empty()) {
        aHist.pop();
    }
}

// End round and check continue
bool endRnd(Save& user, list<Card>& pHand, list<Card>& dHand, int& nCards,
        map<int, int>& cStat, set<Card>& uCard,queue<string>& aHist) {
    
    if (!canPlay(user)) return false;
    
    char choice = getMenu(cStat, uCard, aHist, user);
    
    if (choice == 'n') {
        cout << "Thanks for playing! Goodbye!\n";
        return false;
    }
    
    reset(pHand, dHand, nCards, aHist);
    return true;
}