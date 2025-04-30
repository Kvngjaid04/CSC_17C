/*
* File:   SimpleVector.h
 * Author: rcc
 Purpose: Simple Vector class that uses a LinkedList internally
 *          with dynamic resizing (2x growth, 1/4x shrink)
 * Created on September 16, 2020, 8:10 PM
 */


#ifndef SIMPLEVECTOR_H
#define SIMPLEVECTOR_H

#include "LinkedList.h"

template <class T>
class SimpleVector {
private:
    LinkedList<T> list;    // Internal linked list
    int arraySize;         // Current logical size
    int capacity;          // Current capacity
    
    // Method to resize the vector when needed
    void resize(int newCapacity) {
        // We don't actually need to allocate new memory since we're using a linked list
        // Just update the capacity
        capacity = newCapacity;
    }
    
public:
    // Constructor
    SimpleVector(int size) {
        arraySize = size;
        capacity = size;
        
        // Initialize the linked list with default values
        for (int i = 0; i < size; i++) {
            list.push_back(T());
        }
    }
    
    // Copy constructor
    SimpleVector(const SimpleVector<T>& other) {
        arraySize = other.arraySize;
        capacity = other.capacity;
        
        // Copy the linked list
        for (int i = 0; i < other.arraySize; i++) {
            list.push_back(other[i]);
        }
    }
    
    // Destructor
    ~SimpleVector() {
        // The LinkedList destructor will handle cleanup
    }
    
    // Size accessor
    int size() const {
        return arraySize;
    }
    
    // [] operator
    T& operator[](int index) {
        if (index < 0 || index >= arraySize) {
            throw std::out_of_range("Index out of range");
        }
        
        // Check if we need to grow the vector
        if (index >= capacity) {
            resize(capacity * 2);  // Double the capacity
        }
        
        // Check if we should shrink the vector (if using less than 1/4 of capacity)
        if (arraySize > 0 && capacity > 4 && arraySize <= capacity / 4) {
            resize(capacity / 2);  // Halve the capacity
        }
        
        return list[index];
    }
    
    // Const version of [] operator
    const T& operator[](int index) const {
        if (index < 0 || index >= arraySize) {
            throw std::out_of_range("Index out of range");
        }
        
        return list[index];
    }
    
    // Push back method (add element to end)
    void push_back(const T& value) {
        // Check if we need to grow the vector
        if (arraySize >= capacity) {
            resize(capacity * 2);  // Double the capacity
        }
        
        // If we're adding beyond current size, fill with default values
        while (list.size() < arraySize) {
            list.push_back(T());
        }
        
        list.push_back(value);
        arraySize++;
    }
    
    // Pop back method (remove last element)
    void pop_back() {
        if (arraySize <= 0) return;
        
        list.pop_back();
        arraySize--;
        
        // Check if we should shrink the vector
        if (arraySize > 0 && capacity > 4 && arraySize <= capacity / 4) {
            resize(capacity / 2);  // Halve the capacity
        }
    }
    
    // Push front method (add element to beginning)
    void push_front(const T& value) {
        // Check if we need to grow the vector
        if (arraySize >= capacity) {
            resize(capacity * 2);  // Double the capacity
        }
        
        list.push_front(value);
        arraySize++;
    }
    
    // Pop front method (remove first element)
    void pop_front() {
        if (arraySize <= 0) return;
        
        list.pop_front();
        arraySize--;
        
        // Check if we should shrink the vector
        if (arraySize > 0 && capacity > 4 && arraySize <= capacity / 4) {
            resize(capacity / 2);  // Halve the capacity
        }
    }
    
    // Print the vector - removed since we use prntVec function in main
};

#endif 