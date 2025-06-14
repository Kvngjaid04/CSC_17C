/* 
 * File:   Menu.cpp
 * Author: Ireoluwa
 * Created on June 11, 2025, 12:14 AM
 */

#include "Menu.h"
#include "Deck.h"
#include "UserMgr.h"
#include <iostream>
#include <algorithm>

using namespace std;

// Show help/rules
void help() {
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

// Play Another Round - simplified since menu moved to endRnd
bool again() { 
    string input;
    char cont; 
    do { 
        cout << "\nPlay again? (y/n) or type 'help' for rules: "; 
        cin >> input;
        
        // Convert to lowercase
        transform(input.begin(), input.end(), input.begin(), ::tolower);
        
        if (input == "help") {
            clrBuf();
            help();
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

// Print card statistics with win rate
void stats(const map<int, int>& stat, const Save& user) {
    cout << "\nCard Statistics:\n";
    cout << "----------------\n";
    
    // Use for_each STL algorithm with lambda
    for_each(stat.begin(), stat.end(), [](const pair<int, int>& item) {
        cout << "Card Value " << getVal(item.first) << ": drawn " << 
                item.second << " times\n";
    });
    
    // Add win rate statistics
    cout << "\nPlayer Statistics:\n";
    cout << "------------------\n";
    cout << "Games Played: " << user.games << "\n";
    cout << "Games Won: " << user.wins << "\n";
    cout << "Win Rate: " << clcRate(user.wins, user.games) << "%\n";
    cout << "Current Cash: $" << user.cash << "\n";
}

// Show menu and get user choice
char getMenu(map<int, int>& cStat, set<Card>& uCard, queue<string>& aHist, 
        Graph& cardGph, Save& user) {
    string input;
    char choice;
    bool valid = false;
    
    do {
        cout << "\nOptions:\n";
        cout << "1 - Display card statistics\n";
        cout << "2 - Display number of unique cards drawn\n";
        cout << "3 - Display action history\n";
        cout << "4 - Show sorted deck\n";
        cout << "5 - Show card relationships\n";
        cout << "y - Play again\n";
        cout << "n - Quit game\n";
        cout << "help - Show game rules\n";
        cout << "Enter choice: ";
        
        cin >> input;
        transform(input.begin(), input.end(), input.begin(), ::tolower);
        
        if (input == "1") {
            stats(cStat, user);  // Now includes win rate
        }
        else if (input == "2") {
            cout << "\nUnique card values drawn: " << uCard.size() << endl;
        }
        else if (input == "3") {
            cout << "\nAction history:\n";
            queue<string> tmpQ = aHist;
            while (!tmpQ.empty()) {
                cout << "- " << tmpQ.front() << endl;
                tmpQ.pop();
            }
        }
        else if (input == "4") {
            // Create a full deck to show sorted
            vector<Card> fullDck(SIZE);
            int tmpSize = SIZE;
            init(fullDck, tmpSize);
            showDck(fullDck);
        }
        else if (input == "5") {
            showRel(cardGph);
        }
        else if (input == "help") {
            clrBuf();
            help();
        }
        else if (input == "y") {
            choice = 'y';
            valid = true;
        }
        else if (input == "n") {
            choice = 'n';
            valid = true;
        }
        else {
            cout << "Invalid choice! Please enter 1-5, y, n, or help\n";
        }
        
    } while (!valid);
    
    clrBuf();
    return choice;
}