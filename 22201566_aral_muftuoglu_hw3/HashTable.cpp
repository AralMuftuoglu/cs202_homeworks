/**
* Title: Hash Table
* Author : Aral Muftuoglu
* ID: 22201566
* Section : 3
* Homework : 3
* Description : HashTable cpp file
*/

#include "HashTable.h"
#include <iostream>
using namespace std;


//constructor for hash table
HashTable::HashTable() {
    //table size (prime number)
    size = 211;
    //dynamically allocate memory for the hash table
    hashTable = new string[size];

    int counter = 0;

    //initially all the slots are " "
    while (counter < size) {
        hashTable[counter] = " ";
        counter++;
    }
}

//destructor for hashle table
HashTable::~HashTable() {
    delete[] hashTable;
}

//insert function
void HashTable::insert(const string& item) {

    //calculating the sum of ascii values for every char
    int sumOfASCIIvalues = 0;
    for (char ch : item) {
        sumOfASCIIvalues+=ch;
    }

    //finding the initial index
    int initialIndex = sumOfASCIIvalues % size;

    //check that if there is a collision if there is no, just add the item
    if( hashTable[initialIndex] == " " ) {
        hashTable[initialIndex] = item;
        cout << item << " is registered as a weak spot."<<endl;
    }
    //there is a collision but it is same with the item we want to insert
    else if( hashTable[initialIndex] == item) {
        cout<< item << " is already registered as a weak spot."<<endl;
    }
    //there is collision with another item, need for quadratic probing
    else {
        int i = 1;
        int currentIndex = initialIndex;

        while( hashTable[currentIndex] != "deleted" && hashTable[currentIndex] != " ") {
            if(hashTable[currentIndex] == item) {
                cout<< item << " is already registered as a weak spot."<<endl;
                return;
            }
            currentIndex = (initialIndex+ (i*i)) % size;
            i++;
            if(i==size) {
                cout<<"table is full"<<endl;
                return;
            }
        }

        //found the correct spot insert the item
        hashTable[currentIndex] = item;
        cout << item << " is registered as a weak spot." << endl;
    }
}
//remove function
void HashTable::remove(const string &item) {

    //calculating the sum of ascii values for every char
    int sumOfASCIIvalues = 0;
    for (char ch : item) {
        sumOfASCIIvalues+=ch;
    }

    int initialIndex = sumOfASCIIvalues % size;
    int currentIndex = initialIndex;
    int i = 1;

    bool found = false;

    //probe for empty slot or for the item
    while (hashTable[currentIndex] != " ") {
        if (hashTable[currentIndex] == item) {
            hashTable[currentIndex] = "deleted";
            found = true;
            break;
        }

        currentIndex = (initialIndex + (i * i)) % size;
        i++;

        if (i == size) {
            found = false;
            break;
        }
    }

    if(found) {
        cout << item << " is deleted." << endl;
    }
    else {
        cout << item << " is not present." << endl;
    }
}
//search function
void HashTable::search(const string &item) {

    //calculating the sum of ascii values for every char
    int sumOfASCIIvalues = 0;
    for (char ch : item) {
        sumOfASCIIvalues+=ch;
    }

    int initialIndex = sumOfASCIIvalues % size;
    int currentIndex = initialIndex;
    int i = 1;

    bool found = false;

    //probe until empty slot or item is found
    while (hashTable[currentIndex] != " ") {
        if (hashTable[currentIndex] == item) {
            found = true;
            break;
        }

        currentIndex = (initialIndex + (i * i)) % size;
        i++;

        if (i == size) {
            found = false;
            break;
        }
    }

    if (found) {
        cout << item << " is a weak spot." << endl;
    }
    else {
        cout << item << " is not a weak spot." << endl;
    }
}

