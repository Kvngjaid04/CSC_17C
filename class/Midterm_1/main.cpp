#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <iomanip>
#include <cmath>

// Binary Search implementation
bool binarySearch(const std::vector<int>& arr, int target) {
    int left = 0;
    int right = arr.size() - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == target) {
            return true;
        }
        
        if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return false;
}

int main() {
    const int MIN_SIZE = 1000;
    const int MAX_SIZE = 40000;
    const int NUM_SIZES = 40;
    const int ITERATIONS = 1000; // Run multiple iterations for more reliable timing
    
    // Open CSV file for output
    std::ofstream outputFile("binary_search_times.csv");
    outputFile << "Array_Size,Binary_Time(s),log2(Size)" << std::endl;
    
    // Generate 40 different array sizes
    for (int i = 0; i < NUM_SIZES; i++) {
        int size = MIN_SIZE + i * (MAX_SIZE - MIN_SIZE) / (NUM_SIZES - 1);
        
        // Create a sorted array of the current size
        std::vector<int> arr(size);
        for (int j = 0; j < size; j++) {
            arr[j] = j;
        }
        
        // Target that doesn't exist (worst case)
        int target = size;
        
        // Variable to store cumulative results
        double binaryTotalTime = 0.0;
        
        // Run multiple iterations
        for (int iter = 0; iter < ITERATIONS; iter++) {
            // Time Binary Search
            auto binaryStart = std::chrono::high_resolution_clock::now();
            binarySearch(arr, target);
            auto binaryEnd = std::chrono::high_resolution_clock::now();
            
            std::chrono::duration<double> binaryDuration = binaryEnd - binaryStart;
            binaryTotalTime += binaryDuration.count();
        }
        
        // Calculate average
        double binaryAvgTime = binaryTotalTime / ITERATIONS;
        
        // Calculate logarithm value for binary search analysis
        double log2Size = std::log2(size);
        
        // Output result to CSV
        outputFile << size << "," 
                  << std::fixed << std::setprecision(9) << binaryAvgTime << ","
                  << std::fixed << std::setprecision(6) << log2Size << std::endl;
        
        // Also print to console to monitor progress
        std::cout << "Completed size " << size << ": Binary = " 
                  << std::fixed << std::setprecision(9) << binaryAvgTime << "s, log2(Size) = "
                  << std::fixed << std::setprecision(6) << log2Size << std::endl;
    }
    
    outputFile.close();
    std::cout << "Results saved to binary_search_times.csv" << std::endl;
    
    return 0;
}