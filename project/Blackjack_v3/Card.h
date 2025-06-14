/*  Author: Ireoluwa 
 * Created on October 29, 2024, 12:19 PM 
 * modified for csc_17_c 
 * Date:    May 2, 2024 
 * Purpose: blackjack 
 */ 

#ifndef CARD_H
#define CARD_H

// Card Structure - basic playing card
struct Card { 
    char suit; 
    int val;
    
// Comparison operator for set/map - sorts by suit then value
    bool operator<(const Card& other) const {
        if (suit != other.suit)
            return suit < other.suit;
        return val < other.val;
    }

    // Equality operator - cards equal if suit and value match
    bool operator==(const Card& other) const {
        return (suit == other.suit && val == other.val);
    }
};

// Suit enumeration
enum Suit {HEART, DIAM, SPADE, CLUB}; 

#endif