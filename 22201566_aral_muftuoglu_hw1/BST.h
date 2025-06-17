/**
** Title: BST
** Author : Aral Muftuoglu
** ID: 22201566
** Section : 3
** Homework : 1
** Description : BST header file
*/

#ifndef BST_H
#define BST_H

#include "BSTNode.h"

#include <iostream>

#include "LinkedQueue.h"
using namespace std;

class BST {
private:
    BSTNode* root;
    int BSTsize;

    void constructKey(int key);
    BSTNode* constructKeyHelper(BSTNode* node, int key);
    BSTNode* insertKeyHelper(BSTNode* node, int key);
    void deleteNode(BSTNode* &nodePtr);
    void deleteItem(BSTNode* &treePtr, int key);
    void processLeftmost(BSTNode* &nodePtr, int &replacementItem);
    void destroyTree(BSTNode* &treePtr);
    void maximumSumPathHelper(BSTNode* node, int currentSum, int& maxSum, string currentPath, string& maxPath);
    void displayInorderHelper(BSTNode *node, bool& checkFirst);
    void displayPostorderHelper(BSTNode *node, bool& checkFirst);

    BSTNode* lowestCommonAncestorHelper(BSTNode* node, int a, int b);
    bool nodeExists(BSTNode* current, int key);
    int findLevelHelper(BSTNode* node, int key, int level);


public:
    BST(int keys[], int size);
    ~BST();
    void insertKey(int key);
    void deleteKey(int key);
    void keyLevel(int key);
    void displayInorder();
    void displayPostorder();
    void findFullBTLevel();
    void lowestCommonAncestor(int A, int B);
    void maximumSumPath();
    void maximumWidth();

    BST();
    BSTNode* getRoot();
    int bstHeight(BSTNode* root);

};
#endif //BST_H
