/*
 *  Author: Ireoluwa 
* Created on October 29, 2024, 12:19 PM 
* modified for csc_17_c 
* Date:    May 2, 2024 
* Purpose: blackjack 
*/ 

//System Libraries 
#include <iostream> 
#include <iomanip> 
#include <cstdlib> 
#include <ctime> 
#include <fstream> 
#include <string> 
#include <cctype> 
#include <cstring> 

// STL Containers
#include <vector>     // Sequence container
#include <list>       // Sequence container
#include <map>        // Associative container
#include <set>        // Associative container
#include <stack>      // Container adaptor
#include <queue>      // Container adaptor

// STL Algorithms
#include <algorithm>  // For algorithms like for_each, find, sort.
#include <functional> // For function objects

using namespace std; 

//User Libraries 

 //Card Structure
 //Represents a playing card with a suit and numerical value.
 //Includes operator overloads to work with STL containers.
struct Card { 
    char suit; 
    int val;
    
    // Comparison operator for set/map - sorts by suit then value
    bool operator<(const Card& other) const {
        if (suit != other.suit)
            return suit < other.suit;
        return val < other.val;
    }
    
    //Equality operator for set - cards are equal if suit and value match
    bool operator==(const Card& other) const {
        return (suit == other.suit && val == other.val);
    }
}; 

  //Save Structure
  //Stores player profile information for save/load functionality.
  //Includes data about performance and game statistics.
struct Save { 
    char name[30]; 
    int wins; 
    int games; 
    int cash; 
    
    // Comparison operator for map - sorts by player name
    bool operator<(const Save& other) const {
        return strcmp(name, other.name) < 0;
    }
}; 

//Global Constants 
 //Enumeration for card suits - used for organization
enum Suit {HEART, DIAM, SPADE, CLUB}; 
const int SIZE = 52;                // Deck size 
stack<int> btHstry;           //to track betting history


//Function Prototypes 
void init(vector<Card>&, int&);        // Initialize deck using vector
void shuf(vector<Card>&);              // Shuffle deck using random_shuffle
int draw(vector<Card>&);               // Draw card using STL containers
void pCard(int, char);                 // Print card 
bool load(Save&, string);              // Load game 
void save(Save, string);               // Save game 
int sumHand(const list<int>&);         // Sum hand using list iterator
void showHlp();                        // Show help/rules function 
bool hit();                            // Ask hit/stand 
bool vName(string);                    // Validate name 
void clrBuf();                         // Clear buffer 
string fllSuit(int);                   // Get full name of suit 
string cardVal(int);                   // Get card value as string 
void inzeGme(Save&, string&);          // Initialize new or load existing game 
bool hdSVFLd(Save&, string&);          // Load user save file 
void crtNwUr(Save&, string&);          // Create new user profile 
void dpUsrSt(Save&);                   // Display user stats 
int gtBtAnt(const Save&);              // Get bet amount from player 
void dlInCrd(vector<Card>&, list<int>&, list<int>&); // Deal initial cards 
void dspInDl(const list<int>&, const list<int>&, const vector<Card>&); // cards 
void plyPrTn(vector<Card>&, list<int>&, int&);       // Player's turn 
void plyDrTn(vector<Card>&, list<int>&, int&);       // Dealer's turn 
void hndlGOt(Save&, int, int, int);                 // Handle game outcome 
bool chcGmCe(const Save&);                       // Check if player can continue 
bool plyARnd();                             // Ask if player wants to play again
void pntCStt(const map<int, int>&);    // Print card statistics using map

// function prototypes for main function splitting
void gmeSetp(Save&, string&, map<int, int>&, set<Card>&, queue<string>&);
void plyRund(vector<Card>&, int&, list<int>&, list<int>&, int&, int&, Save&,
               string&,map<int, int>&, set<Card>&, queue<string>&, stack<int>&);
bool endRund(Save&, list<int>&, list<int>&, int&, map<int, int>&, set<Card>&, 
              queue<string>&);

