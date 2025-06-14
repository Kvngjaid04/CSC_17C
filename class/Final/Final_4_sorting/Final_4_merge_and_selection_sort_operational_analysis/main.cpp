/* 
 * File:   main.cpp
 * Author: ireoluwa
 * Purpose:  operational Analysis
 */
//System Level Libraries
#include <iostream>   //I/O Library
#include <cstdlib>    //Random Number Library
using namespace std;  //Library Scope

//Global Operation Counters
long long Ob1, P1, Os1, Oi1, Oj1; // Selection Sort counters
long long Ob2, P2, Os2, Oi2, Oj2; // Merge Sort counters

//Function Prototypes
short *filAray(int);
void destroy(short *);
void selSort(short *,int,int);
void mrgSort(short *,int,int,int);
void merge(short *,int,int,int,int);
void resetCounters();

//Execution Starts Here
int main(int argc, char** argv){
    //Set Random Number Seed Here
     
    //Declare Variables - Known and Unknown, units, range, description
    int size = 100000;
    int p = 100;  // Number of top elements to find
    short* array1;
    short* array2;
    
    //Initialize Variables
    array1 = filAray(size);
    array2 = new short[size];
    
    //Copy array1 to array2 for fair comparison
    for(int i = 0; i < size; i++){
        array2[i] = array1[i];
    }
    
    //Reset operation counters
    resetCounters();
    
    //Test Selection Sort (Top p elements only)
    selSort(array1, size, p);
    
    //Test Merge Sort (Full sort)
    mrgSort(array2, 0, size, p);
    
    //Display operational analysis results
    cout << "N=" << size << " and p=" << p <<  endl;
    cout << endl;
    
    cout << "SELECTION SORT:" << endl;
    cout << "Ob1   = " << Ob1 << endl;
    cout << "Oi1   = " << Oi1 << endl;
    cout << "Oj1   = " << Oj1 << endl;
    cout << "P1    = " << P1 << endl;
    cout << "Os1   = " << Os1 << endl;
    cout << "Total= " << Ob1+Oi1+Oj1+P1+Os1 << endl;
    cout << endl;
    
    cout << "MERGE SORT:" << endl;
    cout << "Ob2   = " << Ob2 << endl;
    cout << "Oi2   = " << Oi2 << endl;
    cout << "Oj2   = " << Oj2 << endl;
    cout << "P2    = " << P2 << endl;
    cout << "Os2   = " << Os2 << endl;
    cout << "Total= " << Ob2+Oi2+Oj2+P2+Os2 << endl;
    cout << endl;
    
    //Clean up
    destroy(array1);
    destroy(array2);
    
    return 0;
}

void resetCounters() {
    Ob1 = P1 = Os1 = Oi1 = Oj1 = 0;
    Ob2 = P2 = Os2 = Oi2 = Oj2 = 0;
}

void selSort(short *a, int n, int p){
    Ob1 += 2; // Initialize variables
    //Loop through p positions to find top p elements
    for(int pos = 0; pos < p; pos++){
        Oi1 += 4; // Loop overhead and initialization
        int max = a[pos];
        int indx = pos;
        
        //Find the largest in the remaining list
        for(int i = pos + 1; i < n; i++){
            Oj1 += 3; // Inner loop overhead and comparison setup
            if(a[i] > max){
                P1++; // Comparison that results in update
                Os1 += 2; // Assignment operations
                max = a[i];
                indx = i;
            }
        }
        
        //Perform the swap if needed
        if(indx != pos) {
            P1++; // Swap condition
            Os1 += 3; // Three assignment operations for swap
            short temp = a[indx];
            a[indx] = a[pos];
            a[pos] = temp;
        }
    }
}

void mrgSort(short *a, int beg, int end, int p){
    Ob2 += 2; // Function entry and center calculation
    int center = (beg + end) / 2;
    
    if ((center - beg) > 1) {
        P2++; // Condition check
        mrgSort(a, beg, center, p);
    }
    if ((end - center) > 1) {
        P2++; // Condition check
        mrgSort(a, center, end, p);
    }
    merge(a, beg, center, end, p);
}

void merge(short *a, int beg, int nlow, int nhigh, int p){
    Ob2 += 5; // Function setup and variable initialization
    int span = nhigh - beg;
    int cntl = beg, cnth = nlow;
    short *c = new short[span];
    int count = 0;
    
    //Fill the merged array
    while (count < p && (cntl < nlow || cnth < nhigh)) {
        Oi2 += 3; // Loop condition checks
        
        if (cntl == nlow) {
            P2++; // Condition check
            Os2++; // Assignment
            c[count++] = a[cnth++];
        }
        else if (cnth == nhigh) {
            P2++; // Condition check
            Os2++; // Assignment
            c[count++] = a[cntl++];
        }
        else if (a[cntl] > a[cnth]) {
            P2++; // Comparison
            Os2++; // Assignment
            c[count++] = a[cntl++];
        }
        else {
            P2++; // Final else condition
            Os2++; // Assignment
            c[count++] = a[cnth++];
        }
    }
    
    //Copy back to original array
    for (int i = 0; i < count; i++) {
        Oj2 += 2; // Loop overhead and assignment
        a[beg + i] = c[i];
    }
    
    delete[] c;
}

void destroy(short *a){
    delete []a;
}

short *filAray(int n){
    short *array = new short[n];
    for(int i = 0; i < n; i++){
        array[i] = rand() % 32768; // short integer range
    }
    return array;
}