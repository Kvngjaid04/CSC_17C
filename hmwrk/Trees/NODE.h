/* 
 * File:   node.h
 * Author: Ireoluwa Dairo
 * Created on May 27, 2025, 1:04 PM
 */

#ifndef NODE_H
#define NODE_H

struct node {
    int data;
    node* left;
    node* right;
    int height;
};

#endif