/* 
 * File:   node.h
 * Author: Ireoluwa Dairo
 * Created on May 27, 2025, 1:04 PM
 * modified for final
 */

#ifndef NODE_H
#define NODE_H
#include <string>
using namespace std;

struct node {
    char data;
    node* left;
    node* right;
    int height;
};

struct HNode {
    string initls;
    HNode* next;
    HNode(string init) : initls(init), next(nullptr) {} 
};
#endif