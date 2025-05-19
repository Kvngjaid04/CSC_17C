/* 
 * File:   main.cpp
 * Author: Ireoluwa
 * Created on May 12, 2025, 7:52 PM
 */

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <ctime>
using namespace std;

//User Libraries

//Global Constants - Mathematical, Scientific, Conversions

//Higher Dimensions go here. No Variables

//Function Prototypes
void simulate(int runs);

//Execution Begins here

int main(int argc, char** argv) {
    //Setting the random number seed

    //Declaring Variables
    int total = 270725; // total ways to draw 4 cards
    float p1, p2, p3, p4;
    //Initialize Variables

    //Processing/Mapping Inputs to Outputs
    /// Theoretical Probabilities
    p4 = (13.0f / total) * 100;
    p3 = ((13.0f * 4 * 12) / total) * 100;
    p2 = ((78.0f * 36) / total) * 100;
    p1 = ((13.0f * 6 * 66 * 16) / total) * 100;
    
    //Displaying Input/Output Information
    cout << " Theoretical Probabilities \n";
    cout << fixed << setprecision(4);
    cout << "Probability of 1 pair: " << p1 << "%" << endl;
    cout << "Probability of 2 pair: " << p2 << "%" << endl;
    cout << "Probability of 3 of a kind: " << p3 << "%" << endl;
    cout << "Probability of 4 of a kind: " << p4 << "%" << endl<< endl;
    
    //simulate
    simulate(1000000); // Simulate 1000000 times
    
    //Exiting stage left/right
    return 0;
}

// Simulation Function
void simulate(int runs) {
    srand(static_cast<unsigned>(time(0)));
    int onePair = 0, twoPair = 0, threeKind = 0, fourKind = 0;

    for (int i = 0; i < runs; i++) {
        int deck[13] = {0};
        for (int j = 0; j < 4; j++)
            deck[rand() % 13]++;

        int pairs = 0;
        bool has3 = false, has4 = false;

        for (int k = 0; k < 13; k++) {
            if (deck[k] == 2) pairs++;
            else if (deck[k] == 3) has3 = true;
            else if (deck[k] == 4) has4 = true;
        }

        if (has4) fourKind++;
        else if (has3) threeKind++;
        else if (pairs == 2) twoPair++;
        else if (pairs == 1) onePair++;
    }

    cout << "Simulated Probabilities (1000000 runs) \n";
    cout << "1 Pair: " << (onePair * 100.0f / runs) << "%\n";
    cout << "2 Pair: " << (twoPair * 100.0f / runs) << "%\n";
    cout << "3 of a Kind: " << (threeKind * 100.0f / runs) << "%\n";
    cout << "4 of a Kind: " << (fourKind * 100.0f / runs) << "%\n";
}
