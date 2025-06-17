/**
** Author : Aral Muftuoglu
** ID: 22201566
** Section : 3
** Homework : 2
** Description : Package class header file
*/

#ifndef PACKAGE_H
#define PACKAGE_H

#include <string>

class Package {
private:
    int id;
    int destinationX;
    int destinationY;
    int priority;
    double weight;
public:
    Package();
    Package(int id, int x, int y, int priority, double weight);
    int getId();
    int getX();
    int getY();
    int getPriority();
    double getWeight();
    void setId(int id);
    void setX(int x);
    void setY(int y);
    void setPriority(int priority);
    void setWeight(double weight);
};
#endif //PACKAGE_H