#include <iostream>
#include <cmath>
#include <SDL.h>

#include "traffic_simulation.hpp"

queue laneQueues[4];


int lanePriorities[4] = { 0, 0, 0, 0 };


const SDL_Color VEHICLE_COLORS[] = {
    { 0,   0, 255, 255 },   
    { 255, 0,   0, 255 },   
    { 0,   0, 128, 255 },   
    { 255, 69,  0, 255 }    
};


void initializeTrafficLights(TrafficLight* lights)
{
    
    lights[0].state = TrafficLightState::RED;
    lights[0].timer = 0;
    lights[0].direction = Direction::NORTH;
    lights[0].position = {
        INTERSECTION_X - TRAFFIC_LIGHT_WIDTH / 2,
        INTERSECTION_Y - LANE_WIDTH - 20,
        TRAFFIC_LIGHT_WIDTH,
        TRAFFIC_LIGHT_HEIGHT
    };

   
    lights[1].state = TrafficLightState::RED;
    lights[1].timer = 0;
    lights[1].direction = Direction::SOUTH;
    lights[1].position = {
        INTERSECTION_X - TRAFFIC_LIGHT_WIDTH / 2,
        INTERSECTION_Y + LANE_WIDTH,
        TRAFFIC_LIGHT_WIDTH,
        TRAFFIC_LIGHT_HEIGHT
    };

   
    lights[2].state = TrafficLightState::GREEN;
    lights[2].timer = 0;
    lights[2].direction = Direction::EAST;
    lights[2].position = {
        INTERSECTION_X + LANE_WIDTH,
        INTERSECTION_Y - TRAFFIC_LIGHT_HEIGHT / 2,
        TRAFFIC_LIGHT_HEIGHT,
        TRAFFIC_LIGHT_WIDTH
    };

   
    lights[3].state = TrafficLightState::GREEN;
    lights[3].timer = 0;
    lights[3].direction = Direction::WEST;
    lights[3].position = {
        INTERSECTION_X - LANE_WIDTH - TRAFFIC_LIGHT_HEIGHT,
        INTERSECTION_Y - TRAFFIC_LIGHT_HEIGHT / 2,
        TRAFFIC_LIGHT_HEIGHT,
        TRAFFIC_LIGHT_WIDTH
    };
}
