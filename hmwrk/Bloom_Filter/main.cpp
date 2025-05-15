/* 
 * File:   main.cpp
 * Author: Ireoluwa
 * Created on May 14, 2025, 7:55 PM
 */

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

//User Libraries

//Global Constants - Mathematical, Scientific, Conversions
const int BITSIZE = 14;

//Higher Dimensions go here. No Variables

//Function Prototypes
int hash1(const string &s);                  // First hash function
int hash2(const string &s);                  // Second hash function
void showVec(const vector<bool> &vec);       // Display bit vector
bool inSet(const string &w, const vector<string> &data);    // membership check
int fpRate(int n);                           // false positive rate

//Execution Begins here

int main(int argc, char** argv) {
    //Setting the random number seed
    //Declaring Variables
    vector<bool> vec(BITSIZE, false);
    vector<string> data;                        // Store added words for check
    string word;                                // User input word
    int h1, h2;                                 // Hash values
    
    //Initialize Variables
    //Displaying Input/Output Information
    cout << "Bloom Filter \n\n";
    
    //Processing/Mapping Inputs to Outputs
    // Loop to add words to bloom filter
        while (true) {
        cout << "Enter word (or 'done'): ";
        getline(cin, word);
        if (word == "done") break;

        // Compute hashes
        h1 = hash1(word), h2 = hash2(word);

        // Set bits in bit vector
        vec[h1] = true, vec[h2] = true;

        // Save word for exact membership checking
        data.push_back(word);

        // Show hash values and current bit vector
        cout << "hash1: " << h1 << "\nhash2: " << h2 << "\n", showVec(vec);}

    // Loop to test words for membership
    while (true) {
        cout << "\nTest an element for membership (or 'exit'): ";
        getline(cin, word);
        if (word == "exit") break;
        h1 = hash1(word), h2 = hash2(word);
        cout << "hash1: " << h1 << "\nhash2: " << h2 << endl;

        // Check if bits are set in bloom filter
        if (vec[h1] && vec[h2])                       // Possible false positive
            cout << "Is the word in set? " << 
                (inSet(word, data) ? "YES\n" : "MAYBE\n");
        else
            cout << "Is the word in set? NO\n";
        
        // Show estimated false positive rate
        cout << "False positive chance: " << fpRate(data.size()) << "%\n";}
    //Exiting stage left/right
return 0;}

// Hash function 1: polynomial rolling hash mod bit size
int hash1(const string &s) {
    int val = 0, p = 31;
    for (char c : s) val = (val * p + c) % BITSIZE;
    return val;
}

// Hash function 2: XOR-based hash mod bit size
int hash2(const string &s) {
    int val = 0;
    for (char c : s) val ^= (val << 3) + (val >> 1) + c;
    return val % BITSIZE;
}

// Display the bit vector
void showVec(const vector<bool> &vec) {
    cout << "\nBit vector:\n";
    for (int i = 0; i < vec.size(); i++) cout << vec[i] << " ";
    cout << endl;
}

// Check  membership in stored data vector
bool inSet(const string &w, const vector<string> &data) {
    for (int i = 0; i < data.size(); i++) {
        if (data[i] == w) return true;
    }
    return false;
}
// Approximate false positive rate based on number of inserted elements
int fpRate(int n) {
    float m = BITSIZE;  // Size of bit vector
    float k = 2;        // Number of hash functions
    
    // Standard formula for Bloom filter false positive probability:
    // (1 - e^(-k*n/m))^k
    float fillRatio = 1.0 - exp(-k * n / m);
    float probability = pow(fillRatio, k) * 100;
    
    return static_cast<int>(probability);
}
