/**
** Author : Aral Muftuoglu
** ID: 22201566
** Section : 3
** Homework : 2
** Description : Heap template class
*/

#ifndef HEAP_H
#define HEAP_H

#include <iostream>

using namespace std;

const int MAX_HEAP = 50;  // Define heap size

template <typename T>
class Heap {
public:
    Heap(); // Default constructor

    bool heapIsEmpty() const;
    void heapInsert(const T& newItem);
    void heapDelete(T& rootItem);
    T getMax() const;

    int getSize() const;
    T* getItems();
protected:
    void heapRebuild(int root);

private:
    T items[MAX_HEAP];
    int size;
};

// Constructor
template <typename T>
Heap<T>::Heap() : size(0) {}

// Check if heap is empty
template <typename T>
bool Heap<T>::heapIsEmpty() const {
    return size == 0;
}

// Insert a new item into the heap
template <typename T>
void Heap<T>::heapInsert(const T& newItem) {
    if (size >= MAX_HEAP) {
        cout << "Heap is full. Cannot insert." << endl;
        return; // Just return instead of throwing an exception
    }

    items[size] = newItem;  // Place the new item at the end

    // Trickle new item up to its proper position
    int place = size;
    int parent = (place - 1) / 2;
    while (place > 0 && items[place] > items[parent]) {

        T temp = items[parent];
        items[parent] = items[place];
        items[place] = temp;

        place = parent;
        parent = (place - 1) / 2;
    }

    ++size;
}

// Delete the root (maximum value) from the heap
template <typename T>
void Heap<T>::heapDelete(T& rootItem) {
    if (heapIsEmpty()) {
        cout << "Heap is empty. Cannot delete." << endl;
        return;
    }

    rootItem = items[0]; // Retrieve the max item
    items[0] = items[--size]; // Move last item to root
    heapRebuild(0);
}

// Rebuild heap after deletion
template <typename T>
void Heap<T>::heapRebuild(int root) {
    int child = 2 * root + 1;  // Left child index

    if (child < size) { // If root has a left child
        int rightChild = child + 1;  // Right child index

        // Use the larger child
        if (rightChild < size && items[rightChild] > items[child]) {
            child = rightChild;
        }

        // Swap if needed
        if (items[root] < items[child]) {
            T temp = items[root];
            items[root] = items[child];
            items[child] = temp;

            heapRebuild(child);
        }
    }
}

// To get the root
template <typename T>
T Heap<T>::getMax() const {
    if (heapIsEmpty()) {
        cout << "Heap is empty. No max element." << endl;
        return T();
    }
    return items[0];
}


// Get heap size
template <typename T>
int Heap<T>::getSize() const {
    return size;
}

// Get pointer to internal array
template <typename T>
T* Heap<T>::getItems() {
    return items;
}
#endif //HEAP_H
