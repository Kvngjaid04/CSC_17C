/*
 * File:   DoublyLinkedList.h
 */

#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include <iostream>
#include <stdexcept>

template <class T>
class DoublyLinkedList {
protected:
    // Node structure for doubly linked list
    struct Node {
        T data;
        Node* next;
        Node* prev;
        
        // Constructor
        Node(const T& value, Node* nextPtr = nullptr, Node* prevPtr = nullptr) 
            : data(value), next(nextPtr), prev(prevPtr) {}
    };
    
    Node* head;  // Pointer to first node
    Node* tail;  // Pointer to last node
    int count;   // Number of elements
    
public:
    // Constructor
    DoublyLinkedList() : head(nullptr), tail(nullptr), count(0) {}
    
    // Destructor
    ~DoublyLinkedList() {
        destroyList();
    }
    
    // Copy constructor
    DoublyLinkedList(const DoublyLinkedList<T>& other) : head(nullptr), tail(nullptr), count(0) {
        Node* current = other.head;
        while (current != nullptr) {
            push_back(current->data);
            current = current->next;
        }
    }
    
    // Assignment operator
    DoublyLinkedList<T>& operator=(const DoublyLinkedList<T>& other) {
        if (this != &other) {
            destroyList();
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
        Node* newNode = new Node(value, head, nullptr);
        
        if (head != nullptr) {
            head->prev = newNode;
        }
        
        head = newNode;
        
        if (tail == nullptr) {
            tail = newNode;
        }
        
        count++;
    }
    
    // Add element to back
    void push_back(const T& value) {
        Node* newNode = new Node(value, nullptr, tail);
        
        if (tail != nullptr) {
            tail->next = newNode;
        }
        
        tail = newNode;
        
        if (head == nullptr) {
            head = newNode;
        }
        
        count++;
    }
    
    // Remove element from front
    void pop_front() {
        if (head == nullptr) return;
        
        Node* temp = head;
        head = head->next;
        
        if (head != nullptr) {
            head->prev = nullptr;
        } else {
            tail = nullptr; // List is now empty
        }
        
        delete temp;
        count--;
    }
    
    // Remove element from back
    void pop_back() {
        if (tail == nullptr) return;
        
        Node* temp = tail;
        tail = tail->prev;
        
        if (tail != nullptr) {
            tail->next = nullptr;
        } else {
            head = nullptr; // List is now empty
        }
        
        delete temp;
        count--;
    }

    // Remove node at a specific position
    void remove(int position) {
        if (position < 0 || position >= count) {
            throw std::out_of_range("Position out of range");
        }

        if (position == 0) {
            pop_front();
            return;
        }

        if (position == count - 1) {
            pop_back();
            return;
        }

        Node* current = head;
        for (int i = 0; i < position; i++) {
            current = current->next;
        }

        current->prev->next = current->next;
        current->next->prev = current->prev;
        delete current;
        count--;
    }

    // Insert a node at a specific position
    void insert(int position, const T& value) {
        if (position < 0 || position > count) {
            throw std::out_of_range("Position out of range");
        }

        if (position == 0) {
            push_front(value);
            return;
        }

        if (position == count) {
            push_back(value);
            return;
        }

        Node* current = head;
        for (int i = 0; i < position; i++) {
            current = current->next;
        }

        Node* newNode = new Node(value, current, current->prev);
        current->prev->next = newNode;
        current->prev = newNode;
        count++;
    }
    
    // Access element at index
    T& operator[](int index) {
        if (index < 0 || index >= count) {
            throw std::out_of_range("Index out of range");
        }
        
        // Optimize traversal by starting from the closest end
        Node* current;
        if (index <= count / 2) {
            // Start from head for first half
            current = head;
            for (int i = 0; i < index; i++) {
                current = current->next;
            }
        } else {
            // Start from tail for second half
            current = tail;
            for (int i = count - 1; i > index; i--) {
                current = current->prev;
            }
        }
        
        return current->data;
    }
    
    // Const version of operator[]
    const T& operator[](int index) const {
        if (index < 0 || index >= count) {
            throw std::out_of_range("Index out of range");
        }
        
        // Optimize traversal by starting from the closest end
        Node* current;
        if (index <= count / 2) {
            // Start from head for first half
            current = head;
            for (int i = 0; i < index; i++) {
                current = current->next;
            }
        } else {
            // Start from tail for second half
            current = tail;
            for (int i = count - 1; i > index; i--) {
                current = current->prev;
            }
        }
        
        return current->data;
    }
    
    // Get size of list
    int size() const {
        return count;
    }
    
    // Check if list is empty
    bool empty() const {
        return count == 0;
    }
    
    // Print list forward
    void printListForward(int perLine = 1) const {
        std::cout << "Forward: ";
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
    
    // Print list backward
    void printListBackward(int perLine = 1) const {
        std::cout << "Backward: ";
        Node* current = tail;
        int i = 0;
        
        while (current != nullptr) {
            std::cout << current->data << " ";
            if ((i + 1) % perLine == 0) std::cout << std::endl;
            current = current->prev;
            i++;
        }
        
        std::cout << std::endl;
    }
    
    // Destroy list
    void destroyList() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        
        tail = nullptr;
        count = 0;
    }
};

#endif /* DOUBLY_LINKED_LIST_H */