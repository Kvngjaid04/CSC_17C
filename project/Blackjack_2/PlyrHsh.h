/* 
 * File:   PlyrHsh.h
 * Author: Ireoluwa
 * Created on June 13, 2025, 10:13 PM
 */

#ifndef PlyrHsh_H
#define PlyrHsh_H

#include <vector>
#include <string>
#include "Save.h"

using namespace std;

struct PlyrEnt {
    string name;
    Save data;
    bool actv;
    
    PlyrEnt();
    PlyrEnt(string n, Save d);
};

class PlyrHsh {
private:
    vector<PlyrEnt> tbl;
    int tblSz;
    int numUsr;
    
    int ha1sh(const string& key);
    int ha2sh(const string& key);

public:
    PlyrHsh(int sz = 13);
    
    void add(const string& name, const Save& data);
    Save* get(const string& name);
    vector<PlyrEnt> getAll();
    bool empty();
    int count();
};

// Global functions
extern PlyrHsh alPlyrs;
int clcRate(int wins, int games);
Save selplyr();
void udtplyr(const Save& user);
void lodExst(); 

#endif