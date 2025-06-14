/* 
 * File:   Graph.h
 * Author: Ireoluwa
 * Created on June 10, 2025, 11:57 PM
 */

#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <list>
#include <queue>
#include <string>

// Graph structure for card relationships
struct Graph {
    std::vector<std::list<std::pair<int, int>>> adjList;  // list with weights
    std::vector<int> freq;                                // Card frequencies
};

// Graph function prototypes
void initGph(Graph&);                       // Initialize graph
void addEdge(Graph&, int, int, int = 1);    // Add weighted edge between cards
void showRel(Graph&);                       // Show relationships
int dijkstra(Graph&, int, int);             // Dijkstra's shortest path
int winProb(Graph&, std::list<int>&, int);  // Win probability calculator
int pathLen(Graph&, int, int);              // Simple BFS path length

#endif