//Execution Begins here 
int main(int argc, char** argv) { 
    
    //Setting the random number seed 
    srand(time(0)); 
    
    //Declaring Variables using STL containers
    vector<Card> deck(SIZE);            // Create deck using vector
    list<int> PlyrHnd;               // Player's hand using list
    list<int> DlrHand;               // Dealer's hand using list
    int nCards = SIZE;                  // Number of cards in deck 
    int pSum = 0, dSum = 0;             // Player and dealer totals 
    Save user;                          // User profile data 
    string fname;                       // Save file name 
    
    // STL containers for game statistics and tracking
    map<int, int> CrdStat;            // Maps card value to count
    set<Card> UnqCard;              // Tracks unique cards
    queue<string> AcnHtry;        // Records game actions
    stack<int> btHstry;              // Records betting history
    
    // Initialize the game
    gmeSetp(user, fname, CrdStat, UnqCard, AcnHtry);
    
    // Main game loop
    do {
        plyRund(deck, nCards, PlyrHnd, DlrHand, pSum, dSum, 
                  user, fname, CrdStat, UnqCard, AcnHtry, 
                    btHstry);
    } while (endRund(user, PlyrHnd, DlrHand, nCards, CrdStat, 
                      UnqCard, AcnHtry));
    
    return 0; 
}

// Print card statistics using map iterator
//Displays frequency statistics for each card value drawn during the game.
//Uses the STL for_each algorithm with a lambda function to process map entries.
void pntCStt(const map<int, int>& stats) {
    cout << "\nCard Statistics:\n";
    cout << "----------------\n";
    
    // Use for_each STL algorithm with lambda
    for_each(stats.begin(), stats.end(), [](const pair<int, int>& item) {
        cout << "Card Value " << cardVal(item.first) << ": drawn " << 
                item.second << " times\n";
    });
}

// Function to initialize a new game or load a previous game 
//First function called at game start - manages player profile.
// Either loads existing save file or creates a new player profile.
void inzeGme(Save& user, string& fname) { 
    char resp; 
    cout << "Want to load a save file? (y/n): "; 
    cin >> resp; 
    clrBuf(); 
     
    if (resp == 'y') { 
        if (hdSVFLd(user, fname)) { 
            dpUsrSt(user); 
        } else { 
            crtNwUr(user, fname); 
        } 
    } else { 
        crtNwUr(user, fname); 
    } 
} 

// Function to handle loading of save file if it exists 
//prompts for username and attempts to load save file.
//Validates username using count_if algorithm through vName function.
bool hdSVFLd(Save& user, string& fname) { 
    do { 
        cout << "Enter username to load: "; 
        getline(cin, fname); 
    } while (!vName(fname)); 
    
    if (load(user, fname)) { 
        return true; 
    } 
    
    cout << "Save file not found.\n"; 
    return false; 
} 

// Function to create a new user profile 
//sets up a new player profile with starting values.
//Validates username using STL count_if algorithm.
void crtNwUr(Save& user, string& fname) { 
    do { 
        cout << "Enter new username (3-30 chars, alphanumeric): "; 
        getline(cin, fname); 
    } while (!vName(fname)); 
    
    strncpy(user.name, fname.c_str(), 29); 
    user.name[29] = '\0'; 
    user.wins = 0; 
    user.games = 0; 
    user.cash = 1000; 
    
    cout << "\nWelcome " << user.name << "!\n"; 
    cout << "Starting cash: $" << user.cash << "\n\n"; 
} 

// Function to display user stats 
//Shows the player's current statistics from their profile.
//Handles edge case of player having no money left.
void dpUsrSt(Save& user) {  
    cout << "\nWelcome back " << user.name << "!\n"; 
    cout << "Stats from last game:\n"; 
    cout << "Wins: " << setw(5) << user.wins << endl; 
    cout << "Games: " << setw(4) <<  user.games << endl; 
    cout << "Cash: $" << user.cash << endl << endl; 
    
    if (user.cash <= 0) { 
        cout << "You have no money left in saved game!\n"; 
        cout << "Starting new game with fresh bankroll.\n\n"; 
        user.cash = 1000;  // Reset cash to 1000 
    } 
} 

