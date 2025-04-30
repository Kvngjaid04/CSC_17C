/* 
 * File:   main.cpp
 * Author: Dr. Mark E. Lehr
 * Created on February 23rd, 2020, 12:15 pM
 * Purpose:  Triangular array
 *           Complete the functions with the defined structure
 */

//System Libraries Here
#include <iostream>  //I/O Library
using namespace std;

//User Libraries Here
struct TriMatx{
     int size;  //Represents the number of rows
     int *col;  //Represents the column array, i.e. number of columns for each row
     int *indx; //Represents the index matrix which you can sort to use for display
     int **data;//Represents the data contents of the Triangular matrix
};

//Global Constants Only, No Global Variables
//Like PI, e, Gravity, or conversions

//Function Prototypes Here
int  mrkRand(int=1<<15-1);     //PSRNG repeating the same sequence
void prntAry(int *,int);       //Print a 1-D array
void destroy(TriMatx *);       //Deallocate memory
//Complete the following Function
TriMatx *fillMat(int);  //Randomly fill a triangular structure
void mrkSort(TriMatx *);//Use a database sort
void prntAry(TriMatx *);//Print a triangular array

//Program Execution Begins Here
int main(int argc, char** argv) {
    //Declare all Variables Here
    int rowSize;   //Number of Rows in the Array
    TriMatx *triMt;//Triangular Matrix Structure
    
    //Input or initialize values Here
    cout<<"Input the Number of Rows in the Array"<<endl;
    cin>>rowSize;
    triMt=fillMat(rowSize);//Dynamic triangular array

    //Output Located Here
    cout<<"The Column Array Size"<<endl;
    prntAry(triMt->col,triMt->size);
    cout<<"The Triangular Array Sorted"<<endl;
    mrkSort(triMt);//Sort the columns with an index
    prntAry(triMt);//Display the Matrix with Columns sorted

    //Deallocate the structure
    destroy(triMt);
    
    //Exit
    return 0;
}

//Create this function
TriMatx *fillMat(int rows){
    TriMatx *triMt=new TriMatx;
    
    // Set the size (number of rows)
    triMt->size=rows;
    
    // Allocate memory for column array
    triMt->col=new int[rows];
    
    // Allocate memory for index array and initialize
    triMt->indx=new int[rows];
    for(int i=0; i<rows; i++){
        triMt->indx[i]=i;
    }
    
    // Randomly assign number of columns for each row (1 to rows)
    for(int i=0; i<rows; i++){
        triMt->col[i]=mrkRand()%9+1;
    }
    
    // Allocate memory for data array (rows)
    triMt->data=new int*[rows];
    
    // Allocate memory for each row and fill with random data
    for(int i=0; i<rows; i++){
        triMt->data[i]=new int[triMt->col[i]];
        for(int j=0; j<triMt->col[i]; j++){
            triMt->data[i][j]=mrkRand()%9+1; // Random value between 0-9
        }
    }
    
    return triMt;
}

//Create this function
void prntAry(TriMatx *triMt){
    for(int i=0; i<triMt->size; i++){
        int idx = triMt->indx[i];
        for(int j=0; j<triMt->col[idx]; j++){
            cout<<triMt->data[idx][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl<<endl;
}

//Create this function
void mrkSort(TriMatx *triMt){
    for(int pos=0; pos<triMt->size-1; pos++){
        for(int lst=pos+1; lst<triMt->size; lst++){
            if(triMt->col[triMt->indx[pos]] > triMt->col[triMt->indx[lst]]){
                int temp = triMt->indx[pos];
                triMt->indx[pos] = triMt->indx[lst];
                triMt->indx[lst] = temp;
            }
        }
    }
}



void destroy(TriMatx *triMt){
    //Delete every row of the triangular array
    for(int i=0;i<triMt->size;i++){
        delete []triMt->data[i];
    }
    //Delete the pointers
    delete []triMt->data;
    delete []triMt->col;
    delete []triMt->indx;
    delete triMt;
}

void prntAry(int *a,int n){
    if(a==0)return;
    for(int i=0;i<n;i++){
        cout<<a[i]<<" ";
    }
    cout<<endl<<endl;
}

int mrkRand(int seed){
    //Xn+1 = (aXn + c) mod m
    //where X is the sequence of pseudo-random values
    //m, 0 < m  - modulus 
    //a, 0 < a < m  - multiplier
    //c, 0 ≤ c < m  - increment
    //x0, 0 ≤ x0 < m  - the seed or start value
    unsigned int a=31051;      //Short Prime
    unsigned int c=997;        //Another Prime
    unsigned int shrt=1<<15-1; //Range of positive signed short
    unsigned int m=1<<31-1;    //Range of positive signed int
    static int Xn=30937;       //Short Prime
    static int cnt=0;          //Initialize the seed
    if(cnt==0&&seed<=shrt)Xn=seed;
    cnt++;
    Xn=(a*Xn+c)%m;
    return Xn;
}