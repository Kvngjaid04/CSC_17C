/* 
 * File:   AVL.h
 * Author: Ireoluwa
 * Created on June 13, 2025, 11:34 PM
 * Purpose: AVL Tree implementation for Blackjack strategy
 */
#ifndef AVL_H
#define AVL_H

#include <iostream>

struct Node {
    int data;
    char hint;
    Node* left;
    Node* right;
    Node(int val, char h) : data(val), hint(h), left(nullptr), right(nullptr) {}
};

class AVL {
public:
    Node* root;

    AVL() { root = nullptr; }
    ~AVL();

    int height(Node*);
    int diff(Node*);
    Node* llRot(Node*);
    Node* rrRot(Node*);
    Node* lrRot(Node*);
    Node* rlRot(Node*);
    Node* bal(Node*);
    Node* ins(Node*, int, char);
    void ins(int, char);
    Node* find(Node*, int);
    char getHint(int pSum, int dCard);
    void bldStr();
    void clear(Node*);
    void show(Node*, int);
    void inOrd(Node*);
};

// Implementation
//---------------------------------------------------------
// Helper functions for encoding/decoding
//---------------------------------------------------------
inline int encStr(int pSum, int dCard) { return pSum * 100 + dCard; }
inline int decSum(int encoded) { return encoded / 100; }
inline int decCard(int encoded) { return encoded % 100; }

//---------------------------------------------------------
// Destructor
//---------------------------------------------------------
inline AVL::~AVL() {
    clear(root);
}

//---------------------------------------------------------
// Clear tree recursively
//---------------------------------------------------------
inline void AVL::clear(Node* node) {
    if (node) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}

//---------------------------------------------------------
// Tree Height
//---------------------------------------------------------
inline int AVL::height(Node* temp) {
    if (!temp) return 0;
    int lh = height(temp->left);
    int rh = height(temp->right);
    return (lh > rh ? lh : rh) + 1;
}

//---------------------------------------------------------
// Balance Factor
//---------------------------------------------------------
inline int AVL::diff(Node* temp) {
    return temp ? height(temp->left) - height(temp->right) : 0;
}

//---------------------------------------------------------
// Left-Left Rotation
//---------------------------------------------------------
inline Node* AVL::llRot(Node* parent) {
    Node* temp = parent->left;
    parent->left = temp->right;
    temp->right = parent;
    return temp;
}

//---------------------------------------------------------
// Right-Right Rotation
//---------------------------------------------------------
inline Node* AVL::rrRot(Node* parent) {
    Node* temp = parent->right;
    parent->right = temp->left;
    temp->left = parent;
    return temp;
}

//---------------------------------------------------------
// Left-Right Rotation
//---------------------------------------------------------
inline Node* AVL::lrRot(Node* parent) {
    parent->left = rrRot(parent->left);
    return llRot(parent);
}

//---------------------------------------------------------
// Right-Left Rotation
//---------------------------------------------------------
inline Node* AVL::rlRot(Node* parent) {
    parent->right = llRot(parent->right);
    return rrRot(parent);
}

//---------------------------------------------------------
// Balance Tree
//---------------------------------------------------------
inline Node* AVL::bal(Node* temp) {
    int bf = diff(temp);
    if (bf > 1) {
        if (diff(temp->left) > 0)
            temp = llRot(temp);
        else
            temp = lrRot(temp);
    }
    else if (bf < -1) {
        if (diff(temp->right) < 0)
            temp = rrRot(temp);
        else
            temp = rlRot(temp);
    }
    return temp;
}

//---------------------------------------------------------
// Recursive Insert
//---------------------------------------------------------
inline Node* AVL::ins(Node* node, int val, char hint) {
    if (!node) {
        return new Node(val, hint);
    }
    else if (val < node->data) {
        node->left = ins(node->left, val, hint);
        node = bal(node);
    }
    else if (val > node->data) {
        node->right = ins(node->right, val, hint);
        node = bal(node);
    }
    else {
        node->hint = hint;
    }
    return node;
}

//---------------------------------------------------------
// Public Insert
//---------------------------------------------------------
inline void AVL::ins(int val, char hint) {
    root = ins(root, val, hint);
}

//---------------------------------------------------------
// Find node
//---------------------------------------------------------
inline Node* AVL::find(Node* node, int val) {
    if (!node || node->data == val)
        return node;
    
    if (val < node->data)
        return find(node->left, val);
    
    return find(node->right, val);
}

//---------------------------------------------------------
// Get strategy hint
//---------------------------------------------------------
inline char AVL::getHint(int pSum, int dCard) {
    int enc = encStr(pSum, dCard);
    Node* found = find(root, enc);
    
    if (found) {
        return found->hint;
    }
    
    if (pSum >= 17) return 's';
    if (pSum <= 8) return 'h';
    return 'h';
}

//---------------------------------------------------------
// Build strategy tree
//---------------------------------------------------------
inline void AVL::bldStr() {
    clear(root);
    root = nullptr;
    
    for (int dCard = 2; dCard <= 11; dCard++) {
        for (int pSum = 17; pSum <= 21; pSum++) {
            ins(encStr(pSum, dCard), 's');
        }
    }
    
    for (int dCard = 2; dCard <= 11; dCard++) {
        ins(encStr(11, dCard), 'd');
    }
    
    for (int dCard = 2; dCard <= 9; dCard++) {
        ins(encStr(10, dCard), 'd');
    }
    
    for (int dCard = 3; dCard <= 6; dCard++) {
        ins(encStr(9, dCard), 'd');
    }
    
    for (int pSum = 13; pSum <= 16; pSum++) {
        for (int dCard = 2; dCard <= 6; dCard++) {
            ins(encStr(pSum, dCard), 's');
        }
    }
    
    for (int dCard = 4; dCard <= 6; dCard++) {
        ins(encStr(12, dCard), 's');
    }
    
    for (int pSum = 12; pSum <= 16; pSum++) {
        for (int dCard = 7; dCard <= 11; dCard++) {
            ins(encStr(pSum, dCard), 'h');
        }
    }
}

//---------------------------------------------------------
// Display tree
//---------------------------------------------------------
inline void AVL::show(Node* ptr, int level) {
    if (ptr != nullptr) {
        show(ptr->right, level + 1);
        if (ptr == root) std::cout << "R -> ";
        for (int i = 0; i < level && ptr != root; i++) 
            std::cout << "     ";
        std::cout << decSum(ptr->data) << "vs" << decCard(ptr->data) 
             << ":" << ptr->hint;
        show(ptr->left, level + 1);
    }
}

//---------------------------------------------------------
// Inorder traversal
//---------------------------------------------------------
inline void AVL::inOrd(Node* node) {
    if (!node) return;
    inOrd(node->left);
    std::cout << decSum(node->data) << "vs" << decCard(node->data) 
         << ":" << node->hint << " ";
    inOrd(node->right);
}

#endif