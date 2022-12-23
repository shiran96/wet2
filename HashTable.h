#ifndef HASH_TABLE_H
#define HASH_TABLE_H

const int PRIME = 31;
const int DEFAULT_SIZE = 10;

template <typename V>
class HashTable {
public:
    HashTable(int size = DEFAULT_SIZE);
    ~HashTable();
    void insert(int key, V value);
    void remove(int key);
    V search(int key);

private:
    class HashEntry {
    public:
        HashEntry() : key(0), value(V()), isEmpty(true) {}
        HashEntry(int key, V value) : key(key), value(value), isEmpty(false) {}
        int key;
        V value;
        bool isEmpty;
    };


    int primaryHash(int key);
    int secondaryHash(int key);
    void resize(int newSize);

    HashEntry* array;
    int size;
    int numElements;
};

template <typename V>
HashTable<V>::HashTable(int size) : size(size), numElements(0) {
    array = new HashEntry[size];
}

template <typename V>
HashTable<V>::~HashTable() {
    delete[] array;
}

template <typename V>
void HashTable<V>::insert(int key, V value) {
    int initialPos = primaryHash(key);
    int pos = initialPos;
    int i = 0;
    while (!array[pos].isEmpty && array[pos].key != key) {
        pos = (initialPos + i * secondaryHash(key)) % size;
        i++;
        if (pos == initialPos) {
            resize(size * 2);
            insert(key, value);
            return;
        }
    }
    array[pos] = HashEntry(key, value);
    numElements++;
}

template <typename V>
void HashTable<V>::remove(int key) {
    int initialPos = primaryHash(key);
    int pos = initialPos;
    int i = 0;
    while (!array[pos].isEmpty && array[pos].key != key) {
        pos = (initialPos + i * secondaryHash(key)) % size;
        i++;
        if (pos == initialPos) {
            return;
        }
    }
    if (array[pos].isEmpty) {
        return;
    }
    array[pos].isEmpty = true;
    array[pos].key = 0;
    array[pos].value = V();
    numElements--;
    if (numElements <= size / 4) {
        resize(size / 2);
    }
}

template <typename V>
V HashTable<V>::search(int key) {
    int initialPos = primaryHash(key);
    int pos = initialPos;
    int i = 0;
    while (!array[pos].isEmpty && array[pos].key != key) {
        pos = (initialPos + i * secondaryHash(key)) % size;
        i++;
        if (pos == initialPos) {
            // Return default value if we have searched the entire array and not found the key
            return V();
        }
    }
    if (array[pos].isEmpty) {
        // Return default value if the key is not found
        return V();
    }
    // Return the value associated with the key
    return array[pos].value;
}

template <typename V>
int HashTable<V>::primaryHash(int key) {
    return key % size;
}

template <typename V>
int HashTable<V>::secondaryHash(int key) {
    return PRIME - (key % PRIME);
}

template <typename V>
void HashTable<V>::resize(int newSize) {
    HashEntry* oldArray = array;
    int oldSize = size;
    size = newSize;
    array = new HashEntry[size];
    numElements = 0;
    for (int i = 0; i < oldSize; i++) {
        if (!oldArray[i].isEmpty) {
            insert(oldArray[i].key, oldArray[i].value);
        }
    }
    delete[] oldArray;
}


#endif