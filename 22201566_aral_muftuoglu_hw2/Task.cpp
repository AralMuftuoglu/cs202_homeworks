/**
** Author : Aral Muftuoglu
** ID: 22201566
** Section : 3
** Homework : 2
** Description : Task class cpp file
*/

#include "Task.h"
#include "Package.h"
#include "Drone.h"
#include <cmath>

Task::Task() {
    package = nullptr;
    drone = nullptr;
}


Task::Task(Package *packageCurrent, Drone *droneCurrent) {
    package = packageCurrent;
    drone = droneCurrent;

    priority = packageCurrent->getPriority();

    int x = packageCurrent->getX()-droneCurrent->getLocationX();
    int y = packageCurrent->getY()-droneCurrent->getLocationY();
    estimatedTime = (sqrt((x*x) + (y*y)))/droneCurrent->getSpeed();
}

int Task::getPriority() {
    return priority;
}
double Task::getEstimatedTime() {
    return estimatedTime;
}
bool Task::operator>(const Task &other) {
    if (priority != other.priority) {
        return priority > other.priority;
    }
    return estimatedTime < other.estimatedTime; // if priority is same, compare estimated times

}

bool Task::operator<(const Task &other)  {
    // This is just the inverse of operator>
    return !(*this > other) && !(*this == other);
}

bool Task::operator==(const Task &other)  {
    return (priority == other.priority) && (estimatedTime == other.estimatedTime);
}

Package *Task::getPackage() {
    return package;
}

Drone *Task::getDrone() {
    return drone;
}

void Task::setDrone(Drone *drone) {
    this->drone = drone;
}
