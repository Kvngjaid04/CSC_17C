/* Author: Ireoluwa
 * file: avltree.h
 */
#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>
#include "BNTnode.h"
using namespace std;

class AVLTree {
public:
    BNTnode* root;

    AVLTree() { root = nullptr; }
    ~AVLTree();

    int height(BNTnode*);             // Tree height
    int diff(BNTnode*);               // Balance factor
    BNTnode* ll_rotation(BNTnode*);   // Left-Left rotation
    BNTnode* rr_rotation(BNTnode*);   // Right-Right rotation
    BNTnode* lr_rotation(BNTnode*);   // Left-Right rotation
    BNTnode* rl_rotation(BNTnode*);   // Right-Left rotation
    BNTnode* balance(BNTnode*);       // Balance node
    BNTnode* insert(BNTnode*, int, char);   // Recursive insert with hint
    void insert(int, char);           // Public insert wrapper
    BNTnode* find(BNTnode*, int);     // Find node
    char getHint(int pSum, int dCard); // Get strategy hint
    void bldStrt();                   // Build strategy tree
    void clear(BNTnode*);             // Clear tree recursively
    void display(BNTnode*, int);      // Display rotated tree
    void inorder(BNTnode*);           // Inorder traversal
};

// Implementation
//---------------------------------------------------------
// Destructor
//---------------------------------------------------------
inline AVLTree::~AVLTree() {
    clear(root);
}

//---------------------------------------------------------
// Clear tree recursively
//---------------------------------------------------------
inline void AVLTree::clear(BNTnode* node) {
    if (node) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}

//---------------------------------------------------------
// Tree Height
//---------------------------------------------------------
inline int AVLTree::height(BNTnode* temp) {
    if (!temp) return 0;
    int lh = height(temp->left);
    int rh = height(temp->right);
    return max(lh, rh) + 1;
}

//---------------------------------------------------------
// Balance Factor
//---------------------------------------------------------
inline int AVLTree::diff(BNTnode* temp) {
    return temp ? height(temp->left) - height(temp->right) : 0;
}

//---------------------------------------------------------
// Left-Left Rotation
//---------------------------------------------------------
inline BNTnode* AVLTree::ll_rotation(BNTnode* parent) {
    BNTnode* temp = parent->left;
    parent->left = temp->right;
    temp->right = parent;
    return temp;
}

//---------------------------------------------------------
// Right-Right Rotation
//---------------------------------------------------------
inline BNTnode* AVLTree::rr_rotation(BNTnode* parent) {
    BNTnode* temp = parent->right;
    parent->right = temp->left;
    temp->left = parent;
    return temp;
}

//---------------------------------------------------------
// Left-Right Rotation
//---------------------------------------------------------
inline BNTnode* AVLTree::lr_rotation(BNTnode* parent) {
    parent->left = rr_rotation(parent->left);
    return ll_rotation(parent);
}

//---------------------------------------------------------
// Right-Left Rotation
//---------------------------------------------------------
inline BNTnode* AVLTree::rl_rotation(BNTnode* parent) {
    parent->right = ll_rotation(parent->right);
    return rr_rotation(parent);
}

//---------------------------------------------------------
// Balance Tree
//---------------------------------------------------------
inline BNTnode* AVLTree::balance(BNTnode* temp) {
    int bf = diff(temp);
    if (bf > 1) {
        if (diff(temp->left) > 0)
            temp = ll_rotation(temp);
        else
            temp = lr_rotation(temp);
    }
    else if (bf < -1) {
        if (diff(temp->right) < 0)
            temp = rr_rotation(temp);
        else
            temp = rl_rotation(temp);
    }
    return temp;
}

//---------------------------------------------------------
// Recursive Insert with hint
//---------------------------------------------------------
inline BNTnode* AVLTree::insert(BNTnode* node, int val, char hint) {
    if (!node) {
        return new BNTnode(val, hint);
    }
    else if (val < node->data) {
        node->left = insert(node->left, val, hint);
        node = balance(node);
    }
    else if (val > node->data) {
        node->right = insert(node->right, val, hint);
        node = balance(node);
    }
    else {
        // Update hint for existing node
        node->hint = hint;
    }
    return node;
}

//---------------------------------------------------------
// Public Insert Wrapper
//---------------------------------------------------------
inline void AVLTree::insert(int val, char hint) {
    root = insert(root, val, hint);
}

//---------------------------------------------------------
// Find node
//---------------------------------------------------------
inline BNTnode* AVLTree::find(BNTnode* node, int val) {
    if (!node || node->data == val)
        return node;
    
    if (val < node->data)
        return find(node->left, val);
    
    return find(node->right, val);
}

