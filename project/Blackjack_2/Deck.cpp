/* 
 * File:   deck.cpp
 * Author: Ireoluwa
 * Created on June 11, 2025, 12:14 AM
 */

#include "Deck.h"
#include <iostream>
#include <algorithm>
#include <map>
#include <cstdlib>
#include <ctime>

using namespace std;

// Function to initialize the deck of cards using vector
void init(vector<Card>& deck, int& size) {
    deck.clear();
    for (int s = 0; s < 4; ++s) {        // 4 suits
        for (int v = 1; v <= 13; ++v) {  // 13 values per suit
            Card c;
            c.val = v;
            c.suit = static_cast<char>(s);  // Store as char
            deck.push_back(c);
        }
    }
    size = deck.size();  // Will be exactly 52
}

// Function to shuffle the deck of cards using STL algorithm
void shuf(vector<Card>& deck) { 
    // Using random_shuffle algorithm (works with srand in main)
    random_shuffle(deck.begin(), deck.end());
} 

// Function to draw a card from the deck using vector
int draw(vector<Card>& deck) { 
    int val = deck.back().val > 10 ? 10 : deck.back().val;
    deck.pop_back();
    return val;
} 

// Function to return the full name of a suit
string getSuit(int s) { 
    switch (s) { 
        case HEART: return "Hearts"; 
        case DIAM: return "Diamonds"; 
        case SPADE: return "Spades"; 
        default: return "Clubs"; 
    } 
} 

// Function to return the full name of a card's value
string getVal(int val) {  
    const map<int, string> vluNmes = {
        {1, "Ace"},
        {2, "Two"},
        {3, "Three"},
        {4, "Four"},
        {5, "Five"},
        {6, "Six"},
        {7, "Seven"},
        {8, "Eight"},
        {9, "Nine"},
        {10, "Ten"},
        {11, "Jack"},
        {12, "Queen"},
        {13, "King"}
    };
    
    // Use find algorithm and map container
    auto it = vluNmes.find(val);
    if (it != vluNmes.end()) {
        return it->second;
    }
    
    return "Unknown";
} 

// Function to print a single card's value and suit 
void pCard(int val, char suit) { 
    cout << getVal(val) << " of " << getSuit(suit) << endl; 
}

// Merge subarrays
void mrg(vector<Card>& deck, int lft, int mid, int rgt) {
    vector<Card> lft_dck(deck.begin() + lft, deck.begin() + mid + 1);
    vector<Card> rgt_dck(deck.begin() + mid + 1, deck.begin() + rgt + 1);
    int i = 0, j = 0, k = lft;
    while (i < lft_dck.size() && j < rgt_dck.size()) {
        if (lft_dck[i].val < rgt_dck[j].val || 
            (lft_dck[i].val == rgt_dck[j].val && lft_dck[i].suit <= rgt_dck[j].suit)) {
            deck[k++] = lft_dck[i++];
        } else {
            deck[k++] = rgt_dck[j++];
        }
    }
    while (i < lft_dck.size()) deck[k++] = lft_dck[i++];
    while (j < rgt_dck.size()) deck[k++] = rgt_dck[j++];
}

// Recursive sort
void srtDeck(vector<Card>& deck, int lft, int rgt) {
    if (lft < rgt) {
        int mid = lft + (rgt - lft) / 2;
        srtDeck(deck, lft, mid);
        srtDeck(deck, mid + 1, rgt);
        mrg(deck, lft, mid, rgt);
    }
}

void showDck(const vector<Card>& deck) {
    cout << "\n      SORTED DECK      \n";
    vector<Card> tempDck = deck;  // Create copy to sort
    srtDeck(tempDck, 0, tempDck.size() - 1);  // Uses your recursive sort!
    
    // Display all 52 cards numbered and organized
    for (int i = 0; i < tempDck.size(); i++) {
        cout << (i + 1) << ". ";
        pCard(tempDck[i].val, tempDck[i].suit);
        
        // Add spacing every 13 cards (each suit)
        if ((i + 1) % 13 == 0 && i < tempDck.size() - 1) {
            cout << "\n";
        }
    }
}