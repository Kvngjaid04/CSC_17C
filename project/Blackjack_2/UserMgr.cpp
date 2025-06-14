#include "UserMgr.h"
#include "PlyrHsh.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <cctype>
#include <cstring>
#include <dirent.h>

using namespace std;

// Function to calculate win rate percentage
int clcRate(int wins, int games) {
    return games > 0 ? (wins * 100) / games : 0;
}

// Function to get the player's betting amount 
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

// Validate Name
bool vName(string name) { 
    if (name.length() < 3 || name.length() > 7) { 
        cout << "Username must be 3-7 characters\n"; 
        return false; 
    } 
    
    // Use STL algorithm count_if with lambda
    int badChr = count_if(name.begin(), name.end(), [](char c) {
        return !isalnum(c) && c != '_';
    });
    
    if (badChr > 0) {
        cout << "Username can only contain letters, numbers, underscore\n"; 
        return false;
    }
    
    return true; 
}

// Validate user data
bool valData(const Save& user) {
    return user.cash >= 0 && user.cash < 999999 && 
           user.games >= 0 && user.wins >= 0 && 
           user.wins <= user.games;
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
    long fSize = in.tellg(); 
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

// Load existing save files into hash table
void lodExst() {
    DIR* dir = opendir(".");
    if (dir == nullptr) return;

    struct dirent* entry;
    while ((entry = readdir(dir)) != nullptr) {
        string fname = entry->d_name;

        if (fname.length() > 4 && fname.substr(fname.length() - 4) == ".dat") {
            string usr = fname.substr(0, fname.length() - 4);
            if (usr.length() < 3 || usr.length() > 7) continue;

            Save user;
            ifstream in(fname, ios::binary);
            if (in && in.good()) {
                in.read(reinterpret_cast<char*>(&user), sizeof(Save));
                in.close();

                if (user.cash >= 0 && user.cash < 999999 &&
                    user.games >= 0 && user.wins >= 0) {
                    alPlyrs.add(usr, user);
                }
            }
        }
    }
    closedir(dir);
}