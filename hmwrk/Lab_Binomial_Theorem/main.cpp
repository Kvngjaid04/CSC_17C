/* 
 * File:   main.cpp
 * Author: Ireoluwa
 * Created on April 29, 2025, 6:47 PM
 */

#include <cstdlib>
#include <iostream>
#include <ctime>
#include <iomanip>
using namespace std;

//User Libraries

//Global Constants - Mathematical, Scientific, Conversions

//Higher Dimensions go here. No Variables

//Function Prototypes
int calcCmb(int n, int k);                              //Calculate combination
float calcPow(float base, int exp);                     //Calculate power
float calcThP(int n, int k, float p, float q);      //Calculate theoretical prob
float simProb(int n, int k, float q, int nTrls);        //Simulate probability
void fairCn();                                          //Fair coin scenario
void biasCn();                                          //Biased coin scenario



//Execution Begins here
int main(int argc, char** argv) {
    //Setting the random number seed
    srand(time(0));
    
    //Displaying Input/Output Information
    cout << fixed << setprecision(2);
    cout << "Binomial theorem: n!/(k!(n-k)!)" << endl << endl;
    
    cout << "FAIR COIN SCENARIO" << endl;
    fairCn();
    
    cout << "\n\nBIASED COIN SCENARIO" << endl;
    biasCn();
    
    //Exiting stage left/right
    return 0;
}

// Function to calculate combination
int calcCmb(int n, int k) {
    int i;
    int nFact = 1;
    int kFact = 1;
    int nkFact = 1;
    
    for(i = 1; i <= n; i++) nFact *= i;    //Calculate n!
    for(i = 1; i <= k; i++) kFact *= i;    //Calculate k!
    for(i = 1; i <= (n-k); i++) nkFact *= i; //Calculate (n-k)!
    
    return nFact / (kFact * nkFact);
}

// Function to calculate power
float calcPow(float base, int exp) {
    float result = 1.0f;
    int i;
    
    for(i = 1; i <= exp; i++) result *= base;
    
    return result;
}

// Function to calculate theoretical probability
float calcThP(int n, int k, float p, float q) {
    int comb = calcCmb(n, k);
    float pPow = calcPow(p, n-k);
    float qPow = calcPow(q, k);
    
    return comb * pPow * qPow;
}

// Function to simulate probability
float simProb(int n, int k, float q, int nTrls) {
    int sucCnt = 0;
    
    for(int i = 0; i < nTrls; i++) {
        int tails = 0;
        
        // Perform n coin flips
        for(int j = 0; j < n; j++) {
            // Random number between 0 and 1
            float rnd = static_cast<float>(rand()) / RAND_MAX;
            if(rnd < q) tails++;
        }
        
        // Count trial as success if we got exactly k tails
        if(tails == k) sucCnt++;
    }
    
    return static_cast<float>(sucCnt) / nTrls;
}

// Function for fair coin scenario
void fairCn() {
    //Declaring Variables
    int n = 4;     // Total number of coin flips
    int k = 1;     // Number of tails we want
    float p = 0.5; // Probability of heads
    float q = 0.5; // Probability of tails
    int nTrils = 10000; // Number of trials for simulation
    
    //Calculate theoretical and simulated probabilities
    float thProb = calcThP(n, k, p, q);
    float simPrb = simProb(n, k, q, nTrils);
    
    //Displaying Output Information
    cout << "x = Probability of flipping a coin and getting a Head: " <<p<<endl;
    cout << "y = Probability of flipping a coin and getting a Tail: " <<q<<endl;
    cout << "\nBinomial probability of getting " << n-k << " heads and " 
         << k << " tails in " << n << " flips = " << thProb << endl;
    cout << "In "<< nTrils << " trials simulated probability: " << simPrb * 100
            << "%" << endl;
    cout << "Binomial theorem probability: " << thProb * 100 << "%" << endl;
}

// Function for biased coin scenario
void biasCn() {
    //Declaring Variables
    int n = 4;     // Total number of coin flips
    int k = 1;     // Number of tails we want
    float p = 0.6; // Probability of heads (biased)
    float q = 0.4; // Probability of tails (biased)
    int nTrils = 10000; // Number of trials for simulation
    
    //Calculate theoretical and simulated probabilities
    float thProb = calcThP(n, k, p, q);
    float simPrb = simProb(n, k, q, nTrils);
    
    //Displaying Output Information
    cout << "x = Probability of flipping a coin and getting a Head: " <<p<<endl;
    cout << "y = Probability of flipping a coin and getting a Tail: " <<q<<endl;
    cout << "\nBinomial probability of getting " << n-k << " heads and " 
         << k << " tails in " << n << " flips = " << thProb << endl;
    cout << "In "<< nTrils << " trials simulated probability: " << simPrb * 100
            << "%" << endl;
    cout << "Binomial theorem probability: " << thProb * 100 << "%" << endl;
}