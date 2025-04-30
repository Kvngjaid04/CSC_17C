/*
 * File:   LinkedList.h
 */

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>

template <class T>
class LinkedList {
private:
    // Node structure for linked list
    struct Node {
        T data;
        Node* next;
        
        // Constructor
        Node(const T& value, Node* nextPtr = nullptr) : data(value),
        next(nextPtr) {}
    };
    
    Node* head;  // Pointer to first node
    Node* tail;  // Pointer to last node
    int count;   // Number of elements
    
public:
    // Constructor
    LinkedList() : head(nullptr), tail(nullptr), count(0) {}
    
    // Destructor
    ~LinkedList() {
        dstryLst();
    }
    
    // Copy constructor
    LinkedList(const LinkedList<T>& other) : head(nullptr), tail(nullptr), 
            count(0) {
        Node* current = other.head;
        while (current != nullptr) {
            push_back(current->data);
            current = current->next;
        }
    }
    
    // Assignment operator
    LinkedList<T>& operator=(const LinkedList<T>& other) {
        if (this != &other) {
            dstryLst();
            Node* current = other.head;
            while (current != nullptr) {
                push_back(current->data);
                current = current->next;
            }
        }
        return *this;
    }
    
    // Add element to front
    void push_front(const T& value) {
        Node* newNode = new Node(value, head);
        head = newNode;
        
        if (tail == nullptr) {
            tail = newNode;
        }
        
        count++;
    }
    
    // Add element to back
    void push_back(const T& value) {
        Node* newNode = new Node(value);
        
        if (tail == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        
        count++;
    }
    
    // Remove element from front
    void pop_front() {
        if (head == nullptr) return;
        
        Node* temp = head;
        head = head->next;
        
        if (head == nullptr) {
            tail = nullptr;
        }
        
        delete temp;
        count--;
    }
    
    // Remove element from back
    void pop_back() {
        if (head == nullptr) return;
        
        if (head == tail) {
            delete head;
            head = tail = nullptr;
            count = 0;
            return;
        }
        
        Node* current = head;
        while (current->next != tail) {
            current = current->next;
        }
        
        delete tail;
        tail = current;
        tail->next = nullptr;
        count--;
    }
    
    // Access element at index
    T& operator[](int index) {
        if (index < 0 || index >= count) {
            throw std::out_of_range("Index out of range");
        }
        
        Node* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        
        return current->data;
    }
    
    // Const version of operator[]
    const T& operator[](int index) const {
        if (index < 0 || index >= count) {
            throw std::out_of_range("Index out of range");
        }
        
        Node* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        
        return current->data;
    }
    
    // Get size of list
    int size() const {
        return count;
    }
    
    // Print list
    void prntLst(int perLine = 1) const {
        std::cout << std::endl;
        Node* current = head;
        int i = 0;
        
        while (current != nullptr) {
            std::cout << current->data << " ";
            if ((i + 1) % perLine == 0) std::cout << std::endl;
            current = current->next;
            i++;
        }
        
        std::cout << std::endl;
    }
    
    // Destroy list
    void dstryLst() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        
        tail = nullptr;
        count = 0;
    }
};

#endif /* LINKEDLIST_H */