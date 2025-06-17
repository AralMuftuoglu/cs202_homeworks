/**
* Title: Hash Table Improved
* Author : Aral Muftuoglu
* ID: 22201566
* Section : 3
* Homework : 3
* Description : HashTableImproved header file
*/

#ifndef HASHTABLEIMPROVED_H
#define HASHTABLEIMPROVED_H

#include <string>
using namespace std;

class HashTableImproved {
public:
    //constructor and destructor
    HashTableImproved();
    ~HashTableImproved();

    //insert, remove and search functions
    void insert(const string& item);
    void remove(const string& item);
    void search(const string& item);
private:

    //node structure for chain logic
    struct Node {
        string data;
        Node* next;
    };

    //size and pointer to the hash table
    static const int size = 211;
    Node* table[size];
};
#endif //HASHTABLEIMPROVED_H