//
// Created by Shiran on 17/11/2022.
//

#ifndef WET1_AVLTREE_H
#define WET1_AVLTREE_H

#include <iostream>
#include "math.h"
#include <memory>

//Using the fact that class P have the operations of (=,<,>,==).
template<class T, class P>
class AVLTree{
private:
    friend class world_cup_t;
    struct Node{
        std::shared_ptr<T> m_data;
        P m_key;
        int m_height;
        Node* m_leftSon;
        Node* m_rightSon;
        int m_numOfRightSons;
        int m_numOfLeftSons;

        std::shared_ptr<T> getData() {
            return m_data;
        }

        void setData(std::shared_ptr<T> newData) {
            m_data.swap(newData);
        }
        //O(n)
        void deleteNode(Node* node){
            if(node== nullptr){
                return;
            }
            deleteNode(node->m_leftSon);
            deleteNode(node->m_rightSon);
            node= nullptr;
        }
        //O(n)
        ~Node(){
            m_leftSon= nullptr;
            m_rightSon= nullptr;
            deleteNode(this);
        };
    };

    Node* m_root;
    int m_size;

    int getHeight(Node* root) const{
        if(root== nullptr){
            return 0;
        }
        return root->m_height;
    }
    //O(n)
    void deleteAVLTree(Node* root){
        if(root== nullptr){
            return;
        }
        deleteAVLTree(root->m_leftSon);
        root->m_leftSon= nullptr;
        deleteAVLTree(root->m_rightSon);
        root->m_rightSon= nullptr;

        delete root;
    }

    int getBalanceFactor(Node* node){
        if(node->m_leftSon == nullptr && node->m_rightSon!= nullptr){
            return (-1)*(node->m_rightSon->m_height + 1);
        }
        else if (node->m_leftSon != nullptr && node->m_rightSon == nullptr) {
            return (node->m_leftSon->m_height+1);
        }
        else if (node->m_leftSon == nullptr && node->m_rightSon == nullptr){
            return 0;
        }
        else{
            return (node->m_leftSon->m_height)-(node->m_rightSon->m_height);
        }
    }

    Node* balance(Node* node){
        if(getBalanceFactor(node)<-1){
            if(getBalanceFactor(node->m_rightSon)==1){
                return RLRoot(node);
            }
            else{
                return RRRoll(node);
            }
        }
        else if (getBalanceFactor(node)>1){
            if (getBalanceFactor(node->m_leftSon)==-1){
                return LRRoll(node);
            }
            else{
                return LLRoll(node);
            }
        }
        return node;
    }

    Node* LLRoll(Node* node){
        Node* newRoot = node->m_leftSon;
        int temp1 =newRoot->m_numOfRightSons;
        node->m_leftSon=newRoot->m_rightSon;
        node->m_numOfLeftSons=temp1;
        newRoot->m_rightSon=node;
        newRoot->m_numOfRightSons=node->m_numOfLeftSons+1+node->m_numOfRightSons;
        initializeHeight(node);
        initializeHeight(newRoot);
        return newRoot;
    }

    Node* RRRoll (Node* node){
        Node* newRoot = node->m_rightSon;
        int temp1 =newRoot->m_numOfLeftSons;
        node->m_rightSon=newRoot->m_leftSon;
        node->m_numOfRightSons=temp1;
        newRoot->m_leftSon=node;
        newRoot->m_numOfLeftSons=node->m_numOfLeftSons+1+node->m_numOfRightSons;
        initializeHeight(node);
        initializeHeight(newRoot);
        return newRoot;
    }

    Node* LRRoll (Node* node){
        Node* temp = node->m_leftSon;
        Node* newRoot =temp->m_rightSon;
        int temp1 = newRoot->m_numOfRightSons;
        int temp2 = newRoot->m_numOfLeftSons;

        temp->m_rightSon=newRoot->m_leftSon;
        temp->m_numOfRightSons=temp2;

        node->m_leftSon=newRoot->m_rightSon;
        node->m_numOfLeftSons=temp1;

        newRoot->m_rightSon=node;
        newRoot->m_numOfRightSons=temp1+node->m_numOfRightSons+1;

        newRoot->m_leftSon=temp;
        newRoot->m_numOfLeftSons=temp2+temp->m_numOfLeftSons+1;

        initializeHeight(node);
        initializeHeight(temp);
        initializeHeight(newRoot);
        return newRoot;
    }