// Function to get the player's betting amount 
//Prompts player for bet amount and validates it.
// Ensures bet is a number within valid range
int gtBtAnt(const Save& user) { 
    int bet; 
    do { 
        cout << "Cash: $" << user.cash << endl; 
        cout << "Bet amount: $"; 
        if (!(cin >> bet)) { 
            cout << "Invalid bet. Enter a number.\n"; 
            clrBuf(); 
            bet = 0; 
            continue; 
        } 
        
        if (bet > user.cash) cout << "Can't bet more than you have!\n"; 
        if (bet < 1) cout << "Minimum bet is $1\n"; 
    } while (bet > user.cash || bet < 1); 
    
    clrBuf(); 
    return bet; 
} 

// Function to deal initial cards using STL containers
//Deals two cards each to player and dealer.
//Only shows dealer's first card (up card).
// Uses list container push_back() to add cards to hands.
void dlInCrd(vector<Card>& deck, list<int>& PlyrHnd, list<int>& DlrHand) { 
    cout << "\nYour cards:\n"; 
    
    // Deal two cards to player
    for (int i = 0; i < 2; i++) {
        int card = draw(deck);
        PlyrHnd.push_back(card);
        pCard(card, deck.back().suit);
    }
    
    // Deal two cards to dealer
    for (int i = 0; i < 2; i++) {
        int card = draw(deck);
        DlrHand.push_back(card);
        if (i == 0) {
            cout << "\nDealer's up card:\n";
            pCard(card, deck.back().suit);
        }
    }
}

// Function to display the initial cards of player and dealer 
//Shows the initial state of the game after cards are dealt.
//Displays dealer's visible total from up card.
// Uses STL iterator to access first element of list.
void dspInDl(const list<int>& PlyrHnd, const list<int>& DlrHand, 
        const vector<Card>& deck) {
    // Use find algorithm to get the first card
    auto it = DlrHand.begin();
    if (it != DlrHand.end()) {
        cout << "Dealer's visible total: " << *it << endl;
    }
} 

// Function to play the player's turn using STL list 
//Manages the player's decisions to hit or stand.
//Uses the sumHand function with STL for_each to calculate hand total.
//Continues until player stands, busts, or reaches 21.
void plyPrTn(vector<Card>& deck, list<int>& hand, int& pSum) { 
    pSum = sumHand(hand);
    cout << "\nYour total: " << pSum << endl; 
    
    while (pSum < 21 && hit()) { 
        int card = draw(deck);
        hand.push_back(card);
        
        cout << "\nYou drew:\n"; 
        pCard(card, deck.back().suit); 
        
        pSum = sumHand(hand);
        cout << "\nYour total: " << pSum << endl; 
    } 
} 

// Function to play the dealer's turn using STL list
//Automatically plays the dealer's hand according to standard rules.
//Dealer must hit until reaching a total of 17 or higher.
//Uses STL iterator to traverse the dealer's hand list.
void plyDrTn(vector<Card>& deck, list<int>& hand, int& dSum) { 
    dSum = sumHand(hand);
    
    cout << "\nDealer shows hidden card:\n"; 
    
    // Using STL iterator to traverse the list
    for (auto it = hand.begin(); it != hand.end(); ++it) {
        pCard(*it, deck.back().suit);
    }
    
    cout << "Dealer total: " << dSum << endl; 
    
    while (dSum < 17) { 
        int card = draw(deck);
        hand.push_back(card);
        
        cout << "\nDealer drew:\n"; 
        pCard(card, deck.back().suit); 
        
        dSum = sumHand(hand);
        cout << "Dealer total: " << dSum << endl; 
    } 
    
    cout << "\nFinal dealer total: " << dSum << endl; 
} 

