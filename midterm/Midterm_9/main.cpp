/* 
 * File:   main.cpp
 * Author: Ireoluwa
 * Created on May 17, 2025, 12:38 AM
 */
#include <cstdlib>
#include <iostream>
using namespace std;

//User Libraries

//Global Constants - Mathematical, Scientific, Conversions
//Higher Dimensions go here. No Variables

//Function Prototypes
int powEvn(int, int);
int powOdd(int, int);

//Execution Begins here
int main(int argc, char** argv) {
    //Declaring Variables
    int x, n;
    
     //Show predefined test cases for verification
    cout << "\nPredefined Test Cases:" << endl;
    cout << "Even Power Function:" << endl;
    cout << "2^0 = " << powEvn(2, 0) << endl;
    cout << "2^2 = " << powEvn(2, 2) << endl;
    cout << "3^4 = " << powEvn(3, 4) << endl;
    cout << "5^6 = " << powEvn(5, 6) << endl;
    
    cout << "\nOdd Power Function:" << endl;
    cout << "2^0 = " << powOdd(2, 0) << endl;
    cout << "2^3 = " << powOdd(2, 3) << endl;
    cout << "3^5 = " << powOdd(3, 5) << endl;
    cout << "4^7 = " << powOdd(4, 7) << endl <<endl;
    cout << "user test cases" <<endl;
    
    //Prompt user for input
    cout << "Enter base (x): ";
    cin >> x;
    cout << "Enter exponent (n): ";
    cin >> n;
    
    //Display results using both functions
    cout << "\nResults:" << endl;
    cout << x << "^" << n << " using even power function = "
            << powEvn(x, n) << endl;
    cout << x << "^" << n << " using odd power function = " 
            << powOdd(x, n) << endl;
    
    return 0;
}

// Function for even power - O(log n) implementation
int powEvn(int x, int n) {
    // Base case: x^0 = 1
    if (n == 0) {
        return 1;
    }
    // Recursive case for even n
    else if (n % 2 == 0) {
        int half = powEvn(x, n / 2);
        return half * half;
    }
    // Handle odd n case by reducing to even
    else {
        return x * powEvn(x, n - 1);
    }
}

// Function for odd power - O(log n) implementation
int powOdd(int x, int n) {
    // Base case: x^0 = 1
    if (n == 0) {
        return 1;
    }
    
    // Calculate half power
    int half = powOdd(x, n / 2);
    
    // If n is odd, return x * (x^(n/2))^2
    if (n % 2 != 0) {
        return x * half * half;
    }
    // If n is even, return (x^(n/2))^2
    else {
        return half * half;
    }
}