/**
** Title: BST
** Author : Aral Muftuoglu
** ID: 22201566
** Section : 3
** Homework : 1
** Description : analysis implementation file
*/

#include "analysis.h"
#include <cstdlib>   // for srand and rand methods
#include <ctime>
#include "BST.h"

void analysis::timeAnalysis() {

    //initialize an empty BST
    int keys[] = {};
    int size = 0;
    BST testBST(keys, size);

    // create random number generator
    srand(time(nullptr));

    // dynamically allocate for random values
    int* randomNumbers = new int[10000];

    // create all random values
    for (int i = 0; i < 10000; ++i) {
        randomNumbers[i] = rand() % 1000000 + 1;
    }

    // start the overall timer
    chrono::high_resolution_clock::time_point overallStart = chrono::high_resolution_clock::now();
    chrono::high_resolution_clock::time_point intervalStart = overallStart;

    // insert numbers and track times
    for (int i = 0; i < 10000; ++i) {
        // insert the random number into BST
        testBST.insertKey(randomNumbers[i]);

        // check points for every 1000*n
        if ((i + 1) % 1000 == 0) {
            // time current
            chrono::high_resolution_clock::time_point currentTime = chrono::high_resolution_clock::now();

            // calculate time for this specific 1000-element interval
            chrono::microseconds intervalTime = chrono::duration_cast<chrono::microseconds>(currentTime - intervalStart);

            // print time for this interval
            cout << "Time for elements " << (i - 999) << " to " << (i + 1) << ": " << intervalTime.count() << " microseconds" << endl;

            // print height for the interval
            int treeHeight = testBST.bstHeight(testBST.getRoot());
            cout << "Tree height at " << (i + 1) << " elements: " << treeHeight << endl;

            // reset interval start
            intervalStart = currentTime;
        }
    }

    // free the memory
    delete[] randomNumbers;
}
