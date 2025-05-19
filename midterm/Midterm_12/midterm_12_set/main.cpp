/* 
 * File:   main.cpp
 * Author: Dr. Mark E. Lehr
 * modified: Ireoluwa
 * Created on May 15, 2025, 11:40 PM
 */
#include <cstdlib>
#include <iostream>
#include <set>
#include <algorithm>
using namespace std;

//User Libraries

//Global Constants - Mathematical, Scientific, Conversions

//Higher Dimensions go here. No Variables

//Function Prototypes
int *fillAry(int,int);
void prntAry(int *,int,int);
void prntMod(int *);
void swap(int *,int *);
void minPos(int *,int,int);
void mrkSort(int *,int);
int *modSet(const int *,int);
int *copy(const int *,int);

//Execution Begins here
int main(int argc, char** argv) {
    //Setting the random number seed
    srand(static_cast<unsigned int>(time(0)));
    
    //Declaring Variables
    int size=15;
    int modNum=10;
    
    //Initialize Variables
    int *ary=fillAry(size,modNum);
    
    //Processing/Mapping Inputs to Outputs
    
    //Print the initial array
    prntAry(ary,size,10);
    
    //Calculate the mode array
    int *modAry=modSet(ary,size);
    
    //Displaying Input/Output Information
    
    //Print the modal information of the array
    prntMod(modAry);
    
    //Exiting stage left/right
    delete []ary;
    delete []modAry;
    return 0;
}

int *copy(const int *a,int n){
    //Declare and allocate an array
    int *b=new int[n];
    //Fill
    for(int i=0;i<n;i++){
        b[i]=a[i];
    }
    //Return the copy
    return b;
}

int *modSet(const int *ary, int size) {
    // Find max value to determine frequency array size
    int maxVal = 0;
    for(int i = 0; i < size; i++) {
        if(ary[i] > maxVal) maxVal = ary[i];
    }
    
    // Count frequencies
    int *freq = new int[maxVal+1]();
    for(int i = 0; i < size; i++) {
        freq[ary[i]]++;
    }
    
    // Find max frequency
    int maxFrq = 0;
    for(int i = 0; i <= maxVal; i++) {
        if(freq[i] > maxFrq) maxFrq = freq[i];
    }
    
    // Use set for modes
    set<int> mSet;
    for(int i = 0; i <= maxVal; i++) {
        if(freq[i] == maxFrq) {
            mSet.insert(i);
        }
    }
    
    // Result array
    int nMode = mSet.size();
    int *modAry = new int[nMode + 2];
    modAry[0] = nMode;
    modAry[1] = maxFrq;
    
    // Fill values
    int idx = 2;
    for(int val : mSet) {
        modAry[idx++] = val;
    }
    
    delete[] freq;
    return modAry;
}

void prntMod(int *ary){
    cout<<endl;
    cout<<"The number of modes = " <<
            ary[0]<<endl;
    cout<<"The max Frequency = " <<
            ary[1]<<endl;
    if(ary[0]==0){
        cout<<"The mode set = {null}"<<endl;
        return;
    }
    cout<<"The mode set = {";
    for(int i=2;i<ary[0]+1;i++){
        cout<<ary[i]<<",";
    }
    cout<<ary[ary[0]+1]<<"}"<<endl;
}

void mrkSort(int *array,int n){
    for(int i=0;i<n-1;i++){
        minPos(array,n,i);
    }
}

void minPos(int *array,int n,int pos){
    for(int i=pos+1;i<n;i++){
        if(*(array+pos)>*(array+i))
            swap(array+pos,array+i);
    }
}

void swap(int *a,int *b){
    //Swap in place
    *a=*a^*b;
    *b=*a^*b;
    *a=*a^*b;
}

void prntAry(int *array,int n,int perLine){
    //Output the array
    cout<<endl;
    for(int i=0;i<n;i++){
        cout<<*(array+i)<<" ";
        if(i%perLine==(perLine-1))cout<<endl;
    }
    cout<<endl;
}

int *fillAry(int n, int modNum){
    //Allocate memory
    int *array=new int[n];
    
    //Fill the array with 2 digit numbers
    for(int i=0;i<n;i++){
        *(array+i)=i%modNum;
        //*(array+i)=rand()%modNum;
    }
    
    //Exit function
    return array;
}