/* 
 * File:   main.cpp
 * Author: Ireoluwa
 * Created on May 17, 2025, 1:45 AM
 */

#include <cstdlib>
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

//User Libraries

//Global Constants - Mathematical, Scientific, Conversions
const float eps = 1e-6f;  // Epsilon for base condition

//Higher Dimensions go here. No Variables

//Function Prototypes
float C(float x);  // C(x) mutual recursive function
float S(float x);  // S(x) mutual recursive function

//Execution Begins here

int main(int argc, char** argv) {
    //Setting the random number seed

    //Declaring Variables
    float x, dx, lim;
    
    //Initialize Variables
    dx = 0.1f;  //step size        
    lim = atanf(1.0f); // Domain limit: arctan(1) ≈ π/4
    
    //Processing/Mapping Inputs to Outputs
    cout << fixed << setprecision(6);
    cout << "Testing Mutual Recursive Functions:" << endl;
    
    // Test values in domain with step size dx
    cout << setw(8) << "x" << setw(15) << "C(x)" << setw(15) << "S(x)" << endl;
    cout << string(38, '-') << endl;
    
    // Loop through domain with specified step size
    for (x = -lim; x <= lim + 0.001f; x += dx) {
        // Ensure x stays within domain bounds
        float tx = (fabsf(x) > lim) ? copysignf(lim, x) : x;
        
        // Skip values too close to zero (base case issue)
        if (fabsf(tx) < eps) continue;
        
        cout << setw(8) << tx 
             << setw(15) << C(tx) 
             << setw(15) << S(tx) << endl;
    }
    //Displaying Input/Output Information

    //Exiting stage left/right
    return 0;
}

// Implementation of C(x) mutual recursive function
float C(float x) {
    // Base condition: |x| < epsilon
    if (fabsf(x) < eps) {
        return 1.0f/x + x/6.0f;  // Base formula for C(x)
    }
    
    // Check if x is within domain |x| ≤ arctan(1)
    if (fabsf(x) <= atanf(1.0f)) {
        // Apply recursive formula: C(2x) = C(x)S(x)/2
        return (C(x/2.0f) * S(x/2.0f)) / 2.0f;
    }
    
    // Return 0 for values outside domain 
    return 0.0f;
}

// Implementation of S(x) mutual recursive function
float S(float x) {
    // Base condition: |x| < epsilon
    if (fabsf(x) < eps) {
        return 1.0f + (x*x)/2.0f;  // Base formula for S(x)
    }
    
    // Check if x is within domain |x| ≤ arctan(1)
    if (fabsf(x) <= atanf(1.0f)) {
        // Calculate intermediate values for clarity
        float cx = C(x/2.0f);
        float sx = S(x/2.0f);
        float c2 = cx * cx;  // C²(x/2)
        float s2 = sx * sx;  // S²(x/2)
        
        // Prevent division by zero
        if (fabsf(c2 - s2) < eps) {
            return 0.0f;  // Return 0 instead of NaN
        }
        
        // Apply recursive formula: S(2x) = C²(x)S²(x)/(C²(x)-S²(x))
        return (c2 * s2) / (c2 - s2);
    }
    
    // Return 0 for values outside domain 
    return 0.0f;
}
