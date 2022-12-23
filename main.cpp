#include "hashtable.h"
#include <iostream>

int main() {
    HashTable<int> ht;

    ht.insert(5, 10);
    ht.insert(15, 20);
    ht.insert(25, 30);
    ht.insert(35, 40);

    std::cout << ht.search(5) << std::endl;
    std::cout << ht.search(15) << std::endl;
    std::cout << ht.search(25) << std::endl;
    std::cout << ht.search(35) << std::endl;
    std::cout << ht.search(45) << std::endl;

    ht.remove(15);

    std::cout << ht.search(5) << std::endl;
    std::cout << ht.search(15) << std::endl;
    std::cout << ht.search(25) << std::endl;
    std::cout << ht.search(35) << std::endl;
    std::cout << ht.search(45) << std::endl;

    return 0;
}
