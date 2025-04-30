/* 
 * File:
 * Author:
 * Date:
 * Purpose:
 * Version:
 */

//System Libraries - Post Here
#include <iostream>
using namespace std;

//User Libraries - Post Here

//Global Constants - Post Here
//Only Universal Physics/Math/Conversions found here
//No Global Variables
//Higher Dimension arrays requiring definition prior to prototype only.

//Function Prototypes - Post Here

//Execution Begins Here
int main(int argc, char** argv) {
    //Set random number seed here when needed
    //Declare variables or constants here
    unsigned short a, b, c,     //3 integers a b c  
                    d,           // a + b,
                   e,             //b + a - c,
                   f;            //(a+b)*c;
    float          g,             //(a/b)*c,
                   h,               //(a*c)/b;
                   i;            //a%b
    

    //Initialize or input data here
    cin >> a >> b >> c;

    //Display initial conditions, headings here
   
    //Process inputs  - map to outputs here
    d = a + b;
    e = b + a - c;
    f = (a + b) * c;
    g = (a / b) * c;
    h = (a * c) / b;
    i = a % b;
    //Format and display outputs here
    cout << "A + B is: " << d << endl;
    cout << "B + A - C is: " << e << endl;
    cout << "(A + B) * C is: " << f << endl;
    cout << "(A / B) * C is: " << g << endl; 
    cout << "(A * C) / B is: " << h << endl; 
    cout << "A % B is: " << i << endl;
    //Clean up allocated memory here
    
    //Exit stage left
    return 0;
}