    Node* RLRoot (Node* node){
        Node* temp = node->m_rightSon;
        Node* newRoot= temp->m_leftSon;
        int temp1 = newRoot->m_numOfRightSons;
        int temp2 = newRoot->m_numOfLeftSons;

        temp->m_leftSon=newRoot->m_rightSon;
        temp->m_numOfLeftSons=temp1;

        node->m_rightSon=newRoot->m_leftSon;
        node->m_numOfRightSons=temp2;

        newRoot->m_rightSon=temp;
        newRoot->m_numOfRightSons=temp1+temp->m_numOfRightSons+1;

        newRoot->m_leftSon=node;
        newRoot->m_numOfLeftSons=temp2+node->m_numOfLeftSons+1;

        initializeHeight(node);
        initializeHeight(temp);
        initializeHeight(newRoot);
        return newRoot;
    }

    //Checking before that the node isn't here.
    //log(n)
    Node* insertNode (std::shared_ptr<T> newItem, P key, Node* root){
        //Creating new node.
        if (root== nullptr){
            root = new Node;
            root->m_leftSon= nullptr;
            root->m_rightSon= nullptr;
            root->m_height=0;
            root->m_data=newItem;
            root->m_key=key;
            root->m_numOfLeftSons=0;
            root->m_numOfRightSons=0;
        }
        else if(key < root->m_key){
            root->m_numOfLeftSons++;
            root->m_leftSon=insertNode(newItem,key,root->m_leftSon);
            root = balance(root);
        }
        else if(key>root->m_key){
            root->m_numOfRightSons++;
            root->m_rightSon=insertNode(newItem,key,root->m_rightSon);
            root = balance(root);
        }
        initializeHeight(root);
        return root;
    }

    //log(n)
    Node* goToMinimal(Node* root){
        if(root== nullptr){
            return nullptr;
        }
        else if(root->m_leftSon== nullptr){
            return root;
        }
        return goToMinimal(root->m_leftSon);
    }

    //log(n)
    Node* removeNode(P& key, Node* root){
        Node* temp;
        //Got to an end of the tree, and didn't find.
        if(root == nullptr){
            return nullptr;
        }
        //Searching for the right key.
        if(key<root->m_key){
            root->m_numOfLeftSons--;
            root->m_leftSon = removeNode(key,root->m_leftSon);
        }
        else if (key>root->m_key){
            root->m_numOfRightSons--;
            root->m_rightSon = removeNode(key,root->m_rightSon);
        }
            //There is 0 child.
        else if(root->m_leftSon== nullptr && root->m_rightSon== nullptr){
            temp=root;
            root= nullptr;
            delete temp;
        }
            //There is 2 children.
        else if(root->m_leftSon != nullptr && root->m_rightSon != nullptr){
            temp= goToMinimal(root->m_rightSon);
            //We'll put the data and key of the minimal in the place of the one we want to delete
            //and then try to delete him, while we want to end it when we find a leaf or node with 1 child.
            root->setData(temp->getData());
            root->m_key=temp->m_key;
            root->m_rightSon= removeNode(root->m_key,root->m_rightSon);
        }
        else if(root->m_rightSon== nullptr){
            temp = root;
            root=root->m_leftSon;
            delete temp;
        }
        else if(root->m_leftSon== nullptr) {
            temp = root;
            root = root->m_rightSon;
            delete temp;
        }
        //Delete the only node in the tree.
        if(root== nullptr){
            return nullptr;
        }
        //Balancing the tree.
        root = balance(root);
        initializeHeight(root);
        return root;
    }
    //Putting the tree keys in order according to they key in the array.
    //O(n)
    void readingInOrder(Node* node, P* array, int& place){
        if (node != nullptr){
            readingInOrder(node->m_leftSon, array, place);
            array[place]=node->m_key;
            ++place;
            readingInOrder(node->m_rightSon, array, place);
        }
    }
    //Putting the tree data in order according to they key in the array.
    //O(n)
    void readingInOrderData(Node* node, std::shared_ptr<T>* array, int& place) {
        if (node != nullptr) {
            readingInOrderData(node->m_leftSon, array, place);
            array[place] = node->m_data;
            ++place;
            readingInOrderData(node->m_rightSon, array, place);
        }
    }
    //O(3r)-r is end-start
    void readingInOrderDataSliced(Node* node, std::shared_ptr<T>* array, int& place, int start, int end){
        if (node != nullptr) {
            if(node->m_key<=end && node->m_key>=start) {
                readingInOrderDataSliced(node->m_leftSon, array, place, start, end);
                array[place] = node->m_data;
                ++place;
                readingInOrderDataSliced(node->m_rightSon, array, place, start, end);
            }
        }
    }

