#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <memory>
#include "NodeUF.h"

#define MIN_SIZE 64
#define NOT_EXIST -1

template <typename V>
class HashNode {
private:
    // key-value pair
    int key;
    std::shared_ptr<V> value;
    HashNode* next;

public:
    HashNode(){
        key = NOT_EXIST;
        value = nullptr;
        next = nullptr;
    }
    HashNode(int key, std::shared_ptr<V> value) :
            key(key), value(value), next(nullptr){};

    ~HashNode(){
        next = nullptr;
    }

    int getKey() const {
        return key;
    }

    std::shared_ptr<V> getValue() const {
        return value;
    }

    void setValue(std::shared_ptr<V> value) {
        this->value = value;
    }

    HashNode* getNext() const {
        return next;
    }

    void setNext(HashNode* next) {
        this->next = next;
    }

};

template <typename V>
class HashTable {
private:
    // hash table
    HashNode<V> **table;
    std::size_t size;
    std::size_t counter;


    void rehash();

public:
    HashTable(){
        size = MIN_SIZE;
        table = new HashNode<V>*[MIN_SIZE];
        counter = 0;

        for (std::size_t i = 0; i < size; ++i) {
            table[i] = nullptr;
        }
    }

    ~HashTable() {
        // destroy all nodes in the hash map
        for (std::size_t i = 0; i < size; ++i) {
            HashNode<V> *node = table[i];
            if (node != nullptr && node->getKey() != NOT_EXIST) {
                while (node) {
                    HashNode<V> *next = node->getNext();
                    delete node;
                    node = next;
                }
            }
        }
        delete[] table;
    }

    std::shared_ptr<V> get(int key);
    void put(int key, std::shared_ptr<V> value);
    void remove(int key);

    std::size_t getSize(){
        return size;
    }

    std::size_t getNumOfElement(){
        return counter;
    }
};
template <typename V>
std::shared_ptr<V> HashTable<V>::get(int key) {
    std::size_t hashValue = key % size;
    HashNode<V> *node = table[hashValue];
    if(node != nullptr && node->getKey() == NOT_EXIST){
        return nullptr;
    } else {
        while (node) {
            if (node->getKey() == key) {
                // key found, return the value
                return node->getValue();
            }
            node = node->getNext();
        }
    }
    // key not found
    return nullptr;
}

    template <typename V>
    void HashTable<V>::put(int key, std::shared_ptr<V> value) {
        std::size_t hashValue = key % size;
        HashNode<V> *node = table[hashValue];
        //HashNode<V> *temp = node;
        if(node != nullptr && node->getKey() != NOT_EXIST){
            while (node) {
                if (node->getKey() == key) {
                    return;
                }
                //temp = node;
                node = node->getNext();
            }
        }
        // key not found, insert a new node at the beginning of the list
        node = new HashNode<V>(key, value);
        node->setNext(table[hashValue]);
        table[hashValue] = node;
        counter ++;
//        delete temp;
        // check if rehashing is necessary
        rehash();
    }

    template <typename V>
    void HashTable<V>::remove(int key) {
        std::size_t hashValue = key % size;
        HashNode<V> *node = table[hashValue];
        HashNode<V> *prev = nullptr;
        if(node != nullptr && node->getKey() != NOT_EXIST){
            while (node) {
                if (node->getKey() == key) {
                    // key found, remove the node from the list
                    if (prev) {
                        prev->setNext(node->getNext());
                    } else {
                        table[hashValue] = node->getNext();
                    }
                    delete node;
                    break;
                }
                prev = node;
                node = node->getNext();
            }
        }
        counter --;
        // check if rehashing is necessary
        rehash();
    }

    template <typename V>
    void HashTable<V>::rehash() {
        // determine the new size of the table based on the number of elements
        std::size_t newSize = size;
        if (counter > size / 2) {
            newSize = size * 2;
        } else if (counter < size / 4 && size > MIN_SIZE) {
            newSize = size / 2;
        }
        if (newSize == size) {
            // no resizing necessary
            return;
        }

        // create a new table with the new size
        HashNode<V> **newTable = new HashNode<V> *[newSize];
        // initialize all elements of newTable to nullptr
        for (std::size_t i = 0; i < newSize; ++i) {
            newTable[i] = nullptr;
        }

        // rehash all elements from the current table into the new table
        for (std::size_t i = 0; i < size; ++i) {
            HashNode<V> *node = table[i];
            while (node) {
                std::size_t hashValue = node->getKey() % newSize;
                HashNode<V> *newNode = new HashNode<V>(node->getKey(), node->getValue());
                newNode->setNext(newTable[hashValue]);
                newTable[hashValue] = newNode;
                node = node->getNext();
            }
        }

        // destroy all nodes in the current table
        for (std::size_t i = 0; i < size; ++i) {
            HashNode<V> *node = table[i];
            while (node) {
                HashNode<V> *next = node->getNext();
                delete node;
                node = next;
            }
        }
        delete[] table;

        // update the table and size variables
        table = newTable;
        size = newSize;
    }



#endif