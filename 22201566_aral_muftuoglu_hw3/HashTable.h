/**
* Title: Hash Table
* Author : Aral Muftuoglu
* ID: 22201566
* Section : 3
* Homework : 3
* Description : HashTable header file
*/

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
using namespace std;

class HashTable {
public:
    //constructor and destructor
    HashTable();
    ~HashTable();

    //insert, remove and search functions
    void insert(const string& item);
    void remove(const string& item);
    void search(const string& item);

private:
    //size and pointer to the hash table
    int size;
    string* hashTable;
};
#endif //HASHTABLE_H