    void initializeHeight(Node* root){
        if(root->m_leftSon!= nullptr && root->m_rightSon!= nullptr) {
            root->m_height = std::max(getHeight(root->m_leftSon), getHeight(root->m_rightSon)) + 1;
        }
        else if(root->m_leftSon != nullptr && root->m_rightSon == nullptr){
            root->m_height = getHeight(root->m_leftSon) + 1;
        }
        else if(root->m_rightSon != nullptr && root->m_leftSon == nullptr){
            root->m_height = getHeight(root->m_rightSon) + 1;
        }
        else{
            root->m_height=0;
        }
    }
    //log(n)
    Node* findNode(Node* root, P key){
        if(root== nullptr){
            return nullptr;
        }
        if(root->m_key==key){
            return root;
        }
        else if(key<root->m_key){
            return findNode(root->m_leftSon, key);
        }
        else if(key>root->m_key){
            return findNode(root->m_rightSon, key);
        }
        //Won't get here
        return nullptr;
    }

    Node* findNodeRank(Node* root, int rank){
        if(root== nullptr){
            return nullptr;
        }
        if(root->m_numOfLeftSons==rank){
            return root;
        } else if(root->m_numOfLeftSons<rank){
            return findNodeRank(root->m_rightSon, rank-root->m_numOfLeftSons-1);
        }
        else if(root->m_numOfLeftSons>rank){
            return findNodeRank(root->m_leftSon, rank);
        }
        return nullptr;
    }
    //O(n)
    Node* sortedArrayToAVLTree(std::shared_ptr<T>* newTreeData,P* newTreeKeys, Node* root, int start, int end){
        if (start > end)
            return nullptr;
        //Splitting the array
        int mid = (start + end)/2;
        if(root == nullptr) {
            root = new Node;
            root->m_rightSon= nullptr;
            root->m_leftSon= nullptr;
        }
        root->m_key=newTreeKeys[mid];
        root->m_data=newTreeData[mid];
        //I will be balanced because we all the time make sure we have exactly (+-1) the same number of nudes each side.
        root->m_leftSon= sortedArrayToAVLTree(newTreeData, newTreeKeys, root->m_leftSon, start, mid-1);
        root->m_rightSon= sortedArrayToAVLTree(newTreeData, newTreeKeys, root->m_rightSon, mid+1, end);
        //n actions in recursion.
        initializeHeight(root);
        return root;
    }
    //log(n)
    Node* getFatherNode(Node* root, P key){
        if(root->m_rightSon == nullptr && root->m_leftSon == nullptr){
            return nullptr;
        }
        else if(root->m_rightSon != nullptr && root->m_rightSon->m_key==key){
            return root;
        }
        else if(root->m_leftSon != nullptr && root->m_leftSon->m_key==key){
            return root;
        }
        else if (root->m_rightSon != nullptr && root->m_key<key){
            return getFatherNode(root->m_rightSon,key);
        }
        else if(root->m_leftSon != nullptr && root->m_key>key){
            return getFatherNode(root->m_leftSon, key);
        }
        return nullptr;
    }

    int getNodeRank(P key, Node* root){
        if(root == nullptr){
            return 0;
        }
        if(root->m_key>key){
            return getNodeRank(key, root->m_leftSon);
        } else if(root->m_key< key){
            return root->m_numOfLeftSons+1+ getNodeRank(key,root->m_rightSon);
        }
        else if(root->m_key==key){
            return root->m_numOfLeftSons+1;
        }
        return 0;
    }
public:
    AVLTree() : m_root(nullptr), m_size(0){};

    AVLTree(const AVLTree<T,P>& tree) = delete;
    //O(n)
    ~AVLTree(){
        if(m_root == NULL)
            return;
        deleteAVLTree(m_root->m_leftSon);
        deleteAVLTree(m_root->m_rightSon);
        delete m_root;
        m_root= nullptr;
    }
    //(log(n))
    void insert(std::shared_ptr<T> newItem, P key){
        if(find(key) == nullptr) {
            m_root = insertNode(newItem, key, m_root);//log(n)
            ++m_size;
        }

    }
    //(log(n))
    void remove(P key)
    {

        if(find(key) != nullptr) {
            m_root = removeNode(key, m_root);
            --m_size;
        }
    }
    //(log(n))
    std::shared_ptr<T> find(P key){
        Node* temp = findNode(m_root, key);
        if (temp!= nullptr){
            return temp->m_data;
        }
        else{
            return nullptr;
        }
    }
    //(1)
    int sizeOfTree() const{
        if(m_root== nullptr){
            return 0;
        }
        return m_size;
    }
    //O(n)
    void putDataOnArray(P* array) {
        //Assuming the array is in the correct size.
        int place =0;
        readingInOrder(m_root, array,place);
    }
    //O(n)
    int putDataOnArraySliced(std::shared_ptr<T>* array, P start, P end){
        int place =0;
        readingInOrderDataSliced(m_root, array, place, start, end);
        return place;
    }
    //O(n)
    void putItemsOnArray(std::shared_ptr<T>* array){
        int place =0;
        readingInOrderData(m_root, array, place);
    }

