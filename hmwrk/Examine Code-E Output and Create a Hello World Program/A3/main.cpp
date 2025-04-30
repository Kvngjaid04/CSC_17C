/* 
 * File: formatted_output.cpp
 * Author: Your Name
 * Date: 06/26/2024
 * Purpose: Display floating-point numbers in various formats.
 * Version: 1.0
 */

// System Libraries
#include <iostream>
#include <iomanip>

using namespace std;

// Execution Begins Here
int main() {
    // Declare variables or constants here
    float a, b, c, d;
    
    // Initialize or input data here
    cin >> a;
    cin >> b;   
    cin >> c;
    cin >> d;
    
    // Display initial conditions, headings here

    // Process inputs - map to outputs here
    
    // Format and display outputs here
    cout << setw(9) << setprecision(0) << fixed << a << setw(10) << setprecision(1) << fixed << a << setw(10) << setprecision(2) << fixed << a << endl;
    cout << setw(9) << setprecision(0) << fixed << b << setw(10) << setprecision(1) << fixed << b << setw(10) << setprecision(2) << fixed << b << endl;
    cout << setw(9) << setprecision(0) << fixed << c << setw(10) << setprecision(1) << fixed << c << setw(10) << setprecision(2) << fixed << c << endl;
    cout << setw(9) << setprecision(0) << fixed << d << setw(10) << setprecision(1) << fixed << d << setw(10) << setprecision(2) << fixed << d;
    
    // Clean up allocated memory here (Not applicable in this case)
    
    // Exit stage left
    return 0;
}
