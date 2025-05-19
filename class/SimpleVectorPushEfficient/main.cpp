/*
 * File:   main.cpp
 * Author: Dr. Mark E. Lehr
 * Purpose:  Test out push values onto simple vector
 *           with a very complex object
 *           Note:  This simple vector only works with objects
 *           Also overloading the == operator in this version of Object
 */

//System Libraries
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <sstream>
#include <fstream>      // For file output
using namespace std;

//User Libraries
#include "Object.h"       //2D Objects
#include "SimpleVector.h" //Simple Vector only works with Classes

int main(int argc, char** argv) {
    //Set the random number seed
    srand(static_cast<unsigned int>(time(0)));
    
    //Test an object
    Object a(3), b(4);
    
    //Test an object by populating the simple vector and print
    SimpleVector<Object> svp(a);
    cout << "Simple Vector Object Size = " << svp.mxSize() << svp[svp.size() - 1];
    
    //Push an Object and printout the last object
    svp.push(b);
    cout << "Simple Vector Push Size = " << svp.mxSize() << svp[svp.size() - 1];
    
    //Fill the simple vector with 100 randomly sized 2D Array Objects and
    //print the last one
    for (int i = 0; i < 100; i++) {
        int rSize = rand() % 10;
        Object c(rSize);
        svp.push(c);
    }
    cout << "Max Size and Size of the Simple Vector = "
         << svp.mxSize() << " " << svp.size() << endl;
    cout << "The last object in the Vector is " << endl;
    cout << svp[svp.size() - 1];
    
    //Create another simple vector by copy constructor
    SimpleVector<Object> csvp(svp);
    cout << "Max Size and Size of the Copy Constructed Simple Vector = "
         << csvp.mxSize() << " " << csvp.size() << endl;
    cout << "The last object in the Vector is " << endl;
    cout << csvp[csvp.size() - 1];
 
    //Utilize a simple integer Simple Vector
    int size = 50;
    SimpleVector<Object> svi(size);
    cout << "Last 2 values of the Simple Vector" << endl;
    cout << "The Max Size and Size = "
         << svi.mxSize() << " " << svi.size() << endl
         << svi[svi.size() - 2] << svi[svi.size() - 1];

    // ----------- Timing Analysis Section -----------

    const int increments = 40;
    const int stepSize = 100;

    ofstream outFile("timing_results.csv");
    if (!outFile) {
        cerr << "Error opening file for writing!" << endl;
        return 1;
    }

    // CSV Header
    outFile << "ArraySize,TimeSeconds\n";

    cout << "\nTiming analysis of pushing Objects into SimpleVector\n";

    for (int i = 1; i <= increments; i++) {
        int currentSize = i * stepSize;
        SimpleVector<Object> timingVector(Object(1)); // initialize vector with 1 Object

        clock_t start = clock();

        for (int j = 0; j < currentSize; j++) {
            int rSize = rand() % 10 + 1; // random size 1 to 10
            Object c(rSize);
            timingVector.push(c);
        }

        clock_t end = clock();
        double elapsedSeconds = double(end - start) / CLOCKS_PER_SEC;

        cout << "Pushed " << currentSize << " Objects in " << elapsedSeconds << " seconds." << endl;

        outFile << currentSize << "," << elapsedSeconds << "\n";
    }

    outFile.close();
    cout << "Timing results saved to timing_results.csv\n";

    //Exit
    return 0;
}
