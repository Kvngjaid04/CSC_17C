/* 
 * File:   Graph.cpp
 * Author: Ireoluwa
 * Created on June 10, 2025, 8:54 PM
 */

#include "Graph.h"
#include "Deck.h"
#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

// Graph functions for card relationships
void initGph(Graph& g) {
    g.adjList.resize(14);  // Cards 1-13
    g.freq.resize(14, 0);  // Initialize frequencies
}

void addEdge(Graph& g, int card1, int card2, int weight) {
    if (card1 > 0 && card1 < 14 && card2 > 0 && card2 < 14) {
        g.adjList[card1].push_back({card2, weight});
        g.adjList[card2].push_back({card1, weight}); // Undirected graph
        g.freq[card1]++;
        g.freq[card2]++;
    }
}

void showRel(Graph& g) {
    cout << "\nCard Relationships:\n";
    for (int i = 1; i < 14; i++) {
        if (!g.adjList[i].empty()) {
            cout << getVal(i) << " connects to: ";
            for (auto& edge : g.adjList[i]) {
                cout << getVal(edge.first) << "(w:" << edge.second << ") ";
            }
            cout << "\n";
        }
    }
}

// Dijkstra's shortest path algorithm
int dijkstra(Graph& g, int start, int end) {
    if (start == end) return 0;
    if (start < 1 || start >= 14 || end < 1 || end >= 14) return -1;
    
    // Distance array initialized to infinity
    vector<int> dist(14, INT_MAX);
    
    // Priority queue: {distance, node}
    priority_queue<pair<int, int>, vector<pair<int, int>>, 
                    greater<pair<int, int>>> pq;
    
    // Initialize starting node
    dist[start] = 0;
    pq.push({0, start});
    
    while (!pq.empty()) {
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();
        
        // If we reached the destination
        if (u == end) {
            return dist[end];
        }
        
        // Skip if we already found a better path
        if (d > dist[u]) continue;
        
        // Check all neighbors
        for (auto& edge : g.adjList[u]) {
            int v = edge.first;
            int weight = edge.second;
            
            // Relaxation step
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }
    
    return -1; // No path found
}

// Win Probability Calculator using Dijkstra
int winProb(Graph& g, list<int>& pHand, int dCard) {
    if (pHand.empty()) return 50; // Default probability
    
    int totalProb = 0;
    int cardCount = 0;
    
    for (auto card : pHand) {
        // Distance from your cards to dealer's card
        int threat = dijkstra(g, card, dCard);
        
        // Convert distance to probability 
        if (threat > 0) {
            int prob = max(20, 80 - (threat * 10));  // 20-80% range
            totalProb += prob;
        } else {
            totalProb += 50; // Default if no path
        }
        cardCount++;
    }
    
    int avgProb = cardCount > 0 ? totalProb / cardCount : 50;
    return min(95, max(5, avgProb)); // Keep between 5-95%
}

int pathLen(Graph& g, int start, int end) {
    if (start == end) return 0;
    
    // Simple BFS for unweighted shortest path
    queue<int> q;
    vector<bool> visited(14, false);
    vector<int> dist(14, -1);
    
    q.push(start);
    visited[start] = true;
    dist[start] = 0;
    
    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        
        for (auto& edge : g.adjList[curr]) {
            int next = edge.first;
            if (!visited[next]) {
                visited[next] = true;
                dist[next] = dist[curr] + 1;
                q.push(next);
                
                if (next == end) {
                    return dist[next];
                }
            }
        }
    }
    
    return -1;  // No path found
}