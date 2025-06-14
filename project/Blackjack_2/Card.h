#ifndef CARD_H
#define CARD_H

// Card Structure
// Represents a playing card with a suit and numerical value.
// Includes operator overloads to work with STL containers.
struct Card { 
    char suit; 
    int val;
    
    // Comparison operator for set/map - sorts by suit then value
    bool operator<(const Card& other) const {
        if (suit != other.suit)
            return suit < other.suit;
        return val < other.val;
    }
    
    // Equality operator for set - cards are equal if suit and value match
    bool operator==(const Card& other) const {
        return (suit == other.suit && val == other.val);
    }
};

// Enumeration for card suits - used for organization
enum Suit {HEART, DIAM, SPADE, CLUB}; 

#endif