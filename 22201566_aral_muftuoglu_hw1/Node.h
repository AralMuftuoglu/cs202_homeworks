/**
** Title: BST
** Author : Aral Muftuoglu
** ID: 22201566
** Section : 3
** Homework : 1
** Description : Node implementation for LinkedQueue
*/

#ifndef NODE_H
#define NODE_H


template <class ItemType>

class Node {
private:
    ItemType item;
    Node<ItemType> *next;
public:
    Node();
    Node(const ItemType& anItem);
    Node(const ItemType& anItem, Node<ItemType> *nextPtr);
    void setItem(const ItemType& anItem);
    void setNext(Node<ItemType> *nextPtr);
    ItemType getItem() const;
    Node<ItemType> *getNext() const;
};

//default constructor
template<class ItemType>
Node<ItemType>::Node() {
    next = nullptr;
    item = ItemType();
}

template<class ItemType>
Node<ItemType>::Node(const ItemType &anItem) {
    item = anItem;
    next = nullptr;
}

template<class ItemType>
Node<ItemType>::Node(const ItemType &anItem, Node<ItemType> *nextPtr) {
    item = anItem;
    next = nextPtr;
}

//set item method
template<class ItemType>
void Node<ItemType>::setItem(const ItemType &anItem) {
    item = anItem;
}

//set next method
template<class ItemType>
void Node<ItemType>::setNext(Node<ItemType> *nextPtr) {
    next = nextPtr;
}

//get item method
template<class ItemType>
ItemType Node <ItemType> ::getItem() const {
    return item;
}

//get next method
template<class ItemType>
Node<ItemType> *Node<ItemType>::getNext() const {
    return next;
}

#endif //NODE_H
