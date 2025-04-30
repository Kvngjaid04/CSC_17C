/* 
 * File:   main.cpp
 * Author: Ireoluwa
 * Created on April 25, 2025, 6:21 PM
 */

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;
//User Libraries

//Global Constants - Mathematical, Scientific, Conversions

//Higher Dimensions go here. No Variables

//Function Prototypes
unsigned long long fact(int n);
unsigned long long perm(int n, int m);
unsigned long long permRep(int n, int m);
unsigned long long comb(int n, int m);
unsigned long long combRep(int n, int m);

//Execution Begins here
int main(int argc, char** argv) {
    //Setting the random number seed
    
    //Declaring Variables
    int minN = 2;
    int maxN = 26;
    
    //Initialize Variables
    
    //Processing/Mapping Inputs to Outputs
    
    //Displaying Input/Output Information
    cout << "P -> Permutation(Order Matters)" << endl;
    cout << "C -> Combination(Order does not matter)" << endl;
    cout << "Rep -> with replacement" << endl;
    cout << "no Rep -> no replacement" << endl;
    cout << "N -> Number of total elements" << endl;
    cout << "M -> Number of elements to take from the total" << endl << endl;
    
    cout << setw(3) << "N" << setw(3) << "M" 
         << setw(16) << "P Rep" 
         << setw(23) << "P no Rep" 
         << setw(23) << "C Rep" 
         << setw(22) << "C no Rep" << endl;
         
    cout << setw(3) << " " << setw(3) << " " 
         << setw(15) << "N^M" 
         << setw(25) << "N!/(N-M)!" 
         << setw(29) << "(N+M-1)!/((N-1)!M!)" 
         << setw(18) << "N!/((N-M)!M!)" << endl << endl;
    
    
    for (int n = minN; n <= maxN; n++) {
        for (int m = 0; m <= n; m++) {
            cout << setw(3) << n << setw(3) << m;
            
            // Permutation with replacement
            cout << setw(23) << permRep(n, m);
            
            // Permutation without replacement
            cout << setw(23) << perm(n, m);
            
            // Combination with replacement
            cout << setw(23) << combRep(n, m);
            
            // Combination without replacement
            cout << setw(15) << comb(n, m);
            
            cout << endl;
        }
    }
    
    //Exiting stage left/right
    return 0;
}
// Calculate factorial
unsigned long long fact(int n) {
    if (n <= 1) return 1;
    
    unsigned long long res = 1;
    for (int i = 2; i <= n; i++) {
        res *= i;
    }
    return res;
}
// Permutation without replacement: nPm = n!/(n-m)!
unsigned long long perm(int n, int m) {
    if (m > n) return 0;
    return fact(n) / fact(n - m);
}
// Permutation with replacement: nPm R = n^m
unsigned long long permRep(int n, int m) {
    unsigned long long result = 1;
    for (int i = 0; i < m; i++) {
        result *= n;
    }
    return result;
}
// Combination without replacement: nCm = n!/((n-m)!*m!)
unsigned long long comb(int n, int m) {
    if (m > n) return 0;
    if (m == 0 || m == n) return 1;
    if (m > n - m) m = n - m;
    
    unsigned long long result = 1;
    
    // Calculate n!/((n-m)!*m!) 
    for (int i = 1; i <= m; i++) {
        result = result * (n - m + i) / i;
    }
    return result;
}

// Combination with replacement: nCm R = (n+m-1)!/((n-1)!*m!)
unsigned long long combRep(int n, int m) {
    if (m == 0) return 1;  
    return comb(n + m - 1, m);
}