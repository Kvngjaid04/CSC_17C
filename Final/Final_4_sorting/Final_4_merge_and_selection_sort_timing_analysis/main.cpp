/* 
 * File:   main.cpp
 * Author:ireoluwa
 * Purpose:  Timing Analysis
 */
//System Level Libraries
#include <iostream>   //I/O Library
#include <cstdlib>    //Random Number Library
#include <ctime>      //Time Library
using namespace std;  //Library Scope

//User Libraries
//Global Constants
//Science and Math, Conversions, Higher Dimensions
//const to follow

//Function Prototypes
short *filAray(int);
void destroy(short *);
void mrgSort(short *,int,int, int);
void merge(short *,int,int,int,int);
void selSort(short *,int,int);

//Execution Starts Here
int main(int argc, char** argv){
    //Set Random Number Seed Here
    srand(static_cast<unsigned int>(time(0)));
    
    //Declare Variables - Known and Unknown, units, range, description
    int size=100000;
    int p=100000;  //Number of top elements to display
    short* array1;
    short* array2;
    
    //Initialize Variables
    array1=filAray(size);
    array2=filAray(size);
    //Copy array1 to array2 for fair comparison
    for(int i=0;i<size;i++){
        array2[i]=array1[i];
    }
    
        
    //Map inputs to outputs -> i.e. process the inputs
    //Test Selection Sort (Top p elements only)
    clock_t beg1=clock();
    selSort(array1,size,p);
    clock_t end1=clock();
    int ms1 = (end1-beg1) * 1000 / CLOCKS_PER_SEC;
    
    //Test Merge Sort (Full sort)
    clock_t beg2=clock();
    mrgSort(array2, 0, size, p);
    clock_t end2=clock();
    int ms2 = (end2-beg2) * 1000 / CLOCKS_PER_SEC;
    
    //Display timing results
    cout<<"For N="<<size<<" and p="<<p<<endl;
    cout<<"Selection Sort Takes "<<ms1<<" Milliseconds"<<endl;
    cout<<"Merge Sort Takes "<<ms2<<" Milliseconds"<<endl;
    
    
    //Clean up - File closing, memory deallocation, etc....
    destroy(array1);
    destroy(array2);
    //Exit Stage Right!
    return 0;
}
void selSort(short *a,int n,int p){
    //Loop and declare variables - modified to stop after p elements
    int indx,min;
    for(int pos=0;pos<p;pos++){
        //Find the largest in the remaining list for top p elements
        int max=a[pos];
        indx=pos;
        for(int i=pos+1;i<n;i++){
            if(a[i]>max){
                max=a[i];
                indx=i;
            }
        }
        //Perform the swap
        a[indx]=a[pos];
        a[pos]=max;
    }
}
void mrgSort(short *a, int beg, int end, int p){
    int center=(beg+end)/2;
    if ((center - beg) > 1) mrgSort(a, beg, center, p);
    if ((end - center) > 1) mrgSort(a, center, end, p);
    merge(a, beg, center, end, p);
}

void merge(short *a, int beg, int nlow, int nhigh, int p){
    //Create a merged array
    int span=nhigh-beg;    //Span the range to merge
    int cntl=beg,cnth=nlow;//Independent counters to merge
    short *c=new short[span];  //Allocate Memory
    int count = 0;
    //Fill the array
    while (count < p && (cntl < nlow || cnth < nhigh)) {
        if (cntl == nlow) {
            c[count++] = a[cnth++];
        }
        else if (cnth == nhigh) {
            c[count++] = a[cntl++];
        }
        else if (a[cntl] > a[cnth]) {  
            c[count++] = a[cntl++];
        }
        else {
            c[count++] = a[cnth++];
        }
    }
    //Copy back and deallocate memory
    for (int i = 0; i < count; i++) {
        a[beg + i] = c[i];
    }
    delete[] c;
}

void destroy(short *a){
    delete []a;
}
//Function Implementations
short *filAray(int n){
    short *array=new short[n];
    for(int i=0;i<n;i++){
        array[i]=rand()%32768;//short integer range
    }
    return array;
}