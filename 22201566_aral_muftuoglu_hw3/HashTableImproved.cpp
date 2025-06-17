/**
* Title: Hash Table Improved
* Author : Aral Muftuoglu
* ID: 22201566
* Section : 3
* Homework : 3
* Description : HashTableImproved cpp file
*/

#include "HashTableImproved.h"
#include <iostream>
using namespace std;

//constructor for hash table
HashTableImproved::HashTableImproved() {
    int counter = 0;

    //initially all the slots are nullptr
    while (counter < size) {
        table[counter] = nullptr;
        counter++;
    }
}

//destructor for hash table
HashTableImproved::~HashTableImproved() {
    int counter = 0;

    while (counter < size) {
        Node* current = table[counter];

        while (current != nullptr) {
            Node* toDelete = current;
            current = (*current).next;
            delete toDelete;
        }
        counter++;
    }
}

//insert function
void HashTableImproved::insert(const string& item) {

    //calculating the sum of ascii values for every char
    int sumOfASCIIvalues = 0;
    for (char ch : item) {
        sumOfASCIIvalues+=ch;
    }

    //finding the initial index
    int initialIndex = sumOfASCIIvalues % size;

    Node* current = table[initialIndex];

    //check if the item is already in the chain to avoid duplication
    while (current != nullptr) {
        if ((*current).data == item) {
            cout << item << " is already registered as a weak spot." << endl;
            return;
        }
        current = (*current).next;
    }

    //if everything is okey, insert at the beginning of the chain
    Node* newNode = new Node;
    (*newNode).data = item;
    (*newNode).next = table[initialIndex];
    table[initialIndex] = newNode;

    cout << item << " is registered as a weak spot." << endl;
}

void HashTableImproved::remove(const string& item) {
    //calculating the sum of ascii values for every char
    int sumOfASCIIvalues = 0;
    for (char ch : item) {
        sumOfASCIIvalues+=ch;
    }

    //finding the initial index
    int initialIndex = sumOfASCIIvalues % size;

    Node* current = table[initialIndex];
    Node* prev = nullptr;

    bool found = false;

    //search the item until it becomes null
    while (current != nullptr) {
        if ((*current).data == item) {
            //item is not there
            if (prev != nullptr) {
                (*prev).next = (*current).next;
            }
            //item is in the first node
            else {
                table[initialIndex] = (*current).next;
            }
            delete current;
            found = true;
            break;
        }
        prev = current;
        current = (*current).next;
    }

    if (found) {
        cout << item << " is deleted." << endl;
    }
    else {
        cout << item << " is not present." << endl;
    }

}

void HashTableImproved::search(const string &item) {

    //calculating the sum of ascii values for every char
    int sumOfASCIIvalues = 0;
    for (char ch : item) {
        sumOfASCIIvalues+=ch;
    }

    //finding the initial index
    int initialIndex = sumOfASCIIvalues % size;

    Node* current = table[initialIndex];

    bool found = false;

    //search the linked list at that location
    while (current != nullptr) {
        if ((*current).data == item) {
            found = true;
            break;
        }
        current = (*current).next;
    }

    if (found) {
        cout << item << " is a weak spot." << endl;
    }else {
        cout << item << " is not a weak spot." << endl;
    }
}
