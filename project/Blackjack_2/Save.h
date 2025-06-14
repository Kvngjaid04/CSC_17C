#ifndef SAVE_H
#define SAVE_H

#include <cstring>

// Save Structure
// Stores player profile information for save/load functionality.
// Includes data about performance and game statistics.
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

#endif