    //combining 2 trees but override the current tree. (n_1+n_2)
    void combineTrees(AVLTree<T,P>* tree1, AVLTree<T,P>* tree2){
        //This tree array.
        int sizeCurr=tree1->sizeOfTree();
        std::shared_ptr<T>* tree1Data;
        tree1Data=new std::shared_ptr<T>[sizeCurr];
        int place=0;
        readingInOrderData(tree1->m_root, tree1Data, place);//(n_1)
        place=0;
        P* tree1Keys;
        tree1Keys = new P[sizeCurr];
        readingInOrder(tree1->m_root,tree1Keys, place);

        //Second tree array.
        int sizeTree=tree2->sizeOfTree();
        std::shared_ptr<T>* tree2Data;
        tree2Data=new std::shared_ptr<T>[sizeTree];
        place=0;
        readingInOrderData(tree2->m_root, tree2Data, place);//(n_2)
        place=0;
        P* tree2Keys;
        tree2Keys=new P[sizeTree];
        readingInOrder(tree2->m_root,tree2Keys, place);

        //Merging. - (n_1+n_2)
        std::shared_ptr<T>* newTreeData;
        newTreeData=new std::shared_ptr<T>[sizeCurr+sizeTree];
        P* newTreeKeys;
        newTreeKeys=new P[sizeCurr+sizeTree];
        int i=0, j=0, k=0;
        while(i<sizeCurr && j<sizeTree){
            if(tree2Keys[j]<tree1Keys[i]){
                newTreeKeys[k]=tree2Keys[j];
                newTreeData[k]=tree2Data[j];
                k++;
                j++;
            }
            else{
                newTreeKeys[k]=tree1Keys[i];
                newTreeData[k]=tree1Data[i];
                k++;
                i++;
            }
        }
        while(i<sizeCurr){
            newTreeKeys[k]=tree1Keys[i];
            newTreeData[k]=tree1Data[i];
            k++;
            i++;
        }
        while(j<sizeTree){
            newTreeKeys[k]=tree2Keys[j];
            newTreeData[k]= tree2Data[j];
            k++;
            j++;
        }
        //Putting the new tree in the current tree. (n_1+n_2)
        m_root=sortedArrayToAVLTree(newTreeData, newTreeKeys, m_root, 0, sizeCurr+sizeTree-1);
        //Must remember to delete the second tree and update stats if needed.
        m_size=tree1->m_size+tree2->m_size;
        delete[] tree1Keys;
        delete[] tree2Keys;
        delete[] tree1Data;
        delete[] tree2Data;
        delete[] newTreeData;
        delete[] newTreeKeys;
    }
    //(2log(n))
    P getFather(P key){
        Node* father=getFatherNode(m_root,key);
        if(father== nullptr){
            return key;
        }
        return (father->m_key);
    }
    //(2log(n))
    bool amISonFromRight(P key){
        if(getFatherNode(m_root, key)->m_rightSon== nullptr){
            return false;
        }
        return (getFatherNode(m_root, key)->m_rightSon->m_key == key);
    }
    //Returns the key of the max node according to the key  - log(n)
    P* getMax(){
        if(m_root== nullptr){
            return nullptr;
        }
        Node* temp=m_root;
        while(temp->m_rightSon!= nullptr){
            temp=temp->m_rightSon;
        }
        return &temp->m_key;
    }
    int getRank(P key){
        if (find(key)){
            return getNodeRank(key, m_root)-1;
        }
        return -1;
    }

    std::shared_ptr<T> findFromRank(int rank){
        if(rank>m_size||rank<0){
            return nullptr;
        }
        else{
            return findNodeRank(m_root, rank)->m_data;
        }
    }
};

#endif //WET1_AVLTREE_H