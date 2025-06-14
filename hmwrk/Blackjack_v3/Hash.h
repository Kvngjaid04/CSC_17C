#ifndef HASH_H
#define HASH_H

#include <vector>
#include <string>
#include "Save.h"

// Player entry for hash table
struct PlyrEnt {
    std::string name;
    Save data;
    bool actv;
    
    PlyrEnt();
    PlyrEnt(std::string n, Save d);
};

// Hash table for players
class Hash {
private:
    std::vector<PlyrEnt> tbl;
    int tblSz;
    int numUsr;
    
    int hash1(const std::string& key);
    int hash2(const std::string& key);

public:
    Hash(int sz = 13);
    
    void add(const std::string& name, const Save& data);
    Save* get(const std::string& name);
    std::vector<PlyrEnt> getAll();
    bool empty();
    int count();
};

// Global hash table
extern Hash allPlyr;

#endif