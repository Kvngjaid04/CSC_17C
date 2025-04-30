/* 
 * File:   main.cpp
 * Author:
 * Created on:
 * Purpose:  To display Permutation and Combination calculations
 */
//System Libraries Here
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

//Function to calculate factorial
unsigned long fact(int n) {
    if (n <= 1) return 1;
    unsigned long res = 1;
    for (int i = 2; i <= n; i++) {
        res *= i;
    }
    return res;
}

//Function to calculate permutation without replacement
unsigned long perm(int n, int m) {
    if (m > n) return 0;
    return fact(n) / fact(n - m);
}

//Function to calculate combination without replacement
unsigned long comb(int n, int m) {
    if (m > n) return 0;
    return fact(n) / (fact(n - m) * fact(m));
}

//Function to calculate combination with replacement
unsigned long combR(int n, int m) {
    return fact(n + m - 1) / (fact(n - 1) * fact(m));
}

//Program Execution Begins Here
int main(int argc, char** argv) {
    //Display the Headers
    cout << "P -> Permutation(Order Matters)" << endl;
    cout << "C -> Combination(Order does not matter)" << endl;
    cout << "Rep -> with replacement" << endl;
    cout << "no Rep -> no replacement" << endl;
    cout << "N -> Number of total elements" << endl;
    cout << "M -> Number of elements to take from the total" << endl << endl;
    
    cout << " N M P Rep P no Rep C Rep C no Rep" << endl;
    cout << " N^M N!/(N-M)! (N+M-1)!/((N-1)!M!) N!/((N-M)!M!)" << endl << endl;
    
    //Calculate and display the table
    for (int n = 2; n <= 26; n++) {
        for (int m = 0; m <= n; m++) {
            unsigned long permR = pow(n, m);
            unsigned long permNR = perm(n, m);
            unsigned long cR = combR(n, m);
            unsigned long combNR = comb(n, m);
            
            cout << setw(2) << n << " " 
                 << setw(2) << m << " " 
                 << setw(10) << permR << " " 
                 << setw(10) << permNR << " " 
                 << setw(10) << cR << " " 
                 << setw(10) << combNR << endl;
        }
    }
    
    //Exit
    return 0;
}