// Function to handle the game outcome and update the player's stats 
//Determines the winner and updates player statistics.
//Applies standard Blackjack rules for win/loss/push conditions.
//Updates player's cash balance based on bet and outcome.
void hndlGOt(Save& user, int bet, int pSum, int dSum) { 
    cout << "\nFinal totals:\n"; 
    cout << "Your total: " << pSum << endl; 
    
    if (pSum <= 21) cout << "Dealer total: " << dSum << endl; 
    
    user.games++; 
    
    if (pSum > 21) { 
        cout << "\nBust! You lose $" << bet << endl; 
        user.cash -= bet; 
    } 
    else if (dSum > 21) { 
        cout << "\nDealer bust! You win $" << bet << endl; 
        user.cash += bet; 
        user.wins++; 
    } 
    else if (pSum > dSum) { 
        cout << "\nYou win $" << bet << endl; 
        user.cash += bet; 
        user.wins++; 
    } 
    else if (pSum < dSum) { 
        cout << "\nYou lose $" << bet << endl; 
        user.cash -= bet; 
    } 
    else cout << "\nPush!\n"; 
    
    cout << "Current cash: $" << user.cash << endl; 
} 

// Function to check if the player can continue the game 
//function to check if balance is positive.
bool chcGmCe(const Save& user) { 
    if (user.cash <= 0) { 
        cout << "\nYou're broke! Game over!\n"; 
        return false; 
    } 
    return true; 
} 

// Play Another Round
//Asks player if they want to play another round of Blackjack.
//Handles various commands including help, stats, and quit.
//Uses STL transform algorithm to convert input to lowercase.
bool plyARnd() { 
    string input;
    char cont; 
    do { 
        cout << "\nPlay again? (y/n) or type 'help' for rules: "; 
        cin >> input;
        
        // Convert to lowercase
        transform(input.begin(), input.end(), input.begin(), ::tolower);
        
        if (input == "help") {
            clrBuf();
            showHlp();
            continue;
        } else if (input == "stats") {
            cout << "\nGame Statistics:\n";
            cout << "Total games played: " << btHstry.size() << "\n";
            // Could display more complex stats here
            continue;
        } else if (input == "quit") {
            cout << "Exiting the game. Thanks for playing!" << endl;
            exit(0);
        } else if (input.length() == 1) {
            cont = input[0];
        } else {
            cont = 'x'; // Invalid
        }
        
        if (cont != 'y' && cont != 'n') 
            cout << "Please enter y or n\n"; 
    } while (cont != 'y' && cont != 'n'); 
    
    clrBuf(); 
    
    if (cont == 'n') { 
        cout << "Exiting the game. Goodbye!" << endl; 
        exit(0); 
    }
    
    return true;
} 

//  Validate Name
// Validates username meets requirements:
// Between 3-30 characters
// Only alphanumeric and underscore characters
// Uses STL count_if algorithm with lambda to check invalid characters.
bool vName(string name) { 
    if (name.length() < 3 || name.length() > 30) { 
        cout << "Username must be 3-30 characters\n"; 
        return false; 
    } 
    
    // Use STL algorithm count_if with lambda
    int InvdChr = count_if(name.begin(), name.end(), [](char c) {
        return !isalnum(c) && c != '_';
    });
    
    if (InvdChr > 0) {
        cout << "Username can only contain letters, numbers, and underscore\n"; 
        return false;
    }
    
    return true; 
} 

// Function to clear the input buffer 
void clrBuf() { 
    cin.clear(); 
    cin.ignore(1000, '\n'); 
} 

// Function to load a saved game 
bool load(Save& user, string name) { 
    string fname = name + ".dat"; 
    ifstream in(fname, ios::binary | ios::in); 
    
    if (!in) return false; 
    
    in.seekg(0, ios::end);
    long fileSize = in.tellg(); 
    in.seekg(0, ios::beg); 
    in.read(reinterpret_cast<char*>(&user), sizeof(Save)); 
    in.close(); 
    
    return true; 
} 

// Function to save the current game state 
void save(Save user, string name) { 
    string fname = name + ".dat"; 
    ofstream out(fname, ios::binary | ios::out); 
    out.write(reinterpret_cast<char*>(&user), sizeof(Save)); 
    out.close(); 
} 

