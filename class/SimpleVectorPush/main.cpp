/*
 * File:   main.cpp
 * Author: Dr. Mark E. Lehr
 * Purpose: Timing analysis for pushing Objects into SimpleVector for increasing sizes
 */

//System Libraries
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <sstream>
#include <fstream> 
using namespace std;

//User Libraries
#include "Object.h"       // 2D Objects
#include "SimpleVector.h" // Simple Vector only works with Classes

int main(int argc, char** argv) {
    srand(static_cast<unsigned int>(time(0)));

    const int increments = 40;
    const int stepSize = 100;

    // Open CSV file for writing
    ofstream outFile("timing_results.csv");
    if (!outFile) {
        cerr << "Error opening file for writing!" << endl;
        return 1;
    }

    // Write CSV header
    outFile << "ArraySize,TimeSeconds\n";

    cout << "Timing analysis of pushing Objects into SimpleVector\n";

    for (int i = 1; i <= increments; i++) {
        int currentSize = i * stepSize;
        SimpleVector<Object> timingVector(Object(1)); // initialize vector

        clock_t start = clock();

        for (int j = 0; j < currentSize; j++) {
            int rSize = rand() % 10 + 1;
            Object c(rSize);
            timingVector.push(c);
        }

        clock_t end = clock();
        double elapsedSeconds = double(end - start) / CLOCKS_PER_SEC;

        cout << "Pushed " << currentSize << " Objects in " << elapsedSeconds << " seconds." << endl;

        // Write to CSV file
        outFile << currentSize << "," << elapsedSeconds << "\n";
    }

    outFile.close();
    cout << "Timing results saved to timing_results.csv\n";

    return 0;
}