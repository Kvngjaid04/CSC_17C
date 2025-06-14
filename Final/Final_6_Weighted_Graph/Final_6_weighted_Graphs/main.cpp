/* 
 * File:   main.cpp
 * Author: Ireoluwa
 * Created on June 9, 2025, 10:31 AM
 */

#include <cstdlib>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string>
using namespace std;

//User Libraries

//Global Constants - Mathematical, Scientific, Conversions
const int INF = 999999;
const int MAXV = 7;
string cities[] = {"SFO", "BOS", "ORD", "JFK", "DFW", "MIA", "LAX"};

//Higher Dimensions go here. No Variables
struct Edge {
    int u, v, wt;
    bool operator<(const Edge& other) const {
        return wt < other.wt;
    }
};

//Function Prototypes
int dijkst(vector<vector<int>>& adj, int start, int end, vector<int>& path);
int kruskal(vector<Edge>& edges, int n);
int find(int parent[], int x);
void unite(int parent[], int rank[], int x, int y);
void printPath(vector<int>&);
void OuTPUT(vector<vector<int>>& adj, vector<Edge>& edges);


//Execution Begins here

int main(int argc, char** argv) {
    //Setting the random number seed

    //Declaring Variables
    vector<vector<int>> adj(MAXV, vector<int>(MAXV, INF));
    vector<Edge> edges;
    
    //Initialize Variables
    // Vertex mapping: SFO=0, BOS=1, ORD=2, JFK=3, DFW=4, MIA=5, LAX=6
    // Add edges 
    int edgeData[][3] = {
        {0, 1, 2703}, // SFO-BOS
        {0, 2, 1847}, // SFO-ORD
        {2, 1, 868},  // ORD-BOS
        {2, 3, 743},  // ORD-JFK
        {3, 1, 189},  // JFK-BOS
        {0, 4, 1465}, // SFO-DFW
        {4, 2, 803},  // DFW-ORD
        {4, 5, 1124}, // DFW-MIA
        {5, 3, 1093}, // MIA-JFK
        {5, 1, 1257}, // MIA-BOS
        {0, 6, 338},  // SFO-LAX
        {6, 4, 1234}, // LAX-DFW
        {6, 5, 2341}  // LAX-MIA
    };
     int numEdg = 13;
     
    //Processing/Mapping Inputs to Outputs
     for(int i = 0; i < numEdg; i++) {
        int u = edgeData[i][0];
        int v = edgeData[i][1];
        int w = edgeData[i][2];
        
        adj[u][v] = w;
        adj[v][u] = w;
        
        edges.push_back({u, v, w});
    }
     
     // Set diagonal to 0
    for(int i = 0; i < MAXV; i++) {
        adj[i][i] = 0;
    }
     
    //Displaying Input/Output Information
     OuTPUT(adj, edges);
     
    //Exiting stage left/right
    return 0;
}

void printPath(vector<int>& path) {
    for(int i = 0; i < (int)path.size(); i++) {
        cout << cities[path[i]];
        if(i < (int)path.size() - 1) {
            cout << " -> ";
        }
    }
}

// Dijkstra's algorithm
int dijkst(vector<vector<int>>& adj, int start, int end, vector<int>& path) {
    vector<int> dist(MAXV, INF);
    vector<bool> visit(MAXV, false);
    vector<int> parent(MAXV, -1);
    
    dist[start] = 0;
    
    for(int i = 0; i < MAXV; i++) {
        int u = -1;
        for(int v = 0; v < MAXV; v++) {
            if(!visit[v] && (u == -1 || dist[v] < dist[u])) {
                u = v;
            }
        }
        
        if(dist[u] == INF) break;
        visit[u] = true;
        
        for(int v = 0; v < MAXV; v++) {
            if(adj[u][v] != INF) {
                if(dist[u] + adj[u][v] < dist[v]) {
                    dist[v] = dist[u] + adj[u][v];
                    parent[v] = u;
                }
            }
        }
    }
    
    // Build path
    path.clear();
    int curr = end;
    while(curr != -1) {
        path.push_back(curr);
        curr = parent[curr];
    }
    reverse(path.begin(), path.end());
    
    return dist[end];
}

// Kruskal's algorithm
int kruskal(vector<Edge>& edges, int n) {
    sort(edges.begin(), edges.end());
    
    int parent[MAXV];
    int rank[MAXV];
    
    for(int i = 0; i < n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }
    
    int mstWt = 0;
    int edgeCnt = 0;
    
    for(Edge& e : edges) {
        if(find(parent, e.u) != find(parent, e.v)) {
            unite(parent, rank, e.u, e.v);
            mstWt += e.wt;
            edgeCnt++;
            
            if(edgeCnt == n - 1) break;
        }
    }
    
    return mstWt;
}

// Find helper functions
int find(int parent[], int x) {
    if(parent[x] != x) {
        parent[x] = find(parent, parent[x]);
    }
    return parent[x];
}

void unite(int parent[], int rank[], int x, int y) {
    int px = find(parent, x);
    int py = find(parent, y);
    
    if(rank[px] < rank[py]) {
        parent[px] = py;
    } else if(rank[px] > rank[py]) {
        parent[py] = px;
    } else {
        parent[py] = px;
        rank[px]++;
    }
}

// OUTPUT function
void OuTPUT(vector<vector<int>>& adj, vector<Edge>& edges) {
    // a) ORD to LAX (ORD=2, LAX=6)
    vector<int> pathA;
    int distA = dijkst(adj, 2, 6, pathA);
    cout << "a) Shortest distance ORD to LAX: " << distA << endl;
    cout << "       Path: ";
    printPath(pathA);
    cout << endl << endl;
    
    // b) JFK to SFO (JFK=3, SFO=0)
    vector<int> pathB;
    int distB = dijkst(adj, 3, 0, pathB);
    cout << "b) Shortest distance JFK to SFO: " << distB << endl;
    cout << "       Path: ";
    printPath(pathB);
    cout << endl << endl;
    
    // c) Minimum Spanning Tree
    int mstWt = kruskal(edges, MAXV);
    cout << "c) Minimum Spanning Tree weight: " << mstWt << endl;
}