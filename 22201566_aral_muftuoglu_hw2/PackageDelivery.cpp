/**
** Author : Aral Muftuoglu
** ID: 22201566
** Section : 3
** Homework : 2
** Description : PackageDelivery class cpp file
*/

#include "PackageDelivery.h"
#include <cmath>

using namespace std;

// constructor
PackageDelivery::PackageDelivery(const string &droneFile, const string &packageFile) {

    ifstream droneText(droneFile);
    ifstream packageText(packageFile);

    int numberDrones;
    droneText >> numberDrones;

    int droneID;
    int droneBattery;
    double droneSpeed;

    // read the txt file for drones
    for (int i = 0; i < numberDrones; i++) {
        droneText >> droneID >> droneBattery >> droneSpeed;
        Drone newDrone(droneID, droneBattery, droneSpeed);
        drones.heapInsert(newDrone);
    }
    droneText.close();

    Drone bestDrone = drones.getMax();

    int numberPackages;
    packageText >> numberPackages;

    noPackages = numberPackages;

    int packageID;
    int packageX;
    int packageY;
    int packagePriority;
    double packageWeight;

    // read txt file for packages
    for (int i = 0; i < numberPackages; i++) {
        packageText >> packageID >> packageX >> packageY >> packageWeight  >> packagePriority;
        Package* newPackage = new Package(packageID, packageX, packageY, packagePriority, packageWeight);
        Task newTask(newPackage, &bestDrone);
        tasks.heapInsert(newTask);
    }
    packageText.close();
}

PackageDelivery::~PackageDelivery() {
    for (int i = 0; i < tasks.getSize(); i++) {
        if (tasks.getItems()[i].getPackage() != nullptr) {
            delete tasks.getItems()[i].getPackage();
        }
    }

    // Clean up Package objects from waitingTasks heap
    for (int i = 0; i < waitingTasks.getSize(); i++) {
        if (waitingTasks.getItems()[i].getPackage() != nullptr) {
            delete waitingTasks.getItems()[i].getPackage();
        }
    }

    // Clean up Drone objects created in Simulation method and stored in tasks
    for (int i = 0; i < waitingTasks.getSize(); i++) {
        if (waitingTasks.getItems()[i].getDrone() != nullptr) {
            delete waitingTasks.getItems()[i].getDrone();
        }
    }
}

void PackageDelivery::UpdateCoolDown() {
    int numberElements = waitingTasks.getSize();

    for (int i = 0; i < numberElements; i++) {
        waitingTasks.getItems()[i].getDrone()->setCooldownTime(waitingTasks.getItems()[i].getDrone()->getCooldownTime()-1);
    }

    for (int i = 0; i < numberElements; i++) {
        if(waitingTasks.getItems()[i].getDrone()->getCooldownTime() == 0) {

            Drone* dronePtr = waitingTasks.getItems()[i].getDrone();
            dronePtr->setBatteryLife(300);

            // Create a copy for the drones heap (value, not pointer)
            Drone droneCopy = *dronePtr;
            drones.heapInsert(droneCopy);

            // Move the task to the tasks heap
            tasks.heapInsert(waitingTasks.getItems()[i]);
            waitingTasks.heapDelete(waitingTasks.getItems()[i]);
        }
    }
}

// simulation of the system
void PackageDelivery::simulation() {

    int tick = 0;
    int packageDone = 0;

    while (packageDone < noPackages) {

        this->UpdateCoolDown();

        if(!tasks.heapIsEmpty()) {
            Task& currentTask = tasks.getItems()[0];
            Drone& currentDrone = drones.getItems()[0];

            int x = currentTask.getPackage()->getX() - currentDrone.getLocationX();
            int y = currentTask.getPackage()->getY() - currentDrone.getLocationY();

            double distance = sqrt(x * x + y * y);
            distance = floor(distance * 10) / 10.0;

            double effectiveSpeed = (currentDrone.getSpeed()) * (
                                 1 - WEIGHT_FACTOR * ((currentTask.getPackage()->getWeight()) / MAX_PACKAGE_WEIGHT));

            effectiveSpeed = effectiveSpeed*(1-BATTERY_FACTOR*(1-(currentDrone.getBatteryLife()/MAX_BATTERY)));
            effectiveSpeed = floor(effectiveSpeed * 10) / 10.0;

            double timeRequired = distance / effectiveSpeed;
            timeRequired = floor(timeRequired * 10) / 10.0;

            if(currentDrone.getBatteryLife() < timeRequired) {

                cout<<"Drone "<<currentDrone.getId()<<" Package "<<currentTask.getPackage()->getId()<<" at tick "<<tick<<" cool down"<<endl;

                currentDrone.setCooldownTime(COOLDOWN_PERIOD);
                currentDrone.setLocationX(0);
                currentDrone.setLocationY(0);

                Drone* newDronePtr = new Drone(currentDrone.getId(),
                               currentDrone.getBatteryLife(),
                               currentDrone.getSpeed());

                newDronePtr->setLocationX(currentDrone.getLocationX());
                newDronePtr->setLocationY(currentDrone.getLocationY());
                newDronePtr->setCooldownTime(currentDrone.getCooldownTime());

                currentTask.setDrone(newDronePtr);

                Task newTaskPtr (currentTask.getPackage(),currentTask.getDrone());

                drones.heapDelete(currentDrone);
                waitingTasks.heapInsert(newTaskPtr);
            }
            else {
                cout<<"Drone "<<currentDrone.getId()<<" Package "<<currentTask.getPackage()->getId()<<" at tick "<<tick
               <<" (delivery time: "<<timeRequired<<", battery life: "<<currentDrone.getBatteryLife()-timeRequired<<")"<<endl;

                Drone newDrone(currentDrone.getId(), currentDrone.getBatteryLife()-timeRequired, currentDrone.getSpeed());
                newDrone.setLocationX(currentTask.getPackage()->getX());
                newDrone.setLocationY(currentTask.getPackage()->getY());
                drones.heapDelete(currentDrone);

                // new version of current drone
                drones.heapInsert(newDrone);

                packageDone++;
            }

            tasks.heapDelete(currentTask);
        }
        tick++;
    }
}