// Function to initialize the deck of cards using vector
void init(vector<Card>& deck, int& size) { 
    // Using STL algorithm generate
    generate(deck.begin(), deck.end(), [&]() {
        static int i = 0;
        Card c;
        c.val = i % 13 + 1;
        c.suit = static_cast<Suit>(i / 13);
        i++;
        return c;
    });
} 

// Function to shuffle the deck of cards using STL algorithm
void shuf(vector<Card>& deck) { 
    // Using random_shuffle algorithm
    random_shuffle(deck.begin(), deck.end());
} 

// Function to draw a card from the deck using vector
int draw(vector<Card>& deck) { 
    int val = deck.back().val > 10 ? 10 : deck.back().val;
    deck.pop_back();
    return val;
} 

// Function to return the full name of a suit
string fllSuit(int s) { 
    switch (s) { 
        case HEART: return "Hearts"; 
        case DIAM: return "Diamonds"; 
        case SPADE: return "Spades"; 
        default: return "Clubs"; 
    } 
} 

// Function to return the full name of a card's value
string cardVal(int val) { 
    const map<int, string> vluNmes = {
        {1, "Ace"},
        {2, "Two"},
        {3, "Three"},
        {4, "Four"},
        {5, "Five"},
        {6, "Six"},
        {7, "Seven"},
        {8, "Eight"},
        {9, "Nine"},
        {10, "Ten"},
        {11, "Jack"},
        {12, "Queen"},
        {13, "King"}
    };
    
    // Use find algorithm and map container
    auto it = vluNmes.find(val);
    if (it != vluNmes.end()) {
        return it->second;
    }
    
    return "Unknown";
} 

// Function to print a single card's value and suit 
void pCard(int val, char suit) { 
    cout << cardVal(val) << " of " << fllSuit(suit) << endl; 
} 

// Function to calculate the sum of a hand using list iterator
int sumHand(const list<int>& hand) { 
    int total = 0; 
    int aces = 0;
    
    // Using STL for_each algorithm with lambda
    for_each(hand.begin(), hand.end(), [&](int card) {
        if (card == 1) {
            aces++;
            total += 11;
        } else {
            total += card;
        }
    });
    
    // Adjust for aces if needed
    while (total > 21 && aces > 0) {
        total -= 10;
        aces--;
    }
    
    return total;
} 

// Function to prompt the player for hit or stand 
bool hit() {
    string input;
    char ch;
    do {
        cout << "\nHit or Stand? (h/s) or type 'help' for rules: ";
        cin >> input;
        
        // Convert to lowercase
        transform(input.begin(), input.end(), input.begin(), ::tolower);
        
        if (input == "help") {
            clrBuf();
            showHlp();
            continue;
        } else if (input.length() == 1) {
            ch = input[0];
        } else {
            ch = 'x'; // invalid
        }
        
        if (ch != 'h' && ch != 's')
            cout << "Please enter 'h' for hit or 's' for stand\n";
    } while (ch != 'h' && ch != 's');
    
    clrBuf();
    return ch == 'h';
}

// Show help/rules
void showHlp() {
    cout << "\n===== BLACKJACK RULES =====\n";
    cout << "1. The goal is to get a hand value closer to 21 than the dealer "
            "without going over.\n";
    cout << "2. Card values: Aces count as either 1 or 11, Jack/Queen/King all "
            "count as 10, and number cards 2 through 10 count as their number "
            "shown.\n";
    cout << "3. Both player and dealer receive two cards; one dealer card"
            " is hidden.\n";
    cout << "4. Player goes first and can 'hit' (take cards) or 'stand' "
            "(keep current hand).\n";
    cout << "5. If player's hand exceeds 21, they 'bust' and lose.\n";
    cout << "6. Dealer must hit until their hand totals 17 or higher.\n";
    cout << "7. If dealer busts, player wins. Otherwise, highest hand wins.\n";
    cout << "8. Blackjack (Ace + 10-value card) pays 3:2.\n";
    cout << "9. Equal values result in a 'push' (tie).\n\n";
    
    cout << "===== GAME COMMANDS =====\n";
    cout << "h - Hit (take another card)\n";
    cout << "s - Stand (end your turn)\n";
    cout << "d - Double Down (double bet, take exactly one more card)\n";
    cout << "help - Display this help screen\n";
    cout << "quit - Exit the game\n";
    cout << "stats - Show detailed statistics\n";
    cout << "options - Change game options\n\n";
    
    cout << "Press Enter to continue..." << endl;
    cin.ignore(1000, '\n');
}

