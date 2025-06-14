#ifndef DECK_H
#define DECK_H

#include <vector>
#include <string>
#include "Card.h"

// Global Constants
const int SIZE = 52;                // Deck size 

// Function Prototypes for deck operations
void init(std::vector<Card>&, int&);        // Initialize deck using vector
void shuf(std::vector<Card>&);              // Shuffle deck using random_shuffle
int draw(std::vector<Card>&);               // Draw card using STL containers
void pCard(int, char);                      // Print card 
std::string getSuit(int);                  // Get full name of suit 
std::string getVal(int);                   // Get card value as string 
void srtDeck(std::vector<Card>&, int, int);     // Sort deck/hand recursively
void mrg(std::vector<Card>&, int, int, int); // Merge subarrays
void showDck(const std::vector<Card>&);    // Print deck/hand

#endif