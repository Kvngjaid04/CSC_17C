/*
* File: main.cpp
* Author: Dr. Mark E. Lehr
*/

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <cmath>
#include <stack>
#include <vector>
#include <iomanip>
#include <algorithm>
using namespace std;

static stack<float> sStack; // holds angles passed to h   (sinh chain)
static stack<float> cStack; // holds angles passed to g   (cosh chain)
static int hCalls = 0;
static int gCalls = 0;

float h(float);
float g(float);
void rstCntSt();

int main(int argc, char** argv) {
    // Vectors to store the data
    vector<float> angs;
    vector<int> hClH, gClH, hClG, gClG;
    
     for (float aRad = -1.0f; aRad <= 1.0001f; aRad += 0.1f) {
        angs.push_back(aRad);

        // Calls when computing h
        rstCntSt();
        h(aRad);
        hClH.push_back(hCalls);
        gClH.push_back(gCalls);

        // Calls when computing g
        rstCntSt();
        g(aRad);
        hClG.push_back(hCalls);
        gClG.push_back(gCalls);
    }
    
    cout << fixed << setprecision(1);
    // Print table header
    cout << setw(10) << "Angle (rad)";
    cout << setw(15) << "h (from h)";
    cout << setw(15) << "g (from h)";
    cout << setw(15) << "h (from g)";
    cout << setw(15) << "g (from g)" << endl;
    cout << string(70, '-') << endl;
    
    // Iterate through the collected data and print each row of the table
    for (size_t i = 0; i < angs.size(); ++i) {
        cout << setw(10) << angs[i] << setw(15) << hClH[i] << setw(15) 
             << gClH[i] << setw(15) << hClG[i] << setw(15) << gClG[i] << endl;
    }
    //Testing out recursive trig functions
    //float angDeg=45;
    //float angRad=angDeg*atan(1)/45;  // converts to pi/4
    //cout << "Angle = "<<angDeg
    //     << " sinh = "<<sinh(angRad)
    //     << " our h = "<<h(angRad)<<endl;
    //cout << "Angle = " 
    //     << angDeg << " cosh = "
    //     << cosh(angRad)
    //    << " our g = "<< g(angRad)<<endl;
    //Exit stage right
    return 0;
    }

float h(float angR) {
    sStack.push(angR);
    hCalls++;
    const float tol = 1e-6f;
    float ans;
    if (fabs(angR) < tol) {
        ans = angR + angR * angR * angR / 6.0f;
    } else {
        ans = 2.0f * h(angR / 2.0f) * g(angR / 2.0f);
    }
    sStack.pop();
    return ans;
}
    
float g(float angR) {
    cStack.push(angR);
    gCalls++;
    const float tol = 1e-6f;
    float ans;
    if (fabs(angR) < tol) {
        ans = 1.0f + angR * angR / 2.0f;
    } else {
        float sHalf = h(angR / 2.0f);
        ans = 1.0f + 2.0f * sHalf * sHalf;
    }
    cStack.pop();
    return ans;
}

void rstCntSt() {
    hCalls = 0;
    gCalls = 0;

    while (!sStack.empty()) {
        sStack.pop();
    }
    while (!cStack.empty()) {
        cStack.pop();
    }
}