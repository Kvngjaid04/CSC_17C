/*  Author: Ireoluwa 
 * Created on October 29, 2024, 12:19 PM 
 * modified for csc_17_c 
 * Date:    May 2, 2024 
 * Purpose: blackjack 
 */

#include "Deck.h"
#include <iostream>
#include <algorithm>
#include <map>
#include <cstdlib>
using namespace std;

// Initialize deck of cards using vector
void init(vector<Card>& deck, int& size) {
    deck.clear();
    for (int s = 0; s < 4; ++s) {
        for (int v = 1; v <= 13; ++v) {
            Card c;
            c.val = v;
            c.suit = static_cast<char>(s);
            deck.push_back(c);
        }
    }
    size = deck.size();
}

// Shuffle deck using STL algorithm
void shuf(vector<Card>& deck) { 
    random_shuffle(deck.begin(), deck.end());
} 

// Draw card from deck
int draw(vector<Card>& deck) { 
    if (deck.empty()) return 10; // Safety check
    int val = deck.back().val > 10 ? 10 : deck.back().val;
    deck.pop_back();
    return val;
} 

// Get full name of suit
string getSuit(int s) { 
    switch (s) { 
        case HEART: return "Hearts"; 
        case DIAM: return "Diamonds"; 
        case SPADE: return "Spades"; 
        default: return "Clubs"; 
    } 
} 

// Get full name of card value
string getVal(int val) {  
    const map<int, string> vluNmes = {
        {1, "Ace"}, {2, "Two"}, {3, "Three"}, {4, "Four"},
        {5, "Five"}, {6, "Six"}, {7, "Seven"}, {8, "Eight"},
        {9, "Nine"}, {10, "Ten"}, {11, "Jack"}, 
        {12, "Queen"}, {13, "King"}
    };
    
    auto it = vluNmes.find(val);
    if (it != vluNmes.end()) {
        return it->second;
    }
    
    return "Unknown";
} 

// Print single card
void pCard(int val, char suit) { 
    cout << getVal(val) << " of " << getSuit(suit) << endl; 
}

// Merge subarrays for sort
void mrg(vector<Card>& deck, int lft, int mid, int rgt) {
    vector<Card> lftDck(deck.begin() + lft, 
                        deck.begin() + mid + 1);
    vector<Card> rgtDck(deck.begin() + mid + 1, 
                        deck.begin() + rgt + 1);
    int i = 0, j = 0, k = lft;
    
    while (i < lftDck.size() && j < rgtDck.size()) {
        if (lftDck[i].val < rgtDck[j].val || 
            (lftDck[i].val == rgtDck[j].val && 
             lftDck[i].suit <= rgtDck[j].suit)) {
            deck[k++] = lftDck[i++];
        } else {
            deck[k++] = rgtDck[j++];
        }
    }
    while (i < lftDck.size()) deck[k++] = lftDck[i++];
    while (j < rgtDck.size()) deck[k++] = rgtDck[j++];
}

// Recursive merge sort
void srtDeck(vector<Card>& deck, int lft, int rgt) {
    if (lft < rgt) {
        int mid = lft + (rgt - lft) / 2;
        srtDeck(deck, lft, mid);
        srtDeck(deck, mid + 1, rgt);
        mrg(deck, lft, mid, rgt);
    }
}

// Show sorted deck
void showDck(const vector<Card>& deck) {
    cout << "\n      SORTED DECK      \n";
    vector<Card> tmpDck = deck;
    srtDeck(tmpDck, 0, tmpDck.size() - 1);
    
    for (int i = 0; i < tmpDck.size(); i++) {
        cout << (i + 1) << ". ";
        pCard(tmpDck[i].val, tmpDck[i].suit);
        
        if ((i + 1) % 13 == 0 && i < tmpDck.size() - 1) {
            cout << "\n";
        }
    }
}