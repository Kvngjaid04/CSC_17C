/*  Author: Ireoluwa 
 * Created on October 29, 2024, 12:19 PM 
 * modified for csc_17_c 
 * Date:    May 2, 2024 
 * Purpose: blackjack 
 */

#ifndef DECK_H
#define DECK_H

#include <vector>
#include <string>
#include "Card.h"

// Global constants
const int SIZE = 52;

// Deck function prototypes
void init(std::vector<Card>&, int&);
void shuf(std::vector<Card>&);
int draw(std::vector<Card>&);
void pCard(int, char);
std::string getSuit(int);
std::string getVal(int);
void srtDeck(std::vector<Card>&, int, int);
void mrg(std::vector<Card>&, int, int, int);
void showDck(const std::vector<Card>&);

#endif