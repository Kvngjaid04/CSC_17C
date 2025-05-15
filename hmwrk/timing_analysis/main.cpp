/* 
 * File:   main.cpp
 * Author: Ireoluwa
 * Created on May 9, 2025, 5:34 PM
 * Note: Heap, Quick, and Shell sort implementations are from GeeksforGeeks
 */
#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
#include <fstream>
using namespace std;
using namespace std::chrono;

//User Libraries

//Global Constants - Mathematical, Scientific, Conversions
//Higher Dimensions go here. No Variables

//Function Prototypes
void hpSort(int arr[], int n);
void qkSort(int arr[], int n);
void shSort(int arr[], int n);
void mgSort(int arr[], int n);
void genRand(int arr[], int n);
void setSizs(vector<int>& sizes, int numSiz, int maxSiz);
void savCSV(const vector<int>& sizes, const vector<float>& hpTims, 
           const vector<float>& qkTims, const vector<float>& shTims,
           const vector<float>& mgTims, int numSiz);

//Execution Begins here
int main(int argc, char** argv) {
    //Setting the random number seed
    srand(static_cast<unsigned>(time(0)));
    //Declaring Variables
    const int NUMRUN = 5;    // Number of runs for each size to average
    const int MAXSIZ = 100000; // Maximum array size
    const int NUMSIZ = 40;   // Number of different sizes to test
    //Initialize Variables
    vector<int> sizes;  setSizs(sizes, NUMSIZ, MAXSIZ);
    // Arrays to store timing results
    vector<float> hpTims(NUMSIZ, 0); vector<float> qkTims(NUMSIZ, 0);
    vector<float> shTims(NUMSIZ, 0); vector<float> mgTims(NUMSIZ, 0);
    for (int i = 0; i < NUMSIZ; i++) {
        int n = sizes[i];  int* arr = new int[n];     int* arrCp1 = new int[n];
        int* arrCp2 = new int[n];                     int* arrCp3 = new int[n];
        cout << "Testing array size: " << n << endl;
        // Run multiple times and take average
        for (int run = 0; run < NUMRUN; run++) {
            genRand(arr, n);   // Generate random array
             // Make copies
            copy(arr, arr + n, arrCp1); 
            copy(arr, arr + n, arrCp2); copy(arr, arr + n, arrCp3);
            // Time sorts
            auto start = high_resolution_clock::now(); hpSort(arr, n);
            auto stop = high_resolution_clock::now();
            duration<float, milli> hpTime = stop - start;
            hpTims[i] += hpTime.count();
            
            start = high_resolution_clock::now(); qkSort(arrCp1, n);
            stop = high_resolution_clock::now();
            duration<float, milli> qkTime = stop - start;
            qkTims[i] += qkTime.count();
            
            start = high_resolution_clock::now();   shSort(arrCp2, n);
            stop = high_resolution_clock::now();
            duration<float, milli> shTime = stop - start;
            shTims[i] += shTime.count();
            
            start = high_resolution_clock::now();   mgSort(arrCp3, n);
            stop = high_resolution_clock::now();
            duration<float, milli> mgTime = stop - start;
            mgTims[i] += mgTime.count(); }
        // Calculate average times
    hpTims[i]/=NUMRUN; qkTims[i]/=NUMRUN; shTims[i]/=NUMRUN; mgTims[i]/=NUMRUN;
    // Clean up   
    delete[] arr; delete[] arrCp1; delete[] arrCp2; delete[] arrCp3;} 
    //Processing/Mapping Inputs to Outputs
    savCSV(sizes, hpTims, qkTims, shTims, mgTims, NUMSIZ);
    //Exiting stage left/right
    return 0;}   


// Function to set up test sizes
void setSizs(vector<int>& sizes, int numSiz, int maxSiz) {
    for (int i = 0; i < numSiz; i++) {
        sizes.push_back((i + 1) * maxSiz / numSiz);
    }
}

// Function to save results to CSV
void savCSV(const vector<int>& sizes, const vector<float>& hpTims, 
           const vector<float>& qkTims, const vector<float>& shTims,
           const vector<float>& mgTims, int numSiz) {
    ofstream outFile("Timing_analysis.csv");
    outFile <<"Array Size, Heap Sort, Quick Sort, Shell Sort, Merge Sort"<<endl;
    for (int i = 0; i < numSiz; i++) {
        outFile << sizes[i] << "," << hpTims[i] << "," << qkTims[i] 
                << "," << shTims[i] << "," << mgTims[i] << endl;
    }
    outFile.close();
    cout << "Done" << endl;
}

// Generate random array
void genRand(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % (n * 10) + 1;  // Random number between 1 and n*10
    }
}

// HeapSort implementation from GeeksforGeeks
void hpSort(int arr[], int n) {
    // Convert array to vector
    vector<int> v(arr, arr + n);

    // Convert vector to Max Heap
    make_heap(v.begin(), v.end());

    // Sort Max Heap
    sort_heap(v.begin(), v.end());

    // Copy sorted vector back to array
    copy(v.begin(), v.end(), arr);
}

// QuickSort implementation from GeeksforGeeks
int partn(vector<int> &vec, int low, int high) {
    // Selecting last element as the pivot
    int pivot = vec[high];

    // Index of element just before the last element
    // It is used for swapping
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        // If current element is smaller than or equal to pivot
        if (vec[j] <= pivot) {
            i++;
            swap(vec[i], vec[j]);
        }
    }

    // Put pivot to its position
    swap(vec[i + 1], vec[high]);

    // Return the point of partition
    return (i + 1);
}

void qSort(vector<int> &vec, int low, int high) {
    // Base case: This part will be executed till the starting
    // index low is lesser than the ending index high
    if (low < high) {
        // pi is Partitioning Index, arr[p] is now at right place
        int pi = partn(vec, low, high);

        // Separately sort elements before and after the Partition Index pi
        qSort(vec, low, pi - 1);
        qSort(vec, pi + 1, high);
    }
}

// Function to convert array to vector for QuickSort
void qkSort(int arr[], int n) {
    vector<int> vec(arr, arr + n);
    qSort(vec, 0, n - 1);
    copy(vec.begin(), vec.end(), arr);
}

// ShellSort implementation from GeeksforGeeks
void shSort(int arr[], int n) {
    // Start with a big gap, then reduce the gap
    for (int gap = n/2; gap > 0; gap /= 2) {
        // Do a gapped insertion sort for this gap size.
        for (int i = gap; i < n; i += 1) {
            // add a[i] to the elements that have been gap sorted
            // save a[i] in temp and make a hole at position i
            int temp = arr[i];

            // shift earlier gap-sorted elements up until the correct 
            // location for a[i] is found
            int j;            
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
                arr[j] = arr[j - gap];
            
            //  put temp (the original a[i]) in its correct location
            arr[j] = temp;
        }
    }
    //return 0;
}

// Merge function for MergeSort
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temp arrays
    int* L = new int[n1];
    int* R = new int[n2];

    // Copy data to temp arrays
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    // Merge the temp arrays back into arr[left..right]
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], if there are any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if there are any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    delete[] L;
    delete[] R;
}

void mSort(int arr[], int left, int right) {
    if (left < right) {
        //  avoids overflow for large left and right
        int mid = left + (right - left) / 2;

        // Sort first and second halves
        mSort(arr, left, mid);
        mSort(arr, mid + 1, right);

        // Merge the sorted halves
        merge(arr, left, mid, right);
    }
}

// Function to perform full merge sort on array
void mgSort(int arr[], int n) {
    mSort(arr, 0, n - 1);
}