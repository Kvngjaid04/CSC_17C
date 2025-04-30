/*
 * File:   SortedLinkedList.h
 */

#ifndef SORTED_LINKED_LIST_H
#define SORTED_LINKED_LIST_H

#include "DoublyLinkedList.h"

template <class T>
class SortedLinkedList : public DoublyLinkedList<T> {
private:
    using typename DoublyLinkedList<T>::Node;
    using DoublyLinkedList<T>::head;
    using DoublyLinkedList<T>::tail;
    using DoublyLinkedList<T>::count;

public:
    // Constructor
    SortedLinkedList() : DoublyLinkedList<T>() {}
    
    // Insert an element in sorted order
    void insert(const T& value) {
        // If list is empty or value is smaller than the head
        if (head == nullptr || value < head->data) {
            DoublyLinkedList<T>::push_front(value);
            return;
        }
        
        // If value is larger than the tail
        if (value >= tail->data) {
            DoublyLinkedList<T>::push_back(value);
            return;
        }
        
        // Find the insertion point
        Node* current = head;
        while (current != nullptr && current->data < value) {
            current = current->next;
        }
        
        // Insert before the current node
        Node* newNode = new Node(value, current, current->prev);
        current->prev->next = newNode;
        current->prev = newNode;
        count++;
    }
    
    // Override push_front and push_back to maintain sorted order
    void push_front(const T& value) {
        insert(value);
    }
    
    void push_back(const T& value) {
        insert(value);
    }
    
    // Check if the list is properly sorted
    bool isSorted() const {
        if (count <= 1) return true;
        
        Node* current = head;
        while (current->next != nullptr) {
            if (current->data > current->next->data) {
                return false;
            }
            current = current->next;
        }
        return true;
    }
};

#endif /* SORTED_LINKED_LIST_H */