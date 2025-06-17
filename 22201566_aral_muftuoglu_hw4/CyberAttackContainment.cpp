/**
** Author : Aral Muftuoglu
** ID: 22201566
** Section : 3
** Homework : 4
** Description : CyberAttackContainment class cpp file
*/

#include "CyberAttackContainment.h"
#include <fstream>
#include <iostream>

// constructor
CyberAttackContainment::CyberAttackContainment(const string inputFile) {
    ifstream file(inputFile);

    //read the number of nodes from txt file
    countNode = 0;
    file >> countNode;

    // initialize the queue
    nodeQueue = new int[countNode];
    head = 0;
    tail = 0;

    // initialize the arrays
    nodeNames = new string[countNode];
    initialNodes = new string[countNode];
    finalNodes = new string[countNode];

    string data;
    for (int i = 0; i < countNode; i++) {
        //getting the node name data
        file >> data;
        nodeNames[i] = data;
        // getting the data for which kind is the node
        file >> data;
        // d for dispatcher, n for normal and m for malware
        if (data == "dispatcher") {
            initialNodes[i] = "d";
        } else if (data == "normal") {
            initialNodes[i] = "n";
        } else if (data == "malware") {
            initialNodes[i] = "m";
        }

        // just initialize the final situation as empty string will be overwritten
        finalNodes[i] = "";
    }

    // initialize the weightedEdgesMatrix
    weightedEdgesMatrix = new double *[countNode];
    for (int i = 0; i < countNode; i++) {
        weightedEdgesMatrix[i] = new double[countNode];
        for (int j = 0; j < countNode; j++) {
            // if corresponding node is itself just give 0
            if (i == j) {
                weightedEdgesMatrix[i][j] = 0;
            }
            // if it is not assume that there is no more connection
            else {
                weightedEdgesMatrix[i][j] = 99999; //case for no connection initially very big number for the weight
            }
        }
    }

    // initialize the connectionEdgesMatrix
    connectionEdgesMatrix = new bool *[countNode];
    for (int i = 0; i < countNode; i++) {
        connectionEdgesMatrix[i] = new bool[countNode];
        for (int j = 0; j < countNode; j++) {
            // make the every edge false initially
            connectionEdgesMatrix[i][j] = false;
        }
    }

    // initialize the edgeCounter
    int edgeCounter = 0;

    // read the edge data from txt
    while (file >> data) {
        // increase the counter
        edgeCounter++;

        // first node
        string first = data;
        file >> data;
        // second node
        string second = data;
        file >> data;
        // weight data
        double edgeWeight = stod(data);

        int n = -1;
        int m = -1;

        // determining the correct positions
        for (int k = 0; k < countNode; k++) {
            if (nodeNames[k] == first) {
                m = k;
            }
            if (nodeNames[k] == second) {
                n = k;
            }
        }

        // save the weight data on matrix
        weightedEdgesMatrix[m][n] = edgeWeight;
        weightedEdgesMatrix[n][m] = edgeWeight;
    }
    // print the output for the result
    cout << countNode << " nodes and " << edgeCounter << " connections are loaded.";

    // close the file
    file.close();
}

// destructor
CyberAttackContainment::~CyberAttackContainment() {
    // delete all the dynamically allocated memories
    delete[] nodeNames;
    delete[] initialNodes;
    delete[] finalNodes;
    delete[] nodeQueue;

    // for matrices follow these ways
    for (int i = 0; i < countNode; i++) {
        delete[] weightedEdgesMatrix[i];
    }
    delete[] weightedEdgesMatrix;

    for (int i = 0; i < countNode; i++) {
        delete[] connectionEdgesMatrix[i];
    }
    delete[] connectionEdgesMatrix;
}

// malwareSpread function for simulation
void CyberAttackContainment::malwareSpread(double *malwareTimes) {

    // first check the initial malware nodes and set their times to 0
    for (int indexNode = 0; indexNode < countNode; indexNode = indexNode + 1) {
        if (initialNodes[indexNode] == "m") {
            nodeQueue[tail] = indexNode;
            malwareTimes[indexNode] = 0;
            tail = tail + 1;
        }
    }

    // BFS traversal for the other ones
    while (head < tail) {
        int indexInfected = nodeQueue[head];
        head = head + 1;

        // check the neighbours to infect by malware
        for (int indexNeighbor = 0; indexNeighbor < countNode; indexNeighbor = indexNeighbor + 1) {

            // if it is not visited before and there is a connection between nodes infect it
            if (weightedEdgesMatrix[indexInfected][indexNeighbor] < 99999 && malwareTimes[indexNeighbor] == -1) {
                // save the infection time
                malwareTimes[indexNeighbor] = malwareTimes[indexInfected] + 1;
                nodeQueue[tail] = indexNeighbor;
                tail = tail + 1;
            }
        }
    }
}

