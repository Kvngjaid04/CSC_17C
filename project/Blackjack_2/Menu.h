/* 
 * File:   Menu.h
 * Author: Ireoluwa
 * Created on June 13, 2025, 9:16 PM
 */

#ifndef MENU_H
#define MENU_H

#include <map>
#include <set>
#include <queue>
#include <string>
#include "Card.h"
#include "Save.h"
#include "Graph.h"

// Menu and UI function prototypes
void help();                                // Show help/rules 
bool again();                               // Play again
void stats(const std::map<int, int>&, const Save&); // Print stats with win rate
char getMenu(std::map<int, int>&, std::set<Card>&, std::queue<std::string>&, 
                Graph&, Save&);                                     // Show menu

#endif