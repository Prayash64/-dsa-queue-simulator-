#ifndef VEHICLE_QUEUE_HPP 
#define VEHICLE_QUEUE_HPP 

#include <queue>
#include "Vehicle.hpp"     

class VehicleQueue {
private:
    std::queue<Vehicle> queue;
public:
    void enqueue(Vehicle v);
    Vehicle dequeue();
    bool isEmpty();
    int size();
};

#endif 