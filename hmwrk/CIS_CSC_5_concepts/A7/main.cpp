/* 
 * File:   main.cpp
 * Author: Ireoluwa Dairo
 * Created on August 4 11:00 pm
 * Purpose:  Sum Rows, Sum Columns, Grand Sum of an integer array
 */

//System Libraries Here
#include <iostream>//cin,cout
#include <iomanip> //setw(10)
using namespace std;

//User Libraries Here

//Global Constants Only, No Global Variables
//Allowed like PI, e, Gravity, conversions, array dimensions necessary
const int COLMAX=80;  //Max Columns much larger than needed.

//Function Prototypes Here
void read(int [][COLMAX],int &,int &);//Prompt for size then table
void sum(const int [][COLMAX],int,int,int[][COLMAX]);//Sum rows,col,grand total
void print(const int [][COLMAX],int,int,int);//Either table can be printed

//Program Execution Begins Here
int main(int argc, char** argv) {
    //Declare all Variables Here
    const int ROW=80;           //Max Rows much larger than needed
    int array[ROW][COLMAX]={};  //Declare original array
    int augAry[ROW][COLMAX]={}; //Actual augmented table row+1, col+1
    int row,col;                
    
    //Input the original table
    read(array,row,col);
    
    //Augment the original table by the sums
    sum(array,row,col,augAry);
    
    //Output the original array
    cout<<endl<<"The Original Array"<<endl;
    print(array,row,col,10);//setw(10)
    
    //Output the augmented array
    cout<<endl<<"The Augmented Array"<<endl;
    print(augAry,row+1,col+1,10);//setw(10)
    
    //Exit
    return 0;
}

void read(int a[][COLMAX],int &row ,int &col){
    cout << "Input a table and output the Augment row,col and total sums." << endl;
    cout << "First input the number of rows and cols. <20 for each" << endl;
    cin >> row >> col;
    
    cout << "Now input the table." << endl;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            cin >> a[i][j];
        }
    }
    } //Prompt for size then table

void sum(const int a[][COLMAX],int row ,int col ,int augary[][COLMAX]){
// Copy original array to augmented array
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            augary[i][j] = a[i][j];
        }
    }
    
    // Calculate row sums
    for (int i = 0; i < row; i++) {
        int sumRow = 0;
        for (int j = 0; j < col; j++) {
            sumRow += augary[i][j];
        }
        augary[i][col] = sumRow;
    }
    
    // Calculate column sums
    for (int j = 0; j <= col; j++) {
        int sumCol = 0;
        for (int i = 0; i < row; i++) {
            sumCol += augary[i][j];
        }
        augary[row][j] = sumCol;
    
    }
    }//Sum rows,col,grand total

void print(const int a[][COLMAX],int row,int col ,int width){
    width = 10;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            cout << setw(width) << a[i][j];
        }
        cout << endl;
    }
    
}//Either table can be printed
