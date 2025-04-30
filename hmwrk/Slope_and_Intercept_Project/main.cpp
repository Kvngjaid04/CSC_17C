/* 
 * File:   slope/intercept.cpp
 * Author: Ireoluwa Dairo
 * Created on April 2, 2025, 7:26 PM
 */
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

//User Libraries

//Global Constants - Mathematical, Scientific, Conversions
//Higher Dimensions go here. No Variables

//Function Prototypes
void readDat(const string& fFile, const string& cFile, 
             vector<float>& fTemp, vector<float>& cTemp);
void calcLS(const vector<float>& x, const vector<float>& y, 
            float& slope, float& intcpt);
void dispRes(float slope, float intcpt);

//Execution Begins here
int main(int argc, char** argv) {
    //Setting the random number seed
    
    //Declaring Variables
    vector<float> fTemp;
    vector<float> cTemp;
    float slope = 0.0f;
    float intcpt = 0.0f;
    string fFile = "fahr.txt";
    string cFile = "ecels.txt";
    
    //Initialize Variables - Read data from files
    
    readDat(fFile, cFile, fTemp, cTemp);
    
    //Processing/Mapping Inputs to Outputs
    calcLS(fTemp, cTemp, slope, intcpt);
    
    //Displaying Input/Output Information
    dispRes(slope, intcpt);
    
    //Exiting stage left/right
    return 0;
}

//Reads temperature data from two separate files
void readDat(const string& fFile, const string& cFile, 
             vector<float>& fTemp, vector<float>& cTemp) {
    // Read Fahrenheit data
    ifstream fin1(fFile);
    string line;
    
    while (getline(fin1, line)) {
        float val = stof(line);
        fTemp.push_back(val);
    }
    fin1.close();
    
    // Read Celsius data
    ifstream fin2(cFile);
    while (getline(fin2, line)) {
        float val = stof(line);
        cTemp.push_back(val);
    }
    fin2.close();
}

//Calculates the slope and intercept 
void calcLS(const vector<float>& x, const vector<float>& y, 
            float& slope, float& intcpt) {
    int n = x.size();
    float sumX = 0.0f, sumY = 0.0f, sumXY = 0.0f, sumX2 = 0.0f;
    
    // Calculate sums 
    for (int i = 0; i < n; i++) {
        sumX += x[i];
        sumY += y[i];
        sumXY += x[i] * y[i];
        sumX2 += x[i] * x[i];
    }
    
    // Calculate slope: m = (n*ΣXY - ΣX*ΣY) / (n*ΣX² - (ΣX)²)
    slope = (n * sumXY - sumX * sumY) / (n * sumX2 - sumX * sumX);
    
    // Calculate intercept: b = (ΣY - m*ΣX) / n
    intcpt = (sumY - slope * sumX) / n;
}

// Displays the results 
void dispRes(float slope, float intcpt) {
    cout << "Equation (deg_C = m * deg_F + b):" << endl;
    cout << "Calculated Slope (m) = " << setprecision(4) << slope << endl;
    cout << "Calculated Intercept (b) = " << setprecision(6) << intcpt << endl;
    cout << "\nResult: deg_C = " << setprecision(4) <<  slope << " * deg_F + ( " 
            << setprecision(6) << intcpt <<" )" <<endl;
}