// patchSpread function for simulation
void CyberAttackContainment::patchSpread(double *patchTimes, bool *visited) {

    // first check the initial dispatcher nodes and set their times to 0
    for (int indexNode = 0; indexNode < countNode; indexNode = indexNode + 1) {
        if (initialNodes[indexNode] == "d") {
            patchTimes[indexNode] = 0;
        }
    }

    // Dijkstra logic
    for (int i = 0; i < countNode; i = i + 1) {
        // initialize the minimum time
        double minTime = 99999;
        int select = -1;

        // determine the node that has minimum time
        for (int j = 0; j < countNode; j = j + 1) {
            if (!visited[j] && patchTimes[j] < minTime) {
                minTime = patchTimes[j];
                select = j;
            }
        }

        // if there is no remaining node, means select equals to -1 exit
        if (select == -1) {
            break;
        }
        // if it there is make it true
        visited[select] = true;

        for (int j = 0; j < countNode; j = j + 1) {
            // if it is not visited before and there is a connection between nodes update it with patch
            if (!visited[j] && weightedEdgesMatrix[select][j] < 99999) {
                double alternativeTime = patchTimes[select] + weightedEdgesMatrix[select][j];
                if (patchTimes[j] > alternativeTime) {
                    patchTimes[j] = alternativeTime;
                }
            }
        }
    }
}

// computeFinalNodes function to determine the final conditions of the nodes
string *CyberAttackContainment::computeFinalNodes() {

    // reset the queue head and tail
    head = 0;
    tail = 0;

    // initialize the arrays
    double *timeToSecure;
    double *timeToInfect;
    bool *visited;

    timeToSecure = new double[countNode];
    timeToInfect = new double[countNode];
    visited = new bool[countNode];

    // initialize the results array
    string *results = new string[countNode];

    // initially give 99999 (very big number) for time to secure and give -1 for time to infect
    for (int i = 0; i < countNode; i = i + 1) {
        timeToSecure[i] = 99999;
        timeToInfect[i] = -1;
        visited[i] = false;
    }

    // use helper functions to calculate required times
    malwareSpread(timeToInfect);
    patchSpread(timeToSecure, visited);

    // determine final status of each node based one required times
    for (int indexNode = 0; indexNode < countNode; indexNode = indexNode + 1) {
        if (timeToSecure[indexNode] < timeToInfect[indexNode] || timeToInfect[indexNode] == -1) {
            results[indexNode] = "secured";
        } else {
            results[indexNode] = "infected";
        }
    }

    // deallocate the memory dynamically allocated
    delete[] timeToInfect;
    delete[] timeToSecure;
    delete[] visited;

    // return the result array
    return results;
}

// nodeStatuses function
void CyberAttackContainment::nodeStatuses() {
    // get the final nodes from computeFinalNodes method
    string *results = computeFinalNodes();

    // print the header
    cout << endl;
    cout << "Node states are:" << endl;

    // sort the node names in alphabetic order
    int *indices = new int[countNode];
    for (int i = 0; i < countNode; i = i + 1) {
        indices[i] = i;
    }

    // manuel sort based on nodeNames using compare() method
    int i = 0;
    while (i < countNode - 1) {
        int j = i + 1;
        while (j < countNode) {
            if (!compare(nodeNames[indices[i]], nodeNames[indices[j]])) {
                int temp = indices[i];
                indices[i] = indices[j];
                indices[j] = temp;
            }
            j = j + 1;
        }
        i = i + 1;
    }

    // print the final nodes in sorted order
    for (i = 0; i < countNode; i = i + 1) {
        int currentIndex = indices[i];
        cout << nodeNames[currentIndex] << " " << results[currentIndex] << endl;
    }

    // deallocate the dynamically allocated memory
    delete[] results;
    delete[] indices;
}

