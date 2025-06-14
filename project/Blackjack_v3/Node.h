/* 
 * File:   Node.h
 * Author: Ireoluwa
 * Created on June 13, 2025, 11:34 PM
 */

#ifndef NODE_H
#define NODE_H

// Binary tree node for AVL tree
struct Node {
    int data;          // Encoded strategy data (pSum * 100 + dCard)
    char hint;         // Strategy hint: 'h', 's', 'd'
    Node* left;        // Left child
    Node* right;       // Right child
    
    Node();
    Node(int d, char h);
};

// Helper functions for encoding/decoding strategy data
// Encode strategy as single int
int encStr(int pSum, int dCard) {
    return pSum * 100 + dCard;
}

// Get player sum from encoded data
int decSum(int enc) {
    return enc / 100;
}

// Get dealer card from encoded data  
int decCard(int enc) {
    return enc % 100;
}