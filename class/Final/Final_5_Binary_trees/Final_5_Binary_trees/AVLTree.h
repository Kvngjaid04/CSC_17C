/* 
 * File:   AVLTree.h
 * Author: Ireoluwa Dairo
 * Created on May 27, 2025, 1:04 PM
 * modified for final
 */

#ifndef AVLTREE_H
#define AVLTREE_H
#include "node.h"
#include <algorithm>
using namespace std;

class AVLTree {
public:
    node* root; 
    int srchCnt;
    AVLTree() { root = nullptr; srchCnt = 0; }
    ~AVLTree() { dstry(root); }
    
    node* insert(node* n, char data) {
        if (!n) {
            node* newN = new node;
            newN->data = data;
            newN->left = nullptr;
            newN->right = nullptr;
            newN->height = 1;
            return newN;
        }
        
        if (data < n->data)
            n->left = insert(n->left, data);
        else if (data > n->data)
            n->right = insert(n->right, data);
        
        return bal(n);
    }
    
    bool search(node* n, char data) {
        srchCnt++;
        if (!n) return false;
        if (data == n->data) return true;
        if (data < n->data) return search(n->left, data);
        return search(n->right, data);
    }
    
    void reset() { srchCnt = 0; }

private:
    void dstry(node* n) {
        if (!n) return;  
        dstry(n->left);               
        dstry(n->right);              
        delete n;                     
    }
    
    int height(node* n) {
        if (!n) return 0;
        return max(height(n->left), height(n->right)) + 1;
    }
    
    int diff(node* n) {
        if (!n) return 0;
        return height(n->left) - height(n->right);
    }
    
    node* bal(node* temp) {
        int bFact = diff(temp);
        if (bFact > 1) {
            if (diff(temp->left) > 0)
                temp = llRot(temp);
            else
                temp = lrRot(temp);
        } else if (bFact < -1) {
            if (diff(temp->right) > 0)
                temp = rlRot(temp);
            else
                temp = rrRot(temp);
        }
        return temp;
    }
    
    node* llRot(node* parent) {
        node* temp = parent->left;
        parent->left = temp->right;
        temp->right = parent;
        return temp;
    }
    
    node* rrRot(node* parent) {
        node* temp = parent->right;
        parent->right = temp->left;
        temp->left = parent;
        return temp;
    }
    
    node* lrRot(node* parent) {
        node* temp = parent->left;
        parent->left = rrRot(temp);
        return llRot(parent);
    }
    
    node* rlRot(node* parent) {
        node* temp = parent->right;
        parent->right = llRot(temp);
        return rrRot(parent);
    }
};
#endif