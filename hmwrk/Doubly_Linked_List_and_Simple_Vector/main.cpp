/* 
 * File:   main.cpp
 * Author: Dr. Mark E. Lehr (Modified)
 * Created on September 16, 2020, 7:50 PM
 * Purpose:  To Test and Modify the Simple Vector with LinkedList
 */

//System Libraries
#include <iostream>
using namespace std;

//User Libraries
#include <iostream>
#include <string>
#include <cassert>
#include "DoublyLinkedList.h"
#include "SortedLinkedList.h"
#include "LRUCache.h"

using namespace std;

// Test the DoublyLinkedList class
void testDoublyLinkedList() {
    cout << "Testing DoublyLinkedList" << endl;
    
    DoublyLinkedList<int> list;
    
    // Test push operations
    list.push_back(10);
    list.push_back(20);
    list.push_front(5);
    list.push_back(30);
    list.push_front(1);
    
    cout << "Initial list:" << endl;
    list.printListForward();
    list.printListBackward();
    
    // Verify size
    assert(list.size() == 5);
    
    // Test access operators
    assert(list[0] == 1);
    assert(list[1] == 5);
    assert(list[2] == 10);
    assert(list[3] == 20);
    assert(list[4] == 30);
    
    // Test pop operations
    list.pop_front();
    list.pop_back();
    
    // Test insert and remove
    list.insert(1, 7);
    list.remove(2);
    
    // Test copy constructor
    DoublyLinkedList<int> listCopy(list);
    
    // Test assignment operator
    DoublyLinkedList<int> listAssign;
    listAssign = list;
    
    cout << "Final list state:" << endl;
    list.printListForward();
    
    // Test destruction
    list.destroyList();
    assert(list.size() == 0);
    
    cout << "DoublyLinkedList test: passed" << endl;
}

// Test the SortedLinkedList class
void testSortedLinkedList() {
    cout << "Testing SortedLinkedList" << endl;
    
    SortedLinkedList<int> list;
    
    // Test insertion
    list.insert(30);
    list.insert(10);
    list.insert(50);
    list.insert(20);
    list.insert(40);
    
    cout << "Initial sorted list:" << endl;
    list.printListForward();
    
    // Verify sorting
    assert(list.isSorted());
    
    // Test push_front and push_back (should maintain sort order)
    list.push_front(5);
    list.push_back(60);
    
    // Verify sorting again
    assert(list.isSorted());
    
    // Test duplicates
    list.insert(30);
    list.insert(30);
    
    cout << "Final sorted list with duplicates:" << endl;
    list.printListForward();
    
    // Verify sorting with duplicates
    assert(list.isSorted());
    
    cout << "SortedLinkedList test: passed" << endl;
}

// Test the LRUCache class
void testLRUCache() {
    cout << "Testing LRUCache" << endl;
    
    LRUCache<string, int> cache(3);  // Cache with capacity 3
    
    // Test put
    cache.put("one", 1);
    cache.put("two", 2);
    cache.put("three", 3);
    
    // Test get (should move "one" to front)
    int value = cache.get("one");
    assert(value == 1);
    
    // Test eviction (adding beyond capacity)
    cache.put("four", 4);
    
    // Verify "two" was evicted
    try {
        cache.get("two");
        assert(false); // Should not reach here
    } catch (const std::out_of_range&) {
        // Expected exception
    }
    
    // Test updating existing key
    cache.put("one", 10);
    assert(cache.get("one") == 10);
    
    // Test order after multiple operations
    cache.get("three");
    
    // Test size and capacity
    assert(cache.size() <= cache.getCapacity());
    
    // Print final state for verification
    cout << "Final LRU Cache state" << endl;
    cache.print();
    
    cout << "LRUCache test: passed" << endl;
}

int main() {
    cout << "Running tests for all linked list implementations" << endl;
    cout << "LRU = Least Recently Used Cache (prioritized list by use: brings "
            "recently queried links to front)" << endl;
    
    // Run all tests
    testDoublyLinkedList();
    testSortedLinkedList();
    testLRUCache();
    
    return 0;
}