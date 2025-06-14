/*  Author: Ireoluwa 
 * Created on October 29, 2024, 12:19 PM 
 * modified for csc_17_c 
 * Date:    May 2, 2024 
 * Purpose: blackjack 
 */

#include "Menu.h"
#include "Deck.h"
#include "UserMgr.h"
#include <iostream>
#include <algorithm>
using namespace std;

// Show help/rules
void help() {
   cout << "\n     BLACKJACK RULES      \n";
     cout << "1. Goal: Get closer to 21 than dealer without going over.\n";
    cout << "2. Card values: Aces=1/11, Face cards=10, others=face.\n";
    cout << "3. Both get two cards; one dealer card hidden.\n";
    cout << "4. Player can 'hit' (take cards) or 'stand' (keep hand).\n";
    cout << "5. If over 21, you 'bust' and lose.\n";
    cout << "6. Dealer hits until 17 or higher.\n";
    cout << "7. If dealer busts, player wins. Else highest wins.\n";
    cout << "8. Blackjack (Ace + 10) pays 3:2.\n";
    cout << "9. Equal values = 'push' (tie).\n\n";
    cout << "      COMMANDS     \n";
    cout << "h - Hit (take card)\n";
    cout << "s - Stand (end turn)\n";
    cout << "d - Double Down (double bet, one card)\n";
    cout << "hint - Show strategy advice\n\n";
    cout << "Press Enter to continue..." << endl;
    cin.ignore(1000, '\n');
}

// Play again prompt
bool again() { 
    string input;
    char cont; 
    do { 
        cout << "\nPlay again? (y/n) or 'help': "; 
        cin >> input;
        
        transform(input.begin(), input.end(), input.begin(), 
                  ::tolower);
        
        if (input == "help") {
            clrBuf();
            help();
            continue;
        } else if (input == "quit") {
            cout << "Exiting game. Thanks for playing!" << endl;
            exit(0);
        } else if (input.length() == 1) {
            cont = input[0];
        } else {
            cont = 'x';
        }
        
        if (cont != 'y' && cont != 'n') 
            cout << "Please enter y or n\n"; 
    } while (cont != 'y' && cont != 'n'); 
    
    clrBuf(); 
    
    if (cont == 'n') { 
        cout << "Exiting game. Goodbye!" << endl; 
        exit(0); 
    }
    
    return true;
}

// Print card statistics with win rate
void stats(const map<int, int>& stat, const Save& user) {
    cout << "\nCard Statistics:\n";
    cout << "----------------\n";
    
    for_each(stat.begin(), stat.end(), [](const pair<int, int>& item) {
        cout << "Card Value " << getVal(item.first) << ": drawn " << 
                item.second << " times\n";
    });
    
    cout << "\nPlayer Statistics:\n";
    cout << "------------------\n";
    cout << "Games Played: " << user.games << "\n";
    cout << "Games Won: " << user.wins << "\n";
    cout << "Win Rate: " << calcRte(user.wins, user.games) << "%\n";
    cout << "Current Cash: $" << user.cash << "\n";
}

// Show menu and get user choice
char getMenu(map<int, int>& cStat, set<Card>& uCard, 
             queue<string>& aHist, Save& user) {
    string input;
    char choice;
    bool valid = false;
    
    do {
        cout << "\nOptions:\n";
        cout << "1 - Card statistics\n";
        cout << "2 - Unique cards drawn\n";
        cout << "3 - Action history\n";
        cout << "4 - Show sorted deck\n";
        cout << "y - Play again\n";
        cout << "n - Quit game\n";
        cout << "help - Show rules\n";
        cout << "Enter choice: ";
        cin >> input;
        transform(input.begin(), input.end(), input.begin(), 
                  ::tolower);
        if (input == "1") {  stats(cStat, user);}
        else if (input == "2") {
            cout << "\nUnique card values drawn: " << uCard.size() << endl; }
        else if (input == "3") { cout << "\nAction history:\n";
            queue<string> tmpQ = aHist;
            while (!tmpQ.empty()) {
                cout << "- " << tmpQ.front() << endl;
                tmpQ.pop();
            }
        }
        else if (input == "4") {
            vector<Card> fullDck(SIZE); int tmpSize = SIZE;
            init(fullDck, tmpSize); showDck(fullDck);
        }
        else if (input == "help") {
            clrBuf(); help();
        }
        else if (input == "y") {
            choice = 'y';  valid = true;
        }
        else if (input == "n") {
            choice = 'n'; valid = true;
        }
        else {
            cout << "Invalid choice! Please enter 1-4, y, n, or help\n";
        }
        
    } while (!valid);
    clrBuf();
    return choice;
}