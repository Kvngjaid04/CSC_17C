/* 
 * File: sorting_analysis.cpp
 * Purpose: Analyze and compare bubble sort and selection sort with multiple array sizes
 */

//System Libraries
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>  // For file output
#include <vector>   // For storing array sizes
using namespace std;

//Global operation counters
int selOBOI = 0; // Operations before outer loop
int selOI = 0;   // Operations inside outer loop
int selOJ = 0;   // Operations inside inner loop
int selOS = 0;   // Operations inside swap

int bubOBOI = 0; // Operations before outer loop
int bubOI = 0;   // Operations inside outer loop
int bubOJ = 0;   // Operations inside inner loop
int bubOS = 0;   // Operations inside swap

//Function Prototypes
void fillAry(int [], int);
void copyAry(int [], int [], int);
void selSortOp(int [], int);  // Selection sort with operation counting
void bubSortOp(int [], int);  // Bubble sort with operation counting
void runAnalysis(vector<int> &arraySizes);

//Main Function
int main(int argc, char** argv) {
    //Set the random number seed
    srand(static_cast<unsigned int>(time(0)));
    
    // Create array of 40 different sizes from 100 to 4000
    vector<int> arraySizes;
    for(int i = 1; i <= 40; i++) {
        arraySizes.push_back(i * 1000);
    }
    
    // Run the analysis
    runAnalysis(arraySizes);
    
    cout << "Analysis complete. Data saved to sort_operations.csv" << endl;
    
    return 0;
}

// Run operational analysis for all array sizes
void runAnalysis(vector<int> &arraySizes) {
    // Create output file
    ofstream outFile("sort_operation1s.csv");
    
    // Write header
    outFile << "ArraySize,SelSort_OBOI,SelSort_OI,SelSort_OJ,SelSort_OS,SelSort_Total,";
    outFile << "BubSort_OBOI,BubSort_OI,BubSort_OJ,BubSort_OS,BubSort_Total" << endl;
    
    // For each array size
    for(size_t i = 0; i < arraySizes.size(); i++) {
        int size = arraySizes[i];
        
        // Create dynamic arrays to handle various sizes
        int *array = new int[size];
        int *backup = new int[size];
        
        // Fill array with random values
        fillAry(array, size);
        copyAry(backup, array, size);
        
        // Reset counters
        selOBOI = 0;
        selOI = 0;
        selOJ = 0;
        selOS = 0;
        bubOBOI = 0;
        bubOI = 0;
        bubOJ = 0;
        bubOS = 0;
        
        // Run selection sort with operation counting
        selSortOp(array, size);
        
        // Run bubble sort with operation counting
        bubSortOp(backup, size);
        
        // Calculate totals
        int selTotal = selOBOI + selOI + selOJ + selOS;
        int bubTotal = bubOBOI + bubOI + bubOJ + bubOS;
        
        // Write data to CSV
        outFile << size << "," 
                << selOBOI << "," << selOI << "," << selOJ << "," << selOS << "," << selTotal << ","
                << bubOBOI << "," << bubOI << "," << bubOJ << "," << bubOS << "," << bubTotal 
                << endl;
        
        // Display progress
        cout << "Completed analysis for array size " << size << endl;
        cout << "  Selection Sort Total: " << selTotal << endl;
        cout << "  Bubble Sort Total: " << bubTotal << endl;
        
        // Free dynamic memory
        delete[] array;
        delete[] backup;
    }
    
    outFile.close();
}

//Fill array with random numbers
void fillAry(int a[], int n) {
    for(int i=0; i<n; i++) {
        a[i] = rand() % (2147483647); // Full range of integers to avoid duplicates
    }
}

//Copy one array to another
void copyAry(int copyTo[], int source[], int n) {
    for(int i=0; i<n; i++) {
        copyTo[i] = source[i];
    }
}

//Selection sort with operation counting
void selSortOp(int a[], int n) {
    int indx, min;
    
    // Operations before the outer loop
    selOBOI++; // Initialize indx and min
    
    for(int pos=0; pos<n-1; pos++) {
        // Operations inside outer loop but before inner loop
        selOI += 3; // min=a[pos], indx=pos, and loop overhead
        min = a[pos];
        indx = pos;
        
        for(int i=pos+1; i<n; i++) {
            // Operations inside inner loop
            selOJ += 2; // Loop overhead and comparison
            
            if(a[i] < min) {
                selOJ += 2; // Assignment operations
                min = a[i];
                indx = i;
            }
        }
        
        // Operations for swap
        selOS += 2; // Two assignments for swap
        a[indx] = a[pos];
        a[pos] = min;
    }
}

//Bubble sort with operation counting
void bubSortOp(int a[], int n) {
    bool swap;
    
    bubOBOI++; // Declare bool swap
    
    do {
        bubOI += 2; // Set swap=false and loop overhead
        swap = false;
        
        for(int i=0; i<n-1; i++) {
            bubOJ += 2; // Loop overhead and comparison
            
            if(a[i] > a[i+1]) {
                bubOS += 4; // Three assignments for swap + setting swap=true
                int temp = a[i];
                a[i] = a[i+1];
                a[i+1] = temp;
                swap = true;
            }
        }
    } while(swap);
}