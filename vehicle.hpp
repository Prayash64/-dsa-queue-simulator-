#ifndef VEHICLE_H
#define VEHICLE_H

class Vehicle {
public:
    int id;
    int arrival_time;
    int lane_id;

    Vehicle(int id, int arrival_time, int lane_id);
};

#endif