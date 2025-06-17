/**
** Author : Aral Muftuoglu
** ID: 22201566
** Section : 3
** Homework : 2
** Description : Package class cpp file
*/

#include "Package.h"

// default constructor
Package::Package() {
    id = 0;
    destinationX = 0;
    destinationY = 0;
    priority = 0;
    weight = 0;
}
// constructor
Package::Package(int ID, int x, int y, int priorityValue, double packageWeight) {
    id = ID;
    destinationX = x;
    destinationY = y;
    priority = priorityValue;
    weight = packageWeight;
}

// getter methods
int Package::getId() {
    return id;
}
int Package::getPriority() {
    return priority;
}
double Package::getWeight() {
    return weight;
}
int Package::getX() {
    return destinationX;
}
int Package::getY() {
    return destinationY;
}

// setter methods
void Package::setId(int ID) {
    id = ID;
}
void Package::setPriority(int priorityValue) {
    priority = priorityValue;
}
void Package::setWeight(double packageWeight) {
    weight = packageWeight;
}
void Package::setX(int x) {
    destinationX = x;
}
void Package::setY(int y) {
    destinationY = y;
}