// computeConnectedZones function
void CyberAttackContainment::computeConnectedZones() {

    // initialize the visited array for being aware of which nodes are visited
    bool *visited;
    visited = new bool[countNode];

    // initially give the value false for they have not been visited yet
    for (int i = 0; i < countNode; i = i + 1) {
        visited[i] = false;
    }

    // get the final nodes via computeFinalNodes method
    string *finalNodes = computeFinalNodes();

    // counter represents the connected nodes
    int numberOfZones = 0;

    // initialize arrays, zoneElements keeps track of the elements in a zone and isInfectedZone shows it is an infected zone or not
    string *zoneElements = new string[countNode];
    bool *isInfectedZone = new bool[countNode];

    // using BFS for determining the zones
    int i = 0;
    while (i < countNode) {
        // if it is not visited before start the new zone from this node
        if (!visited[i]) {
            // initially not infected
            bool isInfected = false;
            visited[i] = true;

            // reset the queue members
            head = 0;
            tail = 0;

            //initial zone members
            string currentZone = "";

            // initialize the BFS
            nodeQueue[tail] = i;
            tail = tail + 1;

            // use BFS to find all connected zones with same final situation
            while (head < tail) {
                int currentNodeIndex = nodeQueue[head];
                head = head + 1;

                // add node's name to zone names array(string)
                currentZone = currentZone + nodeNames[currentNodeIndex] + " ";

                // if there is a infected one change the bool isInfected
                if (finalNodes[currentNodeIndex] == "infected") {
                    isInfected = true;
                }

                // looking for neighbours with same final situation
                int k = 0;
                while (k < countNode) {
                    // when find a connected one with same final situation
                    if (!visited[k] &&
                        weightedEdgesMatrix[currentNodeIndex][k] < 99999 &&
                        finalNodes[k] == finalNodes[currentNodeIndex]) {
                        // add it to the queue
                        nodeQueue[tail] = k;
                        tail = tail + 1;
                        visited[k] = true;
                    }
                    k = k + 1;
                }
            }

            // sort the elements in the zone in alphabetic order via sortZoneElements method
            sortZoneNodes(currentZone);

            //save it in arrays they have parallel structure so they can kept the track
            isInfectedZone[numberOfZones] = isInfected;
            zoneElements[numberOfZones] = currentZone;

            // increase the numberOfZones
            numberOfZones = numberOfZones + 1;
        }
        i = i + 1;
    }

    // sort the zones in alphabetic order via compare method
    i = 0;
    while (i < numberOfZones - 1) {
        int j = i + 1;
        while (j < numberOfZones) {
            // if there is a need for change in between the i and j, swap them in both of arrays which have parallel structure
            if (!compare(zoneElements[i], zoneElements[j])) {
                bool tempBool = isInfectedZone[i];
                isInfectedZone[i] = isInfectedZone[j];
                isInfectedZone[j] = tempBool;

                string tempString = zoneElements[i];
                zoneElements[i] = zoneElements[j];
                zoneElements[j] = tempString;
            }
            j = j + 1;
        }
        i = i + 1;
    }

    // print the connected zones and their kind (infected or secured)
    cout << "Connected zones are:" << endl;
    i = 0;
    while (i < numberOfZones) {
        string zone = zoneElements[i];
        string name = "";

        for (char ch : zone) {
            if (ch == ' ') {
                if (!name.empty()) {
                    cout << name << " ";
                    name = "";
                }
            } else {
                name += ch;
            }
        }

        // Catch the last name if the string didn't end in a space
        if (!name.empty()) {
            cout << name << " ";
        }
        //print the zone situation
        if (isInfectedZone[i]) {
            cout << "infected" << endl;
        } else {
            cout << "secured" << endl;
        }
        i = i + 1;
    }

    // deallocate the dynamically allocated memory
    delete[] visited;
    delete[] finalNodes;
    delete[] zoneElements;
    delete[] isInfectedZone;
}

// compare helper function
bool CyberAttackContainment::compare(const string &a, const string &b) {

    // get the lengths of both strings
    int lenA = a.length();
    int lenB = b.length();
    int smallLength;

    // find the smaller string
    if (lenA < lenB) {
        smallLength = lenA;
    } else {
        smallLength = lenB;
    }

    // compare the every char in the form of (AaBbCcDd...)
    int i = 0;
    while (i < smallLength) {
        char charA = a[i];
        char charB = b[i];

        // if they are not equal compare them in the form of (AaBbCcDd...)
        if (charA != charB) {
            char normA;
            char normB;

            // convert the chars to uppercase
            if (charA >= 'A' && charA <= 'Z') {
                normA = 32 + charA;
            } else {
                normA = charA;
            }
            // also for b
            if (charB >= 'A' && charB <= 'Z') {
                normB = 32 + charB;
            } else {
                normB = charB;
            }

            // return the result
            if (normA < normB) {
                return true;
            }
            else if (normA > normB) {
                return false;
            }
            else if (charA < charB) {
                return true;
            }
            else {
                return false;
            }
        }
        i = i + 1;
    }

    // if all of them equivalent return shorter
    return lenA < lenB;

}

// sortZoneNodes function
void CyberAttackContainment::sortZoneNodes(string &zone) {

    // counter number of names
    int nameCount = 0;
    // count the blank spaces
    for (int i = 0; i < zone.length(); i++) {
        if (zone[i] == ' ') {
            nameCount++;
        }
    }

    // initializing the array
    string *names;
    names = new string[nameCount];

    int nameIndex = 0;
    string current = "";

    // get the names from the string
    for (int i = 0; i < zone.length(); i++) {
        if (zone[i] == ' ') {
            names[nameIndex] = current;
            nameIndex++;
            current = "";
        } else {
            current = current + zone[i];
        }
    }

    // sort the names with the help of compare function
    for (int i = 0; i < nameCount - 1; i++) {
        for (int j = 0; j < nameCount - i - 1; j++) {
            if (!compare(names[j], names[j + 1])) {
                string temp = names[j];
                names[j] = names[j + 1];
                names[j + 1] = temp;
            }
        }
    }

    // based on sorted version construct the string again
    zone = "";
    for (int i = 0; i < nameCount; i++) {
        // for the clear output add blank space
        zone = zone + names[i] + " ";
    }

    // deallocate the dynamically allocated memory
    delete[] names;
}

