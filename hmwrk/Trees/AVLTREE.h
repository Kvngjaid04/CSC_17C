/* 
 * File:   AVLTree.h
 * Author: Ireoluwa Dairo
 * Created on May 27, 2025, 1:04 PM
 */

#ifndef AVLTREE_H
#define AVLTREE_H

#include "node.h"
#include <iostream>
#include <algorithm>
using namespace std;

class AVLTree {
public:
    node* root; 
    AVLTree() { root = nullptr; }    //Constructor
    ~AVLTree() { dstry(root); }      //Destructor  
    
    //**************************************************************************
    //                            Insert Node with AVL Balancing
    //**************************************************************************
    node* insert(node* n, int data) {
        if (!n) {                              //Create new node
            node* newN = new node;
            newN->data = data;
            newN->left = nullptr;
            newN->right = nullptr;
            newN->height = 1;
            return newN;
        }
        
        if (data < n->data)                    //Insert left
            n->left = insert(n->left, data);
        else                                   //Insert right
            n->right = insert(n->right, data);
        
        return bal(n);                        //Balance after insertion
    }
    
    //**************************************************************************
    //                            Delete Node with AVL Balancing
    //**************************************************************************
    node* remove(node* n, int data) {
        if (n == NULL) return n;              //Node not found
        
        if (data < n->data)                   //Search left
            n->left = remove(n->left, data);
        else if (data > n->data)              //Search right
            n->right = remove(n->right, data);
        else {                                //Node found
            if (n->left == NULL || n->right == NULL) { //One or no child
                node* temp = n->left ? n->left : n->right;
                
                if (temp == NULL) {           //No child
                    temp = n;
                    n = NULL;
                } else {                      //One child
                    *n = *temp;
                }
                delete temp;
            } else {                          //Two children
                node* temp = minVal(n->right); //Find successor
                n->data = temp->data;         //Copy data
                n->right = remove(n->right, temp->data); //Delete successor
            }
        }
        
        if (n == NULL) return n;              //Tree had only one node
        
        return bal(n);                        //Balance after deletion
    }
    
    //**************************************************************************
    //                      In-order Output of Tree
    //**************************************************************************
    void inord(node* n) {
        if (n == NULL)
            return;
        inord(n->left);
        cout << n->data << "  ";
        inord(n->right);
    }
    
    //**************************************************************************
    //                      Pre-order Output of Tree
    //**************************************************************************
    void preord(node* n) {
        if (n == NULL)
            return;
        cout << n->data << "  ";
        preord(n->left);
        preord(n->right);
    }
    
    //**************************************************************************
    //                      Post-order Output of Tree
    //**************************************************************************
    void postrd(node* n) {
        if (n == NULL)
            return;
        postrd(n->left);
        postrd(n->right);
        cout << n->data << "  ";
    }
    
    //**************************************************************************
    //                            Level Order Traversal
    //**************************************************************************
    void level(node* root) {
        if (!root) return;                //Base case
        int h = height(root);             //Get tree height
        for (int i = 1; i <= h; i++) level(root, i); //Print each level
    }
    
    //**************************************************************************
    //                            Print Nodes at Given Level
    //**************************************************************************
    void level(node* root, int lvl) {
        if (!root) return;                //Base case
        if (lvl == 1)                     //Target level reached
            cout << root->data << " ";
        else {                            //Recurse down
            level(root->left, lvl - 1);   //Left subtree
            level(root->right, lvl - 1);  //Right subtree
        }
    }
        
    //**************************************************************************
    //                            Display Tree Structure
    //**************************************************************************
    void disp(node* n, int space) {
        if (!n) return;                       //Base case
        space += 10;                          //Increase distance
        disp(n->left, space);                 //Print left subtree first
        cout << endl;
        for (int i = 10; i < space; i++) cout << " "; //Print spaces
        cout << n->data;                      //Print current node
        disp(n->right, space);                //Print right subtree
    }

private:
    //**************************************************************************
    //                            Destroy Tree (Memory Cleanup)
    //**************************************************************************
    void dstry(node* n) {
        if (n == NULL) return;  
        dstry(n->left);               
        dstry(n->right);              
        delete n;                     
    }
    
    //**************************************************************************
    //                            Height of AVL Sub Trees
    //**************************************************************************
    int height(node* n) {
        if (!n) return 0;
        int lHt = height(n->left);
        int rHt = height(n->right);
        return max(lHt, rHt) + 1;
    }
    
    //**************************************************************************
    //                            Balance Factor of Node
    //**************************************************************************
    int diff(node* n) {
        if (!n) return 0;
        int lHt = height(n->left);
        int rHt = height(n->right);
        return lHt - rHt;
    }
    
    //**************************************************************************
    //                         Balancing of Sub Trees
    //**************************************************************************
    node* bal(node* temp) {
        int bFactor = diff(temp);
        if (bFactor > 1) {
            if (diff(temp->left) > 0)
                temp = llRot(temp);
            else
                temp = lrRot(temp);
        } else if (bFactor < -1) {
            if (diff(temp->right) > 0)
                temp = rlRot(temp);
            else
                temp = rrRot(temp);
        }
        return temp;
    }
    
    //**************************************************************************
    //                      Left-Left Rotations of Sub Trees
    //**************************************************************************
    node* llRot(node* parent) {
        node* temp = parent->left;
        parent->left = temp->right;
        temp->right = parent;
        return temp;
    }
    
    //**************************************************************************
    //                      Right-Right Rotations of Sub Trees
    //**************************************************************************
    node* rrRot(node* parent) {
        node* temp = parent->right;
        parent->right = temp->left;
        temp->left = parent;
        return temp;
    }
    
    //**************************************************************************
    //                      Left-Right Rotations of Sub Trees
    //**************************************************************************
    node* lrRot(node* parent) {
        node* temp = parent->left;
        parent->left = rrRot(temp);
        return llRot(parent);
    }
    
    //**************************************************************************
    //                      Right-Left Rotations of Sub Trees
    //**************************************************************************
    node* rlRot(node* parent) {
        node* temp = parent->right;
        parent->right = llRot(temp);
        return rrRot(parent);
    }
    
    //**************************************************************************
    //                            Find Minimum Value Node
    //**************************************************************************
    node* minVal(node* n) {
        while (n->left) n = n->left;          //Go to leftmost node
        return n;                             //Return minimum
    }
};

#endif