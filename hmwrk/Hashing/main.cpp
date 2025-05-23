/* 
 * File:   main.cpp
 * Author: Ireoluwa
 * Created on May 18, 2025, 11:05 PM
 */

#include <cstdlib>
#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <chrono>  //  chrono timing
using namespace std;
using namespace std::chrono;

//User Libraries

struct Node {
    string key;
    int val;
    Node* next;
    
    Node(const string& k, int v) : key(k), val(v), next(nullptr) {}
};

//Global Constants - Mathematical, Scientific, Conversions
//Higher Dimensions go here. No Variables

//Function Prototypes
string rndStr(int);                    // Generate random string of given length
void filAry(string[], int, int);       // Fill array with random strings
int linSrc(string[], int, string);     // Linear search in array
int binSrc(string[], int, string);     // Binary search in sorted array
bool hshSrc(Node*[], string, int);     // Hash table search
void insHsh(Node*[], string, int, int);// Insert into hash table
void freHsh(Node*[], int);             // Free hash table memory
void srtAry(string[], int);            // Sort array of strings
unsigned int DJBhash(const string&);   // Hash function for strings

//Execution Begins here
int main(int argc, char** argv) {
    //Setting the random number seed
    srand(static_cast<unsigned int>(time(0)));

    //Declaring Variables
      const int STLEN = 20;     // Length of each random string
    const int MINLP = 10000;    // Minimum search loop count for timing
    const int SZSTRT = 1000;    // Starting size of arrays
    const int SZINCR = 1000;    // Increment size for array sizes
    const int NUMSZ = 20;       // Number of sizes tested
    int sizes[NUMSZ];
    
    //Initialize Variables
    ofstream file("srch_res.csv");
    file << "Size,Linear,Binary,Hash" << endl;

    for (int i = 0; i < NUMSZ; i++) {
        sizes[i] = SZSTRT + i * SZINCR;
    }

    //Processing/Mapping Inputs to Outputs
    cout << "Search Algorithm Analysis\n";

    for (int i = 0; i < NUMSZ; i++) {
        int size = sizes[i];
        cout << "\nSize: " << size << endl;

        //Create and initialize arrays and hash table
        string* arr1 = new string[size];
        string* arr2 = new string[size];
        filAry(arr1, size, STLEN);
        copy(arr1, arr1 + size, arr2);
        srtAry(arr2, size);

        Node** hTbl = new Node*[size * 2]();
        for (int j = 0; j < size; j++) {
            insHsh(hTbl, arr1[j], j, size * 2);
        }

        int srchSz = MINLP;
        string* srchAr = new string[srchSz];
        for (int j = 0; j < srchSz / 2; j++) {
            srchAr[j] = arr1[rand() % size];
        }
        for (int j = srchSz / 2; j < srchSz; j++) {
            srchAr[j] = rndStr(STLEN);
        }

        // Linear Search Timing with chrono
        int loops = srchSz;
        float linTim = 0;
        while (linTim < 1000) { // run until ~1 second (1000ms)
            if (linTim > 0) {
                loops = static_cast<int>(loops * (1000.0f / linTim));
            }

            auto start = high_resolution_clock::now();
            for (int j = 0; j < loops; j++) {
                linSrc(arr1, size, srchAr[j % srchSz]);
            }
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<milliseconds>(stop - start);
            linTim = duration.count();

            if (linTim < 1000 && loops == srchSz) {
                delete[] srchAr;
                srchSz *= 2;
                srchAr = new string[srchSz];
                for (int j = 0; j < srchSz / 2; j++) {
                    srchAr[j] = arr1[rand() % size];
                }
                for (int j = srchSz / 2; j < srchSz; j++) {
                    srchAr[j] = rndStr(STLEN);
                }
            } else if (linTim > 0) {
                // microseconds per loop approx
                linTim = static_cast<float>(linTim) / loops * 1000; 
                break;
            }
        }

        // Binary Search Timing with chrono
        int bnLoop = loops * 10;
        auto start = high_resolution_clock::now();
        for (int j = 0; j < bnLoop; j++) {
            binSrc(arr2, size, srchAr[j % srchSz]);
        }
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        // ms per search
        float binTim = static_cast<float>(duration.count()) / bnLoop / 1000.0f; 

        // Hash Search Timing with chrono
        int hshLp = loops * 10;
        start = high_resolution_clock::now();
        for (int j = 0; j < hshLp; j++) {
            hshSrc(hTbl, srchAr[j % srchSz], size * 2);
        }
        stop = high_resolution_clock::now();
        duration = duration_cast<microseconds>(stop - start);
        // ms per search
        float hshTim = static_cast<float>(duration.count()) / hshLp / 1000.0f; 

        if (binTim == 0) binTim = 0.0001f;
        if (hshTim == 0) hshTim = 0.0001f;

        //Displaying Input/Output Information
        cout << "Linear: " << fixed << setprecision(6) << linTim <<" ms"<< endl;
        cout << "Binary: " << fixed << setprecision(6) << binTim <<" ms"<< endl;
        cout << "Hash:   " << fixed << setprecision(6) << hshTim <<" ms"<< endl;

        file << size << "," << linTim << "," << binTim << "," << hshTim << endl;

        //Cleanup
        delete[] arr1;
        delete[] arr2;
        delete[] srchAr;
        freHsh(hTbl, size * 2);
        delete[] hTbl;
    }

    cout << "\nResults saved to srch_res.csv" << endl;
    file.close();

    //Exiting stage left/right
    return 0;
}

// Function Implementations
string rndStr(int len) {
    static const char chars[] =
        "abcdefghijklmnopqrstuvwxyz"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "0123456789";

    string result;
    result.reserve(len);
    for (int i = 0; i < len; i++) {
        result += chars[rand() % (sizeof(chars) - 1)];
    }
    return result;
}

void filAry(string arr[], int n, int len) {
    for (int i = 0; i < n; i++) {
        arr[i] = rndStr(len);
    }
}

int linSrc(string arr[], int n, string val) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == val) return i;
    }
    return -1;
}

int binSrc(string arr[], int n, string val) {
    int low = 0, high = n - 1;
    while (low <= high) {
        int mid = (high + low) / 2;
        if (arr[mid] == val) return mid;
        else if (arr[mid] < val) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

void srtAry(string arr[], int n) {
    sort(arr, arr + n);
}

void insHsh(Node* tbl[], string key, int val, int size) {
    unsigned int idx = DJBhash(key) % size;
    Node* curr = tbl[idx];
    while (curr) {
        if (curr->key == key) {
            curr->val = val;
            return;
        }
        curr = curr->next;
    }
    Node* newNd = new Node(key, val);
    newNd->next = tbl[idx];
    tbl[idx] = newNd;
}

bool hshSrc(Node* tbl[], string key, int size) {
    unsigned int idx = DJBhash(key) % size;
    Node* curr = tbl[idx];
    while (curr) {
        if (curr->key == key) return true;
        curr = curr->next;
    }
    return false;
}

void freHsh(Node* tbl[], int size) {
    for (int i = 0; i < size; i++) {
        while (tbl[i]) {
            Node* temp = tbl[i];
            tbl[i] = tbl[i]->next;
            delete temp;
        }
    }
}

// Hash function
unsigned int DJBhash(const string& str)
{
    unsigned int hash = 0;
    for (size_t i = 0; i < str.length(); i++)
    {
        hash = (hash << 4) + str[i];
        unsigned int g = hash & 0xF0000000;
        if (g) {
            hash ^= g >> 24;
            hash &= ~g;
        }
    }
    return hash;
}