// Game setup and initialization
void gmeSetp(Save& user, string& fname, map<int, int>& CrdStat, 
               set<Card>& UnqCard, queue<string>& AcnHtry) {
    // Display welcome message and help information
    cout << "\n WELCOME TO BLACKJACK \n";
    cout << "Type 'help' during gameplay to see rules and commands.\n\n";
    
    inzeGme(user, fname);               // Initialize game 
}

// Play a single round of blackjack
void plyRund(vector<Card>& deck, int& nCards, list<int>& PlyrHnd, 
               list<int>& DlrHand, int& pSum, int& dSum, Save& user, 
               string& fname, map<int, int>& CrdStat, set<Card>& UnqCard,
               queue<string>& AcnHtry, stack<int>& btHstry) {
    
    // Setup new round
    init(deck, nCards);             // Initialize deck 
    shuf(deck);                     // Shuffle deck using STL algorithm
    
    // Ask if player wants to see rules before starting
    char shwRles;
    cout << "Would you like to see the game rules? (y/n): ";
    cin >> shwRles;
    if (tolower(shwRles) == 'y') {
        clrBuf();
        showHlp();
    } else {
        clrBuf();
    }
    
    // Betting phase
    int bet = gtBtAnt(user);        // Get player's bet
    btHstry.push(bet);           // Record bet in history
    
    // Clear hands using STL container methods
    PlyrHnd.clear();             // O(1) operation for list
    DlrHand.clear();             // O(1) operation for list
    
    // Initial deal phase
    dlInCrd(deck, PlyrHnd, DlrHand);  // Deal initial cards 
    dspInDl(PlyrHnd, DlrHand, deck);  // Show initial hands 
    
    // Record action in history
    AcnHtry.push("Initial deal");
    
    plyPrTn(deck, PlyrHnd, pSum);        // Player's turn 
    
    // Record action in history
    AcnHtry.push("Player turn complete");
    
    // Dealer's turn if player didn't bust 
    if (pSum <= 21) { 
        plyDrTn(deck, DlrHand, dSum);
        AcnHtry.push("Dealer turn complete");
    } 
    
    // Outcome determination and statistics update
    hndlGOt(user, bet, pSum, dSum);         // Handle outcome 
    save(user, fname);                      // Save game state 
    
    // Update card statistics
    for (auto it = PlyrHnd.begin(); it != PlyrHnd.end(); ++it) {
        CrdStat[*it]++;
        
        // Create a Card struct to add to the set
        Card c;
        c.val = *it;
        c.suit = HEART; // HEART as a placeholder for uniqueness tracking
        UnqCard.insert(c);
    }
}

// End of round and check for continue
bool endRund(Save& user, list<int>& PlyrHnd, list<int>& DlrHand, 
              int& nCards, map<int, int>& CrdStat, set<Card>& UnqCard,
              queue<string>& AcnHtry) {
    
    // Print card statistics
    pntCStt(CrdStat);
    
    // Report unique cards seen
    cout << "\nNumber of unique card values drawn: " << 
            UnqCard.size() << endl;
    
    // Show action history
    cout << "\nAction history this round:\n";
    queue<string> tmpQeue = AcnHtry;
    while (!tmpQeue.empty()) {
        cout << "- " << tmpQeue.front() << endl;
        tmpQeue.pop();
    }
    
    if (!chcGmCe(user)) return false;   // Check if player can continue 
    
    if (plyARnd()) {                    // Reset for new round
        PlyrHnd.clear();
        DlrHand.clear();
        nCards = SIZE;
        
        // Clear action history for new round
        while (!AcnHtry.empty()) {
            AcnHtry.pop();
        }
        return true;
    }
    
    return false; 
}