/**
** Author : Aral Muftuoglu
** ID: 22201566
** Section : 3
** Homework : 2
** Description : Drone class cpp file
*/

#include "Drone.h"

// default constructor
Drone::Drone() {
    id = 0;
    batteryLife = 0;
    speed = 0;
    locationX = 0;
    locationY = 0;
    cooldownTime = 0;
}

// constructor
Drone::Drone(int ID, double battery, double droneSpeed) {
    id = ID;
    batteryLife = battery;
    speed = droneSpeed;
    locationX = 0;
    locationY = 0;
    cooldownTime = 0;
}

// getter methods
int Drone::getId() {
    return id;
}
double Drone::getBatteryLife() {
    return batteryLife;
}
double Drone::getSpeed() {
    return speed;
}
int Drone::getLocationX() {
    return locationX;
}
int Drone::getLocationY() {
    return locationY;
}
int Drone::getCooldownTime() {
    return cooldownTime;
}

// setter methods
void Drone::setId(int ID) {
    id = ID;
}
void Drone::setBatteryLife(double battery) {
    batteryLife = battery;
}
void Drone::setSpeed(double droneSpeed) {
    speed = droneSpeed;
}
void Drone::setLocationX(int X) {
    locationX = X;
}
void Drone::setLocationY(int Y) {
    locationY = Y;
}
void Drone::setCooldownTime(int time) {
    cooldownTime = time;
}

// overload operator
bool Drone::operator>(const Drone& other) {
    if (batteryLife != other.batteryLife) {
        return batteryLife > other.batteryLife;
    }
    return id < other.id; // if battery is same, compare id values
}

bool Drone::operator<(const Drone& other) {
    // This is just the inverse of operator>
    return !(*this > other) && !(*this == other);
}

bool Drone::operator==(const Drone& other) {
    return (batteryLife == other.batteryLife) && (id == other.id);
}