/* 
 * File:   Gameplay.h
 * Author: Ireoluwa
 * Created on June 10, 2025, 12:10 PM
 */

#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <string>
#include "Card.h"
#include "Save.h"
#include "AVLTree.h"
#include "Graph.h"

// Core gameplay function prototypes
int sumHand(const std::list<int>&);                                  // Sum hand
bool dblDown(Save&, int&, int );                     // Double down recursion
void deal(std::vector<Card>&, std::list<int>&, std::list<int>&);   // Deal cards 
void show(const std::list<int>&, const std::list<int>&, 
            const std::vector<Card>&);                              // Show deal
// Show strategy hint and win probability
void showHint(AVLTree&, Graph&, std::list<int>&, int, int); 
void pTurn(std::vector<Card>&, std::list<int>&, int&, Save&, int&,
        AVLTree&, Graph&);                                      // Player's turn 
void dTurn(std::vector<Card>&, std::list<int>&, int&);          // Dealer's turn 
void result(Save&, int, int, int);                             // Handle outcome 
bool canPlay(const Save&);                                     // Check continue 

#endif