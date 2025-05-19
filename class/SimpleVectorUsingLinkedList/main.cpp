/*
 * File:   main.cpp
 * Author: Dr. Mark E. Lehr
 * Purpose:  Test out push values onto simple vector
 *           with a very complex object
 *           Note:  This simple vector only works with objects
 *           Also overloading the == operator in this version of Object
 *           Simple Vector using Linked List
 */

//System Libraries
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <sstream>
#include <fstream>    // For file output
using namespace std;

//User Libraries
#include "Object.h"       //2D Object
#include "SimpleVector.h" //Simple Vector only works with Classes

//Global Constants

//Execution Begins Here!
int main(int argc, char** argv) {
    //Set the random number seed
    srand(static_cast<unsigned int>(time(0)));
    
    //Test an object
    Object a(3), b(4);
    
    //Output the objects
    cout << "Test Object to put in front = ";
    cout << a;
    cout << "Test Object to put at   end = ";
    cout << b;

    //Create a Simple Vector using Linked Lists
    SimpleVector<Object> svp(a);
    
    //Fill the simple vector with 10 randomly sized 2D Array Objects and
    //print the last one
    for (int i = 0; i < 10; i++) {
        int rSize = rand() % 10;
        Object c(rSize);
        svp.push(c);
    }
    
    //End the Simple Vector using lists with object b
    svp.push(b);
    cout << "Simple Vector Object size  = " << svp.size() << endl;
    cout << "Simple Vector Front Object =  " << svp[0];
    cout << "Simple Vector End Object   =  " << svp[svp.size() - 1];

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

    cout << "\nTiming analysis of pushing Objects into SimpleVector (Linked List version)\n";

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
