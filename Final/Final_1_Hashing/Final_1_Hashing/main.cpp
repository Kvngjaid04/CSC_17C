/* 
 * File:   main.cpp
 * Author: Ireoluwa
 * Created on June 6, 2025, 1:01 PM
 */
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <ctime>
using namespace std;

//User Libraries
struct Node {
    string initls;  // Stores 3-letter initials
    Node* next;     // Pointer to next node in linked list
    Node(string init) : initls(init), next(nullptr) {} 
};

//Global Constants - Mathematical, Scientific, Conversions
const int SIZE = 512;   // Hash table size (number of slots)
const int TOTAL = 512; // Number of random initials to generate and insert

//Function Prototypes
int  Phhash(string initls);               // Hash function for 3-letter initials
void insert(Node* table[], string initls);    // Insert initials into hash table
void genRand(Node* table[]);
void stats(Node* table[]);
int phneMap(char c);    // Map character to phone keypad digit

//Execution Begins here
int main(int argc, char** argv) {
    //Setting the random number seed
    srand(time(0));
    
    //Declaring Variables
    Node* table[SIZE];
    
    //Initialize Variables
    for(int i = 0; i < SIZE; i++) {
        table[i] = nullptr;
    }
    
    //Processing/Mapping Inputs to Outputs
    genRand(table);
    
    //Displaying Input/Output Information
    cout << "Hash Table Statistics for " << TOTAL << " initials:\n";
    cout << "Table size: " << SIZE << "\n\n";
    stats(table);
    
    //Exiting stage left/right
    return 0;
}

// Function to map uppercase letter to phone keypad digit
int phneMap(char c) {           
    if(c >= 'A' && c <= 'C') return 2;
    if(c >= 'D' && c <= 'F') return 3;
    if(c >= 'G' && c <= 'I') return 4;
    if(c >= 'J' && c <= 'L') return 5;
    if(c >= 'M' && c <= 'O') return 6;
    if(c >= 'P' && c <= 'S') return 7;
    if(c >= 'T' && c <= 'V') return 8;
    if(c >= 'W' && c <= 'Z') return 9;
    return 0;
}

// Hash function using phone keypad values 
int Phhash(string initls) {
    int a = phneMap(initls[0]);
    int b = phneMap(initls[1]);
    int c = phneMap(initls[2]);
    //add weights to each position to avoid collisions from same letters in 
    //different orders
    //subtract 2 to normalize phone digits to 0-7 range for better distribution
    return ((a-2) * 64 + (b-2) * 8 + (c-2)) % SIZE; 
}


// Insert initials into hash table at index from hash function
void insert(Node* table[], string initls) {
    int index = Phhash(initls);
    Node* newNode = new Node(initls);
    newNode->next = table[index];
    table[index] = newNode;
}

// Generate TOTAL random 3-letter initials and insert into hash table
void genRand(Node* table[]) {
    for(int i = 0; i < TOTAL; i++) {
        string initls = "";
        for(int j = 0; j < 3; j++) {
            char c = 'A' + rand() % 26;
            initls += c;
        }
        insert(table, initls);
    }
}

void stats(Node* table[]) {
    int counts[20] = {0}; // Count buckets
    int maxColl = 0;
    int empty = 0;
    
    for(int i = 0; i < SIZE; i++) {
        int count = 0;
        Node* curr = table[i];
        
        while(curr != nullptr) {
            count++;
            curr = curr->next;
        }
        
        if(count == 0) empty++;
        if(count > maxColl) maxColl = count;
        if(count < 20) counts[count]++;
    }
    
    // Add this to the end of your stats() function:
cout << "Theoretical vs Actual Comparison:\n";
cout << "Expected (Poisson) vs Actual:\n";
cout << "0 elements: 188 vs " << empty << "\n";
cout << "1 element:  188 vs " << counts[1] << "\n";
cout << "2 elements:  94 vs " << counts[2] << "\n";
cout << "3 elements:  32 vs " << counts[3] << "\n";
cout << "4 elements:   8 vs " << counts[4] << "\n";
cout << "5 elements:   2 vs " << counts[5] << "\n";
cout << "6+ elements:  0 vs " << (counts[6]+counts[7]+counts[8]) << "\n";
cout << "maximum collisions: " << maxColl<< "\n";
cout << "Load factor: " << (float)TOTAL/SIZE << "\n";
}