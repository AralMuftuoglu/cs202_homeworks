/**
** Title: BST
** Author : Aral Muftuoglu
** ID: 22201566
** Section : 3
** Homework : 1
** Description : BSTNode implementation
*/

#ifndef TREENODE_H
#define TREENODE_H

class BSTNode {
private:
    int item;
    BSTNode *leftChildPtr;
    BSTNode *rightChildPtr;

public:
    // constructor
    BSTNode(int nodeItem, BSTNode *left = nullptr, BSTNode *right = nullptr) {
        item = nodeItem;
        leftChildPtr = left;
        rightChildPtr = right;
    }

    // getter for item
    int getItem() {
        return item;
    }

    // setter for item
    void setItem(int newItem) {
        item = newItem;
    }

    // getter for left child
    BSTNode *getLeftChild() {
        return leftChildPtr;
    }

    // getter for right child
    BSTNode *getRightChild() {
        return rightChildPtr;
    }

    // setter for left child
    void setLeftChild(BSTNode *left) {
        leftChildPtr = left;
    }

    // setter for right child
    void setRightChild(BSTNode *right) {
        rightChildPtr = right;
    }
};
#endif // TREENODE_H
