/*  Author: Ireoluwa 
 * Created on October 29, 2024, 12:19 PM 
 * modified for csc_17_c 
 * Date:    May 2, 2024 
 * Purpose: blackjack 
 */

#include "Hash.h"

Hash allPlyr; // Global hash table

// PlyrEnt constructors
PlyrEnt::PlyrEnt() : actv(false) {}

PlyrEnt::PlyrEnt(std::string n, Save d) : name(n), data(d), actv(true) {}

// Hash constructor
Hash::Hash(int sz) : tblSz(sz), numUsr(0) {
    tbl.resize(tblSz);
}

// djb2 hash function
int Hash::hash1(const std::string& key) {
    int hash = 5381;
    for (char c : key) {
        hash = ((hash << 5) + hash) + c;
    }
    return abs(hash) % tblSz;
}

// Secondary hash
int Hash::hash2(const std::string& key) {
    int hash = 0;
    for (char c : key) {
        hash = c + (hash << 6) + (hash << 16) - hash;
    }
    int step = (abs(hash) % (tblSz - 1)) + 1;
    return step;
}

// Add or update player
void Hash::add(const std::string& name, const Save& data) {
    int idx = hash1(name);
    int step = hash2(name);
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
Save* Hash::get(const std::string& name) {
    int idx = hash1(name);
    int step = hash2(name);
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

// Get all players
std::vector<PlyrEnt> Hash::getAll() {
    std::vector<PlyrEnt> result;
    for (int i = 0; i < tblSz; i++) {
        if (tbl[i].actv) {
            result.push_back(tbl[i]);
        }
    }
    return result;
}

// Check if empty
bool Hash::empty() {
    return numUsr == 0;
}

// Get count
int Hash::count() {
    return numUsr;
}