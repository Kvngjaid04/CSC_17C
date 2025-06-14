/*  Author: Ireoluwa 
 * Created on October 29, 2024, 12:19 PM 
 * modified for csc_17_c 
 * Date:    May 2, 2024 
 * Purpose: blackjack 
 */

#include "UserMgr.h"
#include "Hash.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cctype>
#include <cstring>
#include <dirent.h>
using namespace std;

// Calculate win rate percentage
int calcRte(int wins, int games) {
    return games > 0 ? (wins * 100) / games : 0;
}

// Get player's betting amount 
int getBet(const Save& user) { 
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

// Validate username
bool valName(string name) { 
    if (name.length() < 3 || name.length() > 7) { 
        cout << "Username must be 3-7 characters\n"; 
        return false; 
    } 
    
    int badChr = count_if(name.begin(), name.end(), [](char c) {
        return !isalnum(c) && c != '_';
    });
    
    if (badChr > 0) {
        cout << "Username can only contain letters, numbers, "
                "underscore\n"; 
        return false;
    }
    
    return true; 
}

// Validate user data
bool valData(const Save& user) {
    return user.cash >= 0 && user.cash < 999999 &&  // No debt allowed
           user.games >= 0 && user.wins >= 0 && 
           user.wins <= user.games;
}

// Clear input buffer 
void clrBuf() { 
    cin.clear(); 
    cin.ignore(1000, '\n'); 
}

// Load saved game 
bool load(Save& user, string name) { 
    string fname = name + ".dat"; 
    ifstream in(fname, ios::binary | ios::in); 
    
    if (!in) return false; 
    
    in.seekg(0, ios::end);
    long fSize = in.tellg(); 
    in.seekg(0, ios::beg); 
    in.read(reinterpret_cast<char*>(&user), sizeof(Save)); 
    in.close(); 
    
    return true; 
}

// Save current game state 
void save(Save user, string name) { 
    string fname = name + ".dat"; 
    ofstream out(fname, ios::binary | ios::out); 
    out.write(reinterpret_cast<char*>(&user), sizeof(Save)); 
    out.close(); 
}

// Load existing save files into hash table
void lodExst() {
    DIR* dir = opendir(".");
    if (dir == nullptr) return;

    struct dirent* entry;
    while ((entry = readdir(dir)) != nullptr) {
        string fname = entry->d_name;

        if (fname.length() > 4 && 
            fname.substr(fname.length() - 4) == ".dat") {
            string usr = fname.substr(0, fname.length() - 4);
            if (usr.length() < 3 || usr.length() > 7) continue;

            Save user;
            ifstream in(fname, ios::binary);
            if (in && in.good()) {
                in.read(reinterpret_cast<char*>(&user), sizeof(Save));
                in.close();

                if (user.cash >= 0 && user.cash < 999999 &&
                    user.games >= 0 && user.wins >= 0) {
                    allPlyr.add(usr, user);
                }
            }
        }
    }
    closedir(dir);
}

// Check and fix broke player balance
bool chckBal(Save& user) {
    if (user.cash <= 0) {
        cout << "\nPlayer " << user.name 
             << " has $0! Reset balance to $1000? (y/n): ";
        char reset;
        cin >> reset;
        if (reset == 'y' || reset == 'Y') {
            user.cash = 1000;
            string name(user.name);
            allPlyr.add(name, user);
            save(user, name);
            cout << "Balance reset to $1000!\n";
            return true;
        }
        return false;
    }
    return true;
}

// Load existing player
Save lodExst(vector<PlyrEnt>& players) {
    cout << "\nAvailable players:\n";
    for (int i = 0; i < players.size(); i++) {
        auto& p = players[i];
        int r = calcRte(p.data.wins, p.data.games);
        cout << i+1 << ". " << p.name << " (" << p.data.games
             << " games, " << r << "% win rate, $" 
             << p.data.cash << ")\n";
    }
    
    int sel; 
    cout << "\nSelect player: "; 
    cin >> sel;
    
    if (sel >= 1 && sel <= players.size()) {
        Save user = players[sel-1].data;
        
        if (chckBal(user)) {
            cout << "Welcome back " << players[sel-1].name << "!\n";
            return user;
        }
    }
    
    cout << "Invalid selection!\n";
    return selPlyr();
}

// Create new player
Save creatNw() {
    cout << "Enter new username: ";
    string name; 
    cin >> name;
    
    if (!valName(name)) {
        return selPlyr();
    }
    
    if (allPlyr.get(name)) {
        cout << "Player already exists!\n";
        return selPlyr(); 
    }
    
    Save n{}; 
    strcpy(n.name, name.c_str());
    n.cash = 1000;
    allPlyr.add(name, n);
    cout << "Welcome " << name << "!\n";
    return n;
}
    
// Show leaderboard
void shwLead(vector<PlyrEnt>& players) {
    if (players.empty()) {
        cout << "No players found!\n";
        return;
    }
    
    sort(players.begin(), players.end(), [](const PlyrEnt& a, 
         const PlyrEnt& b) { 
            return calcRte(b.data.wins, b.data.games) < 
                   calcRte(a.data.wins, a.data.games); 
    });
    
    cout << "\n    LEADERBOARD  (sorted by win rate)  \n";
    for (int i = 0; i < players.size(); i++) {
        int r = calcRte(players[i].data.wins, players[i].data.games);
        cout << i+1 << ". " << players[i].name << " - " << r 
             << "% win rate ($" << players[i].data.cash << ")\n"; 
    }
}

// Reset player balance
Save rsetBal(vector<PlyrEnt>& players) {
    if (players.empty()) {
        cout << "No players found!\n";
        return selPlyr();
    }
    
    cout << "\nSelect player to reset:\n";
    for (int i = 0; i < players.size(); i++) {
        auto& p = players[i];
        cout << i+1 << ". " << p.name << " ($" << p.data.cash << ")\n";
    }
    
    int sel;
    cout << "\nSelect player: ";
    cin >> sel;
    
    if (sel >= 1 && sel <= players.size()) {
        Save resetUser = players[sel-1].data;
        resetUser.cash = 1000;
        string name(resetUser.name);
        allPlyr.add(name, resetUser);
        save(resetUser, name);
        cout << "Player " << resetUser.name 
             << " balance reset to $1000!\n";
        return resetUser;
    }
    
    cout << "Invalid selection!\n";
    return selPlyr();
}

// Main player selection menu
Save selPlyr() {
    static bool loaded = false;
    if (!loaded) { 
        lodExst();
        loaded = true; 
    }
    
    cout << "\n   PLAYER SELECTION    \n";
    cout << "1. Load existing player\n2. Create new player\n";
    cout << "3. View leaderboard\n4. Switch player\n";
    cout << "5. Reset player balance\n";
    cout << "Choose option: ";
    
    int c; 
    cin >> c;
    vector<PlyrEnt> players = allPlyr.getAll();
    
    if ((c == 1 || c == 4) && players.empty()) {
        cout << "No players found! Please create a new player.\n";
        return selPlyr();
    }
    
    switch(c) {
        case 1:
        case 4:
            return lodExst(players);
        case 2:
            return creatNw();
        case 3:
            shwLead(players);
            return selPlyr();
        case 5:
            return rsetBal(players);
        default:
            cout << "Invalid option!\n";
            return selPlyr();
    }
}

// Update player in hash after game
void updPlyr(const Save& user) {
    string name(user.name);
    allPlyr.add(name, user);
}