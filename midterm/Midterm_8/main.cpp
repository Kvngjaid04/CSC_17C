/* 
 * File:   main.cpp
 * Author: Ireoluwa
 * Created on May 16, 2025, 11:20 PM
 */

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

//User Libraries

//Global Constants - Mathematical, Scientific, Conversions
const int fldPcnt = 40;
const int numTral = 1000000;  // Number of simulations

//Higher Dimensions go here. No Variables

//Function Prototypes

//Execution Begins here

int main(int argc, char** argv) {
    //Setting the random number seed
        srand(time(0));

    //Declaring Variables
    float thrprob = 1.0;
    int suctril = 0;
    //Initialize Variables

    //Processing/Mapping Inputs to Outputs
    for (int i = 0; i < 5; ++i) {
        thrprob *= static_cast<float>(fldPcnt) / 100.0;
    }
    
    for (int trial = 0; trial < numTral; ++trial) {
        int setBits = 0;
        for (int i = 0; i < 5; ++i) {
            if (rand() % 100 < fldPcnt) {
                setBits++;
            }
        }

        if (setBits == 5) {
            suctril++;
        }
    }
    float simProb = static_cast<float>(suctril) / numTral;
    
    //Displaying Input/Output Information
    cout << "Theoretical Probability: " << thrprob << endl << endl;
    cout << "Simulated Probability: " << simProb << endl;
    
    //Exiting stage left/right
    return 0;
}
