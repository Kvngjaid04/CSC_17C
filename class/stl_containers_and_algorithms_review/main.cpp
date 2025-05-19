/* 
 * File:   main.cpp
 * Author: Ireoluwa
 * Created on April 24, 2025, 3:48 PM
 */

#include <cstdlib>
#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// User Libraries

// Global Constants - Mathematical, Scientific, Conversions

// Higher Dimensions go here. No Variables

// Function Prototypes
bool comp(int a, int b); // For sorting
void filList(list<int>& lst, int size);
void prntLst(const list<int>& lst, int groupSize = 5);
void fmof(const list<int>& lst); //find Multiples Of Five
void fmammof(const list<int>& lst); // Find min and max multiples of 5


// Execution Begins here
int main(int argc, char** argv) {
    const int SIZE = 100;
    list<int> myList;

    srand(time(0));

    filList(myList, SIZE);

    // Sorting the list in descending order (using Sort algorithm)
    myList.sort(comp);

    cout << "Sorted list (groups of 5):\n\n";
    prntLst(myList);
    
    // Track unique numbers using set
    set<int> uniqueNums(myList.begin(), myList.end());
    cout << "\nThere are " << uniqueNums.size() << " unique numbers "
            "in the list." << endl;

    cout << "\nMultiples of 5 found:\n";
    fmof(myList);
    cout<<endl;
    
     // Find min and max multiples of 5 (using Min and Max algorithms)
    fmammof(myList);
    return 0;
}
 
// Function Definitions

// Sort in descending order
bool comp(int a, int b) {
    return a > b;
}

// Fills the list with random numbers from 1 to 100 (using List container)
void filList(list<int>& lst, int size) {
    for (int i = 0; i < size; ++i) {
        lst.push_back(rand() % 100 + 1);
    }
}

// Print the list in groups of 5 (using List container)
void prntLst(const list<int>& lst, int groupSize) {
    int count = 0;
    for (auto val : lst) {
        cout << setw(4) << val;
        if (++count % groupSize == 0) cout << endl;
    }
}

// Search and print all multiples of 5 (using List container)
void fmof(const list<int>& lst) {
    for (auto it = lst.begin(); it != lst.end(); ++it) {
        if (*it % 5 == 0) {
            cout << *it << " found at position: "
                << distance(lst.begin(), it) + 1 << endl;
            // Add 1 to the position
        }
    } 
}

void fmammof(const list<int>& lst) {
    // Filter out non-multiples of 5 first
    list<int> multiplesOf5;
    copy_if(lst.begin(), lst.end(), back_inserter(multiplesOf5),
            [](int x) { return x % 5 == 0; });
    
    if (multiplesOf5.empty()) {
        cout << "No multiples of 5 found." << endl;
        return;
    }
    
    // Find min and max multiples of 5 (using Min and Max algorithms)
    auto minIt = min_element(multiplesOf5.begin(), multiplesOf5.end());
    auto maxIt = max_element(multiplesOf5.begin(), multiplesOf5.end());

    int minVal = *minIt;
    int maxVal = *maxIt;

    cout << "Minimum multiple of 5: " << minVal << endl;
    cout << "Maximum multiple of 5: " << maxVal << endl;

     // Create a map to associate values with strings (using Map container)
     cout << "\nMapped Output (using map):\n";
    map<int, string> msgMap;
    msgMap[minVal] = "Hello";
    msgMap[maxVal] = "World";

    for (auto m : msgMap) {
        cout << m.first << " => " << m.second << endl;
    }
    
     // Repeat using pair (using Pair container)
    cout << "\nPaired Output (using pair):\n";
    pair<int, string> helloPair = {minVal, "Hello"};
    pair<int, string> worldPair = make_pair(maxVal, "World");

    cout << helloPair.first << " => " << helloPair.second << endl;
    cout << worldPair.first << " => " << worldPair.second << endl;
}
