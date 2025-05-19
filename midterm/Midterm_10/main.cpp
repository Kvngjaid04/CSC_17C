
/* 
 * File:   main.cpp
 * Author: Ireoluwa
 * Created on May 14, 2025, 2:31 AM
 */

#include <cstdlib>
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

//User Libraries

//Global Constants - Mathematical, Scientific, Conversions
const float EPS = 1e-6f;  // Epsilon for base condition

//Higher Dimensions go here. No Variables

//Function Prototypes
float g(float x);  // Recursive function g(x)
//Execution Begins here

int main(int argc, char** argv) {
    //Setting the random number seed

    // Declaring Variables
    float x, dx;
    
    // Initialize Variables
    dx = 0.1f;  // Step size 

    //Processing/Mapping Inputs to Outputs

    //Displaying Input/Output Information
    cout << fixed << setprecision(6);
    cout << "Testing Recursive Function g(x):" << endl;
    cout << setw(8) << "x" << setw(15) << "g(x)" << endl;
    cout << string(23, '-') << endl;
    
    // Test values in domain [-1, 1] with step size dx = 0.1
    for (x = -1.0f; x <= 1.0f + 0.001f; x += dx) {
         // Format x to exactly one decimal place to avoid floating point issues
         float rX = round(x * 10.0f) / 10.0f;
        cout << setw(8) << rX << setw(15) << g(rX) << endl;
    }
    
    //Exiting stage left/right
    return 0;
}

// Implementation of recursive function g(x)
float g(float x) {
    // Base condition: |x| < epsilon
    if (fabs(x) < EPS) {
        return x - pow(x, 3)/6.0f;  // Base formula: g(x) = x - x³/6
    }
    
    // Check if x is within domain [-1, 1]
    if (fabs(x) <= 1.0f) {
        // The problem gives us: g(2x) = 2g(x)/(1+g(x)²)
        // Case: x = 2(x/2)
        //so we need to find g(x) when we know how to find g(x/2)
        
        // First calculate g(x/2)
        float gHalf = g(x/2.0f);
        
        // To find g(x) we use the relation:
        // If y = x/2, then x = 2y and g(x) = g(2y)
        // g(2y) = 2g(y)/(1+g(y)²)
        // g(x) = 2g(x/2)/(1+g(x/2)²)
        
        return (2.0f * gHalf) / (1.0f + pow(gHalf, 2));
    }
    
    // Return 0 for values outside domain
    return 0.0f;
}