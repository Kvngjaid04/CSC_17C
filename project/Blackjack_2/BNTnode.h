/* 
 * File:   bntnode.h
 * Author: Ireoluwa
 * Created on June 10, 2025, 12:10 PM
 */

#ifndef BNTNODE_H
#define BNTNODE_H

struct BNTnode {
    int data;          // Encoded strategy data (pSum * 100 + dCard)
    char hint;         // Strategy hint: 'h', 's', 'd'
    BNTnode* left;     // Left child
    BNTnode* right;    // Right child
    
    // Constructor
    BNTnode() : data(0), hint('s'), left(nullptr), right(nullptr) {}
    BNTnode(int d, char h) : data(d), hint(h), left(nullptr), right(nullptr) {}
};

// Helper functions for encoding/decoding strategy data
inline int encodeStrat(int pSum, int dCard) {
    return pSum * 100 + dCard;  // Encode as single int
}

inline int decodeSum(int encoded) {
    return encoded / 100;       // Get player sum
}

inline int decodeCard(int encoded) {
    return encoded % 100;       // Get dealer card
}

#endif