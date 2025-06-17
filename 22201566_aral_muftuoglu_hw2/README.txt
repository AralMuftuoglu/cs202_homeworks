/**
** Author : Aral Muftuoglu
** ID: 22201566
** Section : 3
** Homework : 2
** Description : README file
*/


Package Delivery System is designed to control the packages and drones which are used in delivery operations. There are 5 different classes in this system.

Classes

PackageDelivery
Construct the initial values and run the simulation
Reads input files (drone.txt and package.txt)
Saves the drones in heap
Creates tasks according to drones and packages and also save them in heap
Has the simulation logic 
Includes cooldown method

Drone
Responsible for forwarding packages
Has id, battery, speed, x and y location, cooldownTime
Getters and setters methods
Include overloaded <, = and > operators according the priority preferences (for heap imp.)

Package
Carried by drones
Has id, x and y destination, weight and priority 
Getters and setters methods

Task
Includes the responsible drone and carried package
Has Package* package and Drone* drone 
Getters and setters methods
Include overloaded <, = and > operators according the priority preferences (for heap imp.)

Heap<T>
Used for priority queue 
Has heapInsert, heapDelete, getMax and heapRebuild methods
Codes in slides are used

Input files drone.txt and package.txt

In simulation,
Store all the drones and packages not heaps 
Best drone is used for the largest priority package
Drone's battery is affected by estimated delivery time
If drone has not enough battery to finish the job and still it is the best drone it goes to cooldown 
In cooldown, it gets max battery but wait for 5 tick
System repeats this same process until all of the packages are done