//---------------------------------------------------------
// Get strategy hint - FIXED VERSION
//---------------------------------------------------------
inline char AVLTree::getHint(int pSum, int dCard) {
    int encoded = encodeStrat(pSum, dCard);
    BNTnode* found = find(root, encoded);
    
    if (found) {
        return found->hint;
    }
    
    // IMPROVED Default strategy rules if not found in tree
    // Handle obvious cases first
    if (pSum >= 21) return 's';         // Always stand on 21+
    if (pSum >= 17) return 's';         // Always stand on hard 17+
    if (pSum <= 8) return 'h';          // Always hit on 8 or less
    
    // Double down opportunities
    if (pSum == 11) return 'd';         // Always double on 11
    if (pSum == 10 && dCard <= 9) return 'd'; // Double 10 vs 2-9
    if (pSum == 9 && dCard >= 3 && dCard <= 6) return 'd'; // Double 9 vs 3-6
    
    // Basic strategy for standing/hitting
    if (pSum >= 17) return 's';         // Stand on 17+
    if (pSum >= 13 && dCard <= 6) return 's';  // Stand on 13-16 vs weak dealer
    if (pSum == 12 && dCard >= 4 && dCard <= 6) return 's'; // Stand 12 vs 4-6
    
    // Default to hit for everything else
    return 'h';
}

//---------------------------------------------------------
// Build comprehensive strategy tree - EXPANDED VERSION
//---------------------------------------------------------
inline void AVLTree::bldStrt() {
    // Clear any existing data
    clear(root);
    root = nullptr;
    
    // STANDING strategies (17+ always stand)
    for (int dCard = 2; dCard <= 11; dCard++) {
        for (int pSum = 17; pSum <= 21; pSum++) {
            insert(encodeStrat(pSum, dCard), 's');
        }
    }
    
    // DOUBLING strategies
    // Double on 11 vs any dealer card
    for (int dCard = 2; dCard <= 11; dCard++) {
        insert(encodeStrat(11, dCard), 'd');
    }
    
    // Double on 10 vs 2-9
    for (int dCard = 2; dCard <= 9; dCard++) {
        insert(encodeStrat(10, dCard), 'd');
    }
    
    // Double on 9 vs 3-6
    for (int dCard = 3; dCard <= 6; dCard++) {
        insert(encodeStrat(9, dCard), 'd');
    }
    
    // STANDING on stiff hands vs weak dealer
    // Stand 13-16 vs 2-6
    for (int pSum = 13; pSum <= 16; pSum++) {
        for (int dCard = 2; dCard <= 6; dCard++) {
            insert(encodeStrat(pSum, dCard), 's');
        }
    }
    
    // Stand 12 vs 4-6
    for (int dCard = 4; dCard <= 6; dCard++) {
        insert(encodeStrat(12, dCard), 's');
    }
    
    // HITTING strategies (everything else defaults to hit in getHint)
    // Hit hard totals vs strong dealer cards
    for (int pSum = 12; pSum <= 16; pSum++) {
        for (int dCard = 7; dCard <= 11; dCard++) {
            insert(encodeStrat(pSum, dCard), 'h');
        }
    }
    
    // Hit 12 vs 2,3,7+
    insert(encodeStrat(12, 2), 'h');
    insert(encodeStrat(12, 3), 'h');
    for (int dCard = 7; dCard <= 11; dCard++) {
        insert(encodeStrat(12, dCard), 'h');
    }
    
    cout << "Strategy tree built with comprehensive basic strategy rules!\n";
}

//---------------------------------------------------------
// Tree Display
//---------------------------------------------------------
inline void AVLTree::display(BNTnode* ptr, int level) {
    if (ptr != nullptr) {
        display(ptr->right, level + 1);
        cout << endl;
        if (ptr == root) cout << "R -> ";
        for (int i = 0; i < level && ptr != root; i++) cout << "     ";
        cout << decodeSum(ptr->data) << "vs" << decodeCard(ptr->data) 
             << ":" << ptr->hint;
        display(ptr->left, level + 1);
    }
}

//---------------------------------------------------------
// Inorder Traversal
//---------------------------------------------------------
inline void AVLTree::inorder(BNTnode* node) {
    if (!node) return;
    inorder(node->left);
    cout << decodeSum(node->data) << "vs" << decodeCard(node->data) 
         << ":" << node->hint << " ";
    inorder(node->right);
}

#endif // AVLTREE_H