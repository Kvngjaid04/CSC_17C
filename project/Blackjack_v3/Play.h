/*  Author: Ireoluwa 
 * Created on October 29, 2024, 12:19 PM 
 * modified for csc_17_c 
 * Date:    May 2, 2024 
 * Purpose: blackjack 
 */

#ifndef PLAY_H
#define PLAY_H

#include <vector>
#include <list>
#include "Card.h"
#include "Save.h"
#include "AVL.h"
//#include "Graph.h"

// Core gameplay function prototypes
int sumHand(const std::list<Card>&);
bool dblDown(Save&, int&, int = 0);
void deal(std::vector<Card>&, std::list<Card>&, std::list<Card>&);
void show(const std::list<Card>&, const std::list<Card>&, 
          const std::vector<Card>&);
void hint(AVL&, std::list<Card>&, int, int);
void pTurn(std::vector<Card>&, std::list<Card>&, int&, Save&, 
           int&, AVL&);
void dTurn(std::vector<Card>&, std::list<Card>&, int&);
void result(Save&, int, int, int);
bool canPlay(const Save&);

#endif