/*
 * File:   LRUCache.h
 * Implements a Least Recently Used (LRU) cache using a doubly linked list
 * Recently accessed items are moved to the front of the list
 */

#ifndef LRU_CACHE_H
#define LRU_CACHE_H

#include "DoublyLinkedList.h"
#include <unordered_map>

template <class K, class V>
class LRUCache {
private:
    // Node for the cache
    struct CacheNode {
        K key;
        V value;
        
        CacheNode(const K& k, const V& v) : key(k), value(v) {}
        
        // For comparison purposes
        bool operator==(const CacheNode& other) const {
            return key == other.key;
        }
        
        // For printing
        friend std::ostream& operator<<(std::ostream& os, const CacheNode& node) {
            os << "[" << node.key << ": " << node.value << "]";
            return os;
        }
    };
    
    DoublyLinkedList<CacheNode> list;                  // Store items in order of recency
    std::unordered_map<K, int> keyToIndex;             // Map keys to their position in the list
    int capacity;                                       // Maximum cache size
    
    // Update the index map after list changes
    void updateIndices() {
        keyToIndex.clear();
        for (int i = 0; i < list.size(); i++) {
            keyToIndex[list[i].key] = i;
        }
    }
    
public:
    // Constructor with default capacity of 10
    LRUCache(int cap = 10) : capacity(cap) {}
    
    // Check if key exists in cache
    bool exists(const K& key) const {
        return keyToIndex.find(key) != keyToIndex.end();
    }
    
    // Put a value in the cache
    void put(const K& key, const V& value) {
        CacheNode newNode(key, value);
        
        // If key already exists, remove it first
        if (exists(key)) {
            int index = keyToIndex[key];
            list.remove(index);
        } 
        // If at capacity, remove least recently used item (at the end)
        else if (list.size() >= capacity) {
            // Remove the key from the map first
            keyToIndex.erase(list[list.size() - 1].key);
            list.pop_back();
        }
        
        // Add new item to front (most recently used)
        list.push_front(newNode);
        updateIndices();
    }
    
    // Get a value from the cache
    V get(const K& key) {
        if (!exists(key)) {
            throw std::out_of_range("Key not found in cache");
        }
        
        int index = keyToIndex[key];
        V value = list[index].value;
        
        // Remove from current position
        list.remove(index);
        
        // Add to front (most recently used)
        CacheNode node(key, value);
        list.push_front(node);
        
        // Update indices
        updateIndices();
        
        return value;
    }
    
    // Get size of cache
    int size() const {
        return list.size();
    }
    
    // Get capacity of cache
    int getCapacity() const {
        return capacity;
    }
    
    // Print the cache
    void print() const {
        std::cout << "LRU Cache:" << std::endl;
        for (int i = 0; i < list.size(); i++) {
            std::cout << list[i] << " ";
        }
        std::cout << std::endl;
    }
};

#endif /* LRU_CACHE_H */