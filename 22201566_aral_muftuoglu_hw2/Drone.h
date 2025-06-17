/**
** Author : Aral Muftuoglu
** ID: 22201566
** Section : 3
** Homework : 2
** Description : Drone class header file
*/

#ifndef DRONE_H
#define DRONE_H

#include <string>
using namespace std;

class Drone {
private:
    int id;
    double batteryLife;
    double speed;
    int locationX;
    int locationY;
    int cooldownTime;
public:
    Drone();
    Drone(int ID, double battery, double droneSpeed);
    int getId();
    double getBatteryLife();
    double getSpeed();
    int getLocationX();
    int getLocationY();
    int getCooldownTime();
    void setId(int ID);
    void setBatteryLife(double battery);
    void setSpeed(double droneSpeed);
    void setLocationX(int X);
    void setLocationY(int Y);
    void setCooldownTime(int time);
    bool operator>(const Drone& other);
    bool operator<(const Drone& other);
    bool operator==(const Drone& other);
};

#endif //DRONE_H