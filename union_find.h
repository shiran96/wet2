//
// Created by Shiran on 23/12/2022.
//

#ifndef WET2_DISJOINTSETFOREST_H
#define WET2_DISJOINTSETFOREST_H

#include "hash_table.h"
#include "NodeUF.h"

template <typename G, typename E>
class UnionFind {
public:
    UnionFind();
    std::shared_ptr<G> findSet(int key);
    void unionSets(int key1, int key2);

    HashTable<G>* groupTable;
    HashTable<E>* elementTable;
};

template <typename G, typename E>
UnionFind<G,E>::UnionFind() {}


template <typename G, typename E>
void UnionFind<G,E>::unionSets(int key1, int key2) {
    NodeUF<G> node1 = groupTable->get(findSet(key1));
    NodeUF<G> node2 = groupTable->get(findSet(key2));
    if (node1->parent == node2->parent) {
        return;
    }
    if (node1->rank > node2->rank) {
        node2->parent = node1;
        node1->size += node2->size;
    } else {
        node1->parent = node2;
        node2->size += node1->size;
        if (node1->rank == node2->rank) {
            node2->rank++;
        }
    }
}

template <typename G, typename E>
std::shared_ptr<G> UnionFind<G,E>::findSet(int key) {

    NodeUF<G>* node = elementTable->get(key);
    return node->findRoot(node)->group;
}




#endif //WET2_DISJOINTSETFOREST_H
