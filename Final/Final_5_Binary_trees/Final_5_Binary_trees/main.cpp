/* 
 * File:   main.cpp
 * Author: Ireoluwa
 * Created on June 10, 2025, 1:07 AM
 */

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <string>
#include <vector>
using namespace std;

//User Libraries
#include "AVLTree.h"

//Global Constants - Mathematical, Scientific, Conversions
const int SIZE = 512;
const int TOTAL = 512;

//Higher Dimensions go here. No Variables

//Function Prototypes

int phneMap(char c);
int phhash(string initls);
void insert(HNode* table[], string initls);
void genRand(HNode* table[], vector<string>& initls);
void bldTree(AVLTree trees[], vector<string>& initls);
void compare(HNode* table[], AVLTree trees[], vector<string>& initls);
int hashSrc(HNode* table[], string initls);
int treeSrc(AVLTree trees[], string initls);

//Execution Begins here

int main(int argc, char** argv) {
    //Setting the random number seed
    srand(time(0));
    
    //Declaring Variables
    //Initialize Variables
    HNode* table[SIZE];
    AVLTree trees[3];
    vector<string> initls;
    
    for(int i = 0; i < SIZE; i++) {
        table[i] = nullptr;
    }
    
    //Displaying Input/Output Information
    genRand(table, initls);
    bldTree(trees, initls);
    compare(table, trees, initls);
    
    //Exiting stage left/right
    return 0;
}

int phneMap(char c) {           
    if(c >= 'A' && c <= 'C') return 2;
    if(c >= 'D' && c <= 'F') return 3;
    if(c >= 'G' && c <= 'I') return 4;
    if(c >= 'J' && c <= 'L') return 5;
    if(c >= 'M' && c <= 'O') return 6;
    if(c >= 'P' && c <= 'S') return 7;
    if(c >= 'T' && c <= 'V') return 8;
    if(c >= 'W' && c <= 'Z') return 9;
    return 0;
}

int phhash(string initls) {
    int a = phneMap(initls[0]);
    int b = phneMap(initls[1]);
    int c = phneMap(initls[2]);
    return ((a-2) * 64 + (b-2) * 8 + (c-2)) % SIZE; 
}

void insert(HNode* table[], string initls) {
    int index = phhash(initls);
    HNode* newN = new HNode(initls);
    newN->next = table[index];
    table[index] = newN;
}

void genRand(HNode* table[], vector<string>& initls) {
    for(int i = 0; i < TOTAL; i++) {
        string init = "";
        for(int j = 0; j < 3; j++) {
            char c = 'A' + rand() % 26;
            init += c;
        }
        insert(table, init);
        initls.push_back(init);
    }
}

void bldTree(AVLTree trees[], vector<string>& initls) {
    for(string init : initls) {
        for(int i = 0; i < 3; i++) {
            trees[i].root = trees[i].insert(trees[i].root, init[i]);
        }
    }
}

int hashSrc(HNode* table[], string initls) {
    int index = phhash(initls);
    int count = 0;
    HNode* curr = table[index];
    
    while(curr) {
        count++;
        if(curr->initls == initls) return count;
        curr = curr->next;
    }
    return count;
}

int treeSrc(AVLTree trees[], string initls) {
    int total = 0;
    for(int i = 0; i < 3; i++) {
        trees[i].reset();
        trees[i].search(trees[i].root, initls[i]);
        total += trees[i].srchCnt;
    }
    return total;
}

void compare(HNode* table[], AVLTree trees[], vector<string>& initls) {
    cout << "Hash vs AVL Tree Comparison:\n";
    cout << "Searching for 10 random initials:\n\n";
    
    int hashTot = 0, treeTot = 0;
    
    for(int i = 0; i < 10 && i < initls.size(); i++) {
        string target = initls[rand() % initls.size()];
        int hashOps = hashSrc(table, target);
        int treeOps = treeSrc(trees, target);
        
        cout << target << ": Hash=" << hashOps 
             << " operations, Tree=" << treeOps << " operations\n";
        
        hashTot += hashOps;
        treeTot += treeOps;
    }
    
    cout << "\nAverage operations:\n";
    cout << "Hash Table: " << hashTot/10.0 << "\n";
    cout << "AVL Trees: " << treeTot/10.0 << "\n";
    
    if(hashTot < treeTot) {
        cout << "Hash table is faster\n";
    } else {
        cout << "AVL trees are faster\n";
    }
}