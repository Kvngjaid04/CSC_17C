/* 
 * File:   main.cpp
 * Author: Dr. Mark E. Lehr (Modified)
 * Created on September 16, 2020, 7:50 PM
 * Purpose:  To Test and Modify the Simple Vector with LinkedList
 */

//System Libraries
#include <iostream>
using namespace std;

//User Libraries
#include "SimpleVector.h"

//Global Constants

//Function prototypes
void fillVec(SimpleVector<char> &);
void prntVec(SimpleVector<char> &, int);

//Execution Begins Here
int main(int argc, char** argv) {
    //Declare Variables
    char size = 100;
    SimpleVector<char> sv(size);
    
    //Fill the Vector
    fillVec(sv);
    
    //Print the Vector
    prntVec(sv, 10);
    
    //Copy the Vector
    SimpleVector<char> copysv(sv);
    
    //Print the copied Vector
    prntVec(copysv, 10);
    
    //Test additional functionality
    cout << "Testing push_back and push_front:" << endl;
    
    //Add elements to end
    sv.push_back('!');
    sv.push_back('@');
    
    //Add elements to beginning
    sv.push_front('#');
    sv.push_front('$');
    
    //Print modified vector
    prntVec(sv, 10);
    
    //Test removal functions
    cout << "Testing pop_back and pop_front:" << endl;
    
    //Remove from end
    sv.pop_back();
    
    //Remove from beginning
    sv.pop_front();
    
    //Print final vector
    prntVec(sv, 10);
    
    return 0;
}

void prntVec(SimpleVector<char> &sv, int perLine) {
    cout << endl;
    for(int i = 0; i < sv.size(); i++) {
        cout << sv[i] << " ";
        if(i % perLine == (perLine - 1)) cout << endl;
    }
    cout << endl;
}

void fillVec(SimpleVector<char> &sv) {
    for(int i = 0; i < sv.size(); i++) {
        sv[i] = rand() % 26 + 65;  // Random uppercase letters
    }
}