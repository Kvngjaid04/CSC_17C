/*  Author: Ireoluwa 
 * Created on October 29, 2024, 12:19 PM 
 * modified for csc_17_c 
 * Date:    May 2, 2024 
 * Purpose: blackjack 
 */

#ifndef MENU_H
#define MENU_H

#include <map>
#include <set>
#include <queue>
#include <string>
#include "Card.h"
#include "Save.h"
//#include "Graph.h"

// Menu and UI function prototypes
void help();
bool again();
void stats(const std::map<int, int>&, const Save&);
char getMenu(std::map<int, int>&, std::set<Card>&, 
             std::queue<std::string>&, Save&);

#endif