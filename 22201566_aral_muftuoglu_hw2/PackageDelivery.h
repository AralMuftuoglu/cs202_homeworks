/**
** Author : Aral Muftuoglu
** ID: 22201566
** Section : 3
** Homework : 2
** Description : PackageDelivery class header file
*/

#ifndef PACKAGEDELIVERY_H
#define PACKAGEDELIVERY_H

const int MAX_PACKAGE_WEIGHT = 10;
const double WEIGHT_FACTOR = 0.2;
const double BATTERY_FACTOR = 0.3;
const int COOLDOWN_PERIOD = 5;
const int MAX_BATTERY = 300;

#include "Task.h"
#include "Drone.h"
#include "Package.h"
#include "Heap.h"
#include <fstream>
#include <iostream>

class PackageDelivery {
private:
    int noPackages;

    Heap<Drone> drones;
    Heap<Task> tasks;
    Heap<Task> waitingTasks;
public:
    PackageDelivery(const std::string& droneFile, const std::string& packageFile);
    ~PackageDelivery();
    void simulation();
    void UpdateCoolDown();
};
#endif //PACKAGEDELIVERY_H
