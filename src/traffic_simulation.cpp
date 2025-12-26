#include "traffic_simulation.hpp"
#include <iostream>
#include <cstdlib>


Queue laneQueues[4]; 


const SDL_Color VEHICLE_COLORS[] = {
    {0, 0, 255, 255},    // REGULAR_CAR: Blue
    {255, 0, 0, 255},    // AMBULANCE: Red
    {0, 0, 128, 255},    // POLICE_CAR: Dark Blue
    {255, 69, 0, 255}    // FIRE_TRUCK: Orange-Red
};


Queue::~Queue() {
    while (!isEmpty()) {
        dequeue();
    }
}

void Queue::init() {
    front = rear = nullptr;
    size = 0;
}

void Queue::enqueue(const Vehicle& vehicle) {
    Node* node = new Node;
    node->vehicle = vehicle;
    node->next = nullptr;

    if (rear == nullptr) {
        front = rear = node;
    } else {
        rear->next = node;
        rear = node;
    }
    size++;
}

Vehicle Queue::dequeue() {
    if (front == nullptr) {
        return Vehicle(); 
    }
    Node* temp = front;
    Vehicle v = temp->vehicle;
    front = front->next;
    if (front == nullptr) rear = nullptr;
    delete temp;
    size--;
    return v;
}

bool Queue::isEmpty() const {
    return front == nullptr;
}


void initializeTrafficLights(TrafficLight* lights) {
    lights[0].state = TrafficLightState::RED;
    lights[0].timer = 0;
    lights[0].position = { INTERSECTION_X - LANE_WIDTH, INTERSECTION_Y - LANE_WIDTH - TRAFFIC_LIGHT_HEIGHT, TRAFFIC_LIGHT_WIDTH, TRAFFIC_LIGHT_HEIGHT };
    lights[0].direction = Direction::NORTH;

    lights[1].state = TrafficLightState::RED;
    lights[1].timer = 0;
    lights[1].position = { INTERSECTION_X - LANE_WIDTH, INTERSECTION_Y + LANE_WIDTH, TRAFFIC_LIGHT_WIDTH, TRAFFIC_LIGHT_HEIGHT };
    lights[1].direction = Direction::SOUTH;

    lights[2].state = TrafficLightState::GREEN;
    lights[2].timer = 0;
    lights[2].position = { INTERSECTION_X + LANE_WIDTH, INTERSECTION_Y - LANE_WIDTH, TRAFFIC_LIGHT_HEIGHT, TRAFFIC_LIGHT_WIDTH };
    lights[2].direction = Direction::EAST;

    lights[3].state = TrafficLightState::GREEN;
    lights[3].timer = 0;
    lights[3].position = { INTERSECTION_X - LANE_WIDTH - TRAFFIC_LIGHT_HEIGHT, INTERSECTION_Y - LANE_WIDTH, TRAFFIC_LIGHT_HEIGHT, TRAFFIC_LIGHT_WIDTH };
    lights[3].direction = Direction::WEST;
}
