#include "Queue.hpp"
#include <iostream>
#include "VehicleQueue.hpp"
#include "LaneQueue.hpp"

int main() {
    Queue vehicleQueue;
    VehicleQueue vq;
    LaneQueue lq;

    vehicleQueue.enqueue(1, 5);
    vehicleQueue.enqueue(2, 8);
    vehicleQueue.enqueue(3, 12);
   
    vq.enqueue(Vehicle(1, 5, 2));
    vq.enqueue(Vehicle(2, 10, 3));
    vq.enqueue(Vehicle(3, 15, 1));

    std::cout << "Current Queue:\n";
    vehicleQueue.displayQueue();
   
    std::cout << "Vehicle Queue Size: " << vq.size() << std::endl;
    std::cout << "Dequeued Vehicle ID: " << vq.dequeue().id << std::endl;

    Vehicle* servedVehicle = vehicleQueue.dequeue();
    if (servedVehicle) {
        std::cout << "\nServed Vehicle: ID = " << servedVehicle->id 
                  << ", Arrival Time = " << servedVehicle->arrival_time << "\n";
        delete servedVehicle; 
    }
   
    lq.addLane(1, 5);
    lq.addLane(2, 15); 
    lq.addLane(3, 8);

    std::cout << "\nQueue after serving one vehicle:\n";
    vehicleQueue.displayQueue();
    
    std::cout << "Highest Priority Lane: " << lq.getHighestPriorityLane().lane_id << std::endl;

    return 0;
}