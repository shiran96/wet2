#include "hash_table.h"
#include "union_find.h"
#include <iostream>
#include <memory>

int main() {
    // create a hash map
    HashTable<int> map;


//    // insert some elements
//    map.put(std::make_shared<int>(10), 10);
//    map.put(std::make_shared<int>(20), 74);
//    map.put(std::make_shared<int>(30),30);
//    map.put(std::make_shared<int>(40), 40);
//
//    for (int i = 0; i < 40; ++i) {
//        map.put(std::make_shared<int>(i), i);
//    }


    // retrieve some elements
    std::shared_ptr<int> value1 = map.get(10);
    std::shared_ptr<int> value2 = map.get(74);
    std::shared_ptr<int> value3 = map.get(30);
    std::shared_ptr<int> value4 = map.get(40);
    std::shared_ptr<int> value5 = map.get(50);  // key not found
    std::shared_ptr<int> value6 = map.get(33);

    // print the retrieved elements
    std::cout << *value1 << std::endl;
    std::cout << *value2 << std::endl;
    std::cout << *value3 << std::endl;
    std::cout << *value4 << std::endl;
    if (value5) {
        std::cout << *value5 << std::endl;
    } else {
        std::cout << "nullptr" << std::endl;
    }
    std::cout << *value6 << std::endl;
    std::cout << map.getSize() << std::endl;
    std::cout << map.getNumOfElement() << std::endl;

    // remove some elements
    map.remove(20);
    map.remove(30);

    for (int i = 0; i < 10; ++i) {
        map.remove(i);
    }

    std::cout << map.getSize() << std::endl;
    std::cout << map.getNumOfElement() << std::endl;

    // retrieve the remaining elements
    value1 = map.get(10);
    value2 = map.get(20);  // key not found
    value3 = map.get(30);  // key not found
    value4 = map.get(40);

    // print the retrieved elements
    std::cout << *value1 << std::endl;
    if (value2) {
        std::cout << *value2 << std::endl;
    } else {
        std::cout << "nullptr" << std::endl;
    }
    if (value3) {
        std::cout << *value3 << std::endl;
    } else {
        std::cout << "nullptr" << std::endl;
    }
    std::cout << *value4 << std::endl;

    UnionFind<int> uf;

    // Test makeSet
    uf.makeSet(0, std::make_shared<int>(10));
    uf.makeSet(1, 20);
    uf.makeSet(2, 30);
    uf.makeSet(3, 40);
    uf.makeSet(4, 50);

    // Test findSet
    std::cout << uf.findSet(0) << std::endl; // Expected output: 10
    std::cout << uf.findSet(1) << std::endl; // Expected output: 20
    std::cout << uf.findSet(2) << std::endl; // Expected output: 30
    std::cout << uf.findSet(3) << std::endl; // Expected output: 40
    std::cout << uf.findSet(4) << std::endl; // Expected output: 50

    // Test unionSets
    uf.unionSets(0, 1);
    uf.unionSets(2, 3);
    uf.unionSets(0, 3);

    // Test findSet after union
    std::cout << uf.findSet(0) << std::endl; // Expected output: 10
    std::cout << uf.findSet(1) << std::endl; // Expected output: 10
    std::cout << uf.findSet(2) << std::endl; // Expected output: 10
    std::cout << uf.findSet(3) << std::endl; // Expected output: 10
    std::cout << uf.findSet(4) << std::endl; // Expected output: 50

    return 0;
    }


    return 0;
}
