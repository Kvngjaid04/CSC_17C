/* 
 * File:   main.cpp
 * Author: Ireoluwa Dairo
 * Created on March 11, 2025, 6:12 PM
 */
#include <cstdlib>
#include <iostream>

using namespace std;

//User Libraries

//Global Constants - Mathematical, Scientific, Conversions
//Higher Dimensions go here. No Variables

//Function Prototypes
int sumUsingLoop(int c, int m, int n);
int sumUsingFormula(int c, int m, int n);

//Execution Begins here
int main(int argc, char** argv) {
    //Setting the random number seed
    srand(static_cast<unsigned int>(time(0)));
    
    //Declaring Variables
    int c;
    int m, n;
    int result1, result2;
    
    //Initialize Variables
    cout << "Summation Series: ∑C from i=m to n" << endl;    
    cout << "Enter constant value C: ";
    cin >> c;
    cout << "Enter lower bound m: ";
    cin >> m;
    cout << "Enter upper bound n: ";
    cin >> n;
    
    //Processing/Mapping Inputs to Outputs
    // Solution 1: Using a for-loop to sum the series
    result1 = sumUsingLoop(c, m, n);
    
    // Solution 2: Using the derived formula
    result2 = sumUsingFormula(c, m, n);
    
    //Displaying Input/Output Information
    cout << "\nResults:" << endl;
    cout << "Solution 1 (For-loop): " << result1 << endl;
       
    // Display the formula
    cout << "\nDerived formula:" << endl;
    cout << "f(C, n, m) = C * (n - m + 1)" << endl;
    cout << "Solution 2:  " << result2 << endl;
    
    //Exiting stage left/right
    return 0;
}

// Solution 1: Sum the series using a for-loop
int sumUsingLoop(int c, int m, int n) {
    int sum = 0;
    
    for (int i = m; i <= n; i++) {
        sum += c;
    }
    
    return sum;
}

// Solution 2: Calculate the sum using the derived formula
int sumUsingFormula(int c, int m, int n) {
    int result = c * (n - m + 1);
    return result;
}