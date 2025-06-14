/* 
 * File:   PlyrHsh.cpp
 * Author: Ireoluwa
 * Created on June 13, 2025, 10:13 PM
 */

#include "PlyrHsh.h"
#include "UserMgr.h"
#include <iostream>
#include <algorithm>

using namespace std;

PlyrHsh alPlyrs;  // Global hash table

// PlyrEnt constructors
PlyrEnt::PlyrEnt() : actv(false) {}
PlyrEnt::PlyrEnt(string n, Save d) : name(n), data(d), actv(true) {}

// PlyrHsh constructor
PlyrHsh::PlyrHsh(int sz) : tblSz(sz), numUsr(0) {
    tbl.resize(tblSz);
}

// djb2 hash function
int PlyrHsh::ha1sh(const string& key) {
    int hash = 5381;
    for (char c : key) {
        hash = ((hash << 5) + hash) + c;
    }
    return abs(hash) % tblSz;
}

// Secondary hash
int PlyrHsh::ha2sh(const string& key) {
    int hash = 0;
    for (char c : key) {
        hash = c + (hash << 6) + (hash << 16) - hash;
    }
    int step = (abs(hash) % (tblSz - 1)) + 1;
    return step;
}

// Add or update player
void PlyrHsh::add(const string& name, const Save& data) {
    int idx = ha1sh(name);
    int step = ha2sh(name);
    int start = idx;

    do {
        if (!tbl[idx].actv) {
            tbl[idx] = PlyrEnt(name, data);
            numUsr++;
            return;
        } else if (tbl[idx].name == name) {
            tbl[idx].data = data;
            return;
        }
        idx = (idx + step) % tblSz;
    } while (idx != start);
}

// Retrieve player
Save* PlyrHsh::get(const string& name) {
    int idx = ha1sh(name);
    int step = ha2sh(name);
    int start = idx;

    do {
        if (tbl[idx].actv && tbl[idx].name == name) {
            return &(tbl[idx].data);
        } else if (!tbl[idx].actv && tbl[idx].name.empty()) {
            break;
        }
        idx = (idx + step) % tblSz;
    } while (idx != start);

    return nullptr;
}

// All players
vector<PlyrEnt> PlyrHsh::getAll() {
    vector<PlyrEnt> result;
    for (int i = 0; i < tblSz; i++) {
        if (tbl[i].actv) {
            result.push_back(tbl[i]);
        }
    }
    return result;
}

bool PlyrHsh::empty() {
    return numUsr == 0;
}

int PlyrHsh::count() {
    return numUsr;
}

// Player selection menu
Save selplyr() {
    static bool loaded = false;
    if (!loaded) { 
        lodExst();  // Now in UserMgr.cpp
        loaded = true; 
    }
    
    cout << "\n   PLAYER SELECTION    \n";
    cout << "1. Load existing player\n2. Create new player\n";
    cout << "3. View leaderboard\n4. Switch player\nChoose option: ";
    
    int c; 
    cin >> c;
    vector<PlyrEnt> players = alPlyrs.getAll();
    
    if ((c == 1 || c == 4) && players.empty()) {
        cout << "No players found! Please create a new player.\n";
        return selplyr();
    }
    
    if (c == 1 || c == 4) {
        cout << "\nAvailable players:\n";
        for (int i = 0; i < players.size(); i++) {
            auto& p = players[i];
            int r = clcRate(p.data.wins, p.data.games);  // Now in UserMgr.cpp
            cout << i+1 << ". " << p.name << " (" << p.data.games
                 << " games, " << r << "% win rate, $" << p.data.cash << ")\n";
        }
        
        int sel; 
        cout << "\nSelect player: "; 
        cin >> sel;
        
        if (sel >= 1 && sel <= players.size()) {
            cout << "Welcome back " << players[sel-1].name << "!\n";
            return players[sel-1].data;
        }
        
        cout << "Invalid selection!\n";
        return selplyr();
    }
    
    if (c == 2) {
        cout << "Enter new username: ";
        string name; 
        cin >> name;
        
        if (!vName(name)) {  // Use UserMgr validation
            return selplyr();
        }
        
        if (alPlyrs.get(name)) {
            cout << "Player already exists!\n";
            return selplyr(); 
        }
        
        Save n{}; 
        strcpy(n.name, name.c_str());
        n.cash = 1000;
        alPlyrs.add(name, n);
        cout << "Welcome " << name << "!\n";
        return n;
    }
    
    if (c == 3) {
        if (players.empty()) {
            cout << "No players found!\n";
            return selplyr();
        }
        
        sort(players.begin(), players.end(), [](const PlyrEnt& a, 
             const PlyrEnt& b) { 
                return clcRate(b.data.wins, b.data.games) < 
                       clcRate(a.data.wins, a.data.games); 
        });
        
        cout << "\n    LEADERBOARD  (sorted by win rate)  \n";
        for (int i = 0; i < players.size(); i++) {
            int r = clcRate(players[i].data.wins, players[i].data.games);
            cout << i+1 << ". " << players[i].name << " - " << r << "% win rate "
                    "($" << players[i].data.cash << ")\n"; 
        }
        return selplyr();
    }
    
    cout << "Invalid option!\n";
    return selplyr();
}

// Update player in hash after game
void udtplyr(const Save& user) {
    string name(user.name);
    alPlyrs.add(name, user);
}