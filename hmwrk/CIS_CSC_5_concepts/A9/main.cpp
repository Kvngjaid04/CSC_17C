/* 
 * File:   main.cpp
 * Author: Ireoluwa Dairo
 * Created on August 3 12:36 pm
 * Purpose:  Input something, output it reversed with some modifications
 * Note:Range should be 5 digits, 321 = 00321 reverse = 12300 before subtraction
 *      12300 - 999 = 11301 after subtraction
 *      12300 = 00321 = 321 after reversal and no subtraction
 */

//System Libraries Here
#include <iostream>//cin,cout,endl
#include <cstring> //strlen()
using namespace std;
//User Libraries Here

//Global Constants Only, No Global Variables
//Like PI, e, Gravity, or conversions

//Function Prototypes Here
bool  inRange(const char [],unsigned short &);
bool  reverse(unsigned short,signed short &);
short subtrct(signed short,int);

//Program Execution Begins Here
int main(int argc, char** argv) {
    
    //Declare all Variables Here
    const int SIZE=80;     //More than enough
    char  digits[SIZE];    //Character digits or not
    unsigned short unShort;//Unsigned short
    short snShort;         //Signed short
    
    //Input or initialize values Here
    cout<<"Reverse a number and subtract if possible."<<endl;
    cout<<"Input a number in the range of an unsigned short"<<endl;
    cin>>digits;
    
    //Test if it is in the Range of an unsigned short
    if(!inRange(digits,unShort)){
        cout<<"No Conversion Possible"<<endl;
        return 0;
    }
    
    //Reverse and see if it falls in the range of an signed short
    if(!reverse(unShort,snShort)){
        cout<<"No Conversion Possible"<<endl;
        return 0;
    }
    
    //Now subtract if the result is not negative else don't subtract
    snShort=subtrct(snShort,999);
    
    //Output the result
    cout<<snShort<<endl;
    
    //Exit
    return 0;
}

bool  inRange(const char a[],unsigned short &n){
      n = 0;
    int length = strlen(a);
    if (length > 5) return false;
    if (length == 5 && strcmp(a, "65535") > 0) return false;
    for (int i = 0; i < length; i++) {
        if (a[i] < '0' || a[i] > '9') {
            return false; // Not a digit
        }
        n = n * 10 + (a[i] - '0');
        if (n > 65535) {return false;}
    }
    return true;
    }//Output true,unsigned or false

bool reverse(unsigned short unShort, signed short &snShort) {
    int temp = 0;
    int dgtsCnt = 0;
    while (unShort > 0) {
        temp = temp * 10 + (unShort % 10);
        unShort /= 10;
        dgtsCnt++;
    }
    
    // If reversed number has fewer than 5 digits, pad with zeros
    while (dgtsCnt < 5) {
        temp *= 10;
        dgtsCnt++;
    }
    
    // Check if the padded value is within the range of a signed short
    if (temp > 32767) {
        return false;
    }
    
    snShort = static_cast<signed short>(temp);
    return true;
}

short subtrct(signed short snShort, int value) {
    if (snShort - value >= 0) {
        return snShort - value;
    }
    return snShort;
    
}