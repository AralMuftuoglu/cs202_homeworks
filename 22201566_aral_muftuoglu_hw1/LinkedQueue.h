/**
** Title: BST
** Author : Aral Muftuoglu
** ID: 22201566
** Section : 3
** Homework : 1
** Description : LinkedQueue implementation
*/

#ifndef LINKEDQUEUE_H
#define LINKEDQUEUE_H

#include <iostream>
#include "Node.h"

using namespace std;

template <class ItemType>
class LinkedQueue {
private:
    Node<ItemType>* frontPtr;
    Node<ItemType>* backPtr;
    int size; // To track the number of items in the queue

public:
    LinkedQueue();
    LinkedQueue(const LinkedQueue& aQueue);
    ~LinkedQueue();

    bool isEmpty() const;
    bool enqueue(const ItemType& newEntry);
    bool dequeue();
    ItemType peekFront() const;
    int getSize() const; // Method to return the size of the queue
};

// default constructor
template<class ItemType>
LinkedQueue<ItemType>::LinkedQueue() {
    frontPtr = nullptr;
    backPtr = nullptr;
    size = 0; // Initialize size to 0
}

// copy constructor
template<class ItemType>
LinkedQueue<ItemType>::LinkedQueue(const LinkedQueue& aQueue) {
    frontPtr = nullptr;
    backPtr = nullptr;
    size = 0; // Initialize size to 0

    if (aQueue.isEmpty()) {
        return;
    } else {
        Node<ItemType>* tempNode = aQueue.frontPtr;
        while (tempNode != nullptr) {
            enqueue(tempNode->getItem());
            tempNode = tempNode->getNext();
        }
    }
}

// destructor
template<class ItemType>
LinkedQueue<ItemType>::~LinkedQueue() {
    while(!isEmpty()) {
        dequeue();
    }
}

// isEmpty method
template<class ItemType>
bool LinkedQueue<ItemType>::isEmpty() const {
    return frontPtr == nullptr;
}

// peekFront method
template<class ItemType>
ItemType LinkedQueue<ItemType>::peekFront() const {
    if (isEmpty()) {
        cout << "The queue is empty." << endl;
        return nullptr; // Return nullptr for pointer types
    }
    return frontPtr->getItem();
}


// enqueue method
template<class ItemType>
bool LinkedQueue<ItemType>::enqueue(const ItemType &newEntry) {
    Node<ItemType>* newNodePtr = new Node<ItemType>(newEntry);

    if(isEmpty()) {
        frontPtr = newNodePtr;
    } else {
        backPtr->setNext(newNodePtr);
    }

    backPtr = newNodePtr;
    size++; // Increment the size when a new item is added
    return true;
}

// dequeue method
template<class ItemType>
bool LinkedQueue<ItemType>::dequeue() {
    bool result = false;

    if(!isEmpty()) {
        Node<ItemType>* nodeToDeletePtr = frontPtr;

        if(frontPtr == backPtr) {
            frontPtr = nullptr;
            backPtr = nullptr;
        } else {
            frontPtr = frontPtr->getNext();
        }

        nodeToDeletePtr->setNext(nullptr);
        delete nodeToDeletePtr;
        size--; // Decrement the size when an item is removed
        result = true;
    }
    return result;
}

// getSize method
template<class ItemType>
int LinkedQueue<ItemType>::getSize() const {
    return size; // Return the current size of the queue
}

#endif //LINKEDQUEUE_H
