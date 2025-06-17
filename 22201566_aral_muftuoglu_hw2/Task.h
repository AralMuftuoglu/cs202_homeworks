/**
** Author : Aral Muftuoglu
** ID: 22201566
** Section : 3
** Homework : 2
** Description : Task class header file
*/

#ifndef TASK_H
#define TASK_H

class Package;
class Drone;

class Task {
private:
    Package* package;
    Drone* drone;
    double estimatedTime;
    int priority;
public:
    Task();
    Task(Package* packageCurrent, Drone* droneCurrent);
    double getEstimatedTime();
    int getPriority();
    bool operator>(const Task& other);
    bool operator<(const Task& other) ;
    bool operator==(const Task& other) ;

    Package* getPackage();
    Drone* getDrone();

    void setDrone(Drone* drone);
};
#endif //TASK_H
