#include "Vehicle.hpp" 

Vehicle::Vehicle(int id, int arrival_time, int lane_id) {
    this->id = id;
    this->arrival_time = arrival_time;
    this->lane_id = lane_id;
}