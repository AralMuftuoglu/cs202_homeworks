/**
** Author : Aral Muftuoglu
** ID: 22201566
** Section : 3
** Homework : 4
** Description : CyberAttackContainment class header file
*/

#ifndef CYBERATTACKCONTAINMENT_H
#define CYBERATTACKCONTAINMENT_H

using namespace std;
#include <string>

class CyberAttackContainment {
public:
    // constructor and destructor
    CyberAttackContainment(const string inputFile);
    ~CyberAttackContainment();
    // nodeStatuses function which prints the final condition of the nodes
    void nodeStatuses();
    // computeConnectedZones function which prints the all connected zones and their kind
    void computeConnectedZones();
private:
    // number of nodes which obtained from txt file
    int countNode;
    // array for storing the names of the nodes
    string* nodeNames;
    // matrix for the weights of the different edges
    double** weightedEdgesMatrix;
    // matrix to determine whether there is a edge between the nodes or not
    bool** connectionEdgesMatrix;

    // array for storing the initial condition of the nodes
    string* initialNodes;
    // array for storing the final condition of the nodes
    string* finalNodes;

    // basic queue data members for using it in BFS operations
    int* nodeQueue;
    int head;
    int tail;

    // malwareSpread function using BFS
    void malwareSpread(double* malwareTimes);
    // patchSpread function using Dijkstra
    void patchSpread(double* patchTimes, bool* visited);
    // private helper function which determines the final condition of the nodes, it is used by nodeStatuses and computeConnectedZones
    string* computeFinalNodes();
    // helper function for compare the node names for order the output
    bool compare(const string& a, const string& b);
    // helper function for compare the chars in a zone, for order the names
    void sortZoneNodes(string& zoneElements);
};
#endif //CYBERATTACKCONTAINMENT_H