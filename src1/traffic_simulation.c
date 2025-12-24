#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <SDL2/SDL.h>
#include "traffic_simulation.h"


Queue laneQueues[4];
int lanePriorities[4] = {0};
LanePosition laneVehicles[4][MAX_VEHICLES];
int vehiclesInLane[4] = {0};

const SDL_Color VEHICLE_COLORS[] = {
    {0, 0, 255, 255},     
    {255, 0, 0, 255},     
    {0, 0, 128, 255},    
    {255, 69, 0, 255}     
};



float getDistanceBetweenVehicles(Vehicle* v1, Vehicle* v2)
{
    float dx = v1->x - v2->x;
    float dy = v1->y - v2->y;
    return std::sqrt(dx * dx + dy * dy);
}

int getVehicleLane(Vehicle* vehicle)
{
    if (vehicle->direction == DIRECTION_NORTH ||
        vehicle->direction == DIRECTION_SOUTH)
        return (vehicle->x < INTERSECTION_X) ? 0 : 1;
    else
        return (vehicle->y < INTERSECTION_Y) ? 2 : 3;
}



void initializeTrafficLights(TrafficLight* lights)
{
    lights[0] = {RED, 0,
        {INTERSECTION_X - LANE_WIDTH,
         INTERSECTION_Y - LANE_WIDTH - TRAFFIC_LIGHT_HEIGHT,
         TRAFFIC_LIGHT_WIDTH, TRAFFIC_LIGHT_HEIGHT},
        DIRECTION_NORTH};

    lights[1] = {RED, 0,
        {INTERSECTION_X - LANE_WIDTH,
         INTERSECTION_Y + LANE_WIDTH,
         TRAFFIC_LIGHT_WIDTH, TRAFFIC_LIGHT_HEIGHT},
        DIRECTION_SOUTH};

    lights[2] = {GREEN, 0,
        {INTERSECTION_X + LANE_WIDTH,
         INTERSECTION_Y - LANE_WIDTH,
         TRAFFIC_LIGHT_HEIGHT, TRAFFIC_LIGHT_WIDTH},
        DIRECTION_EAST};

    lights[3] = {GREEN, 0,
        {INTERSECTION_X - LANE_WIDTH - TRAFFIC_LIGHT_HEIGHT,
         INTERSECTION_Y - LANE_WIDTH,
         TRAFFIC_LIGHT_HEIGHT, TRAFFIC_LIGHT_WIDTH},
        DIRECTION_WEST};
}

void updateTrafficLights(TrafficLight* lights)
{
    static Uint32 lastChange = 0;
    static int phase = 0;
    Uint32 now = SDL_GetTicks();

    if (now - lastChange >= 5000)
    {
        phase = 1 - phase;

        if (phase == 0)
        {
            lights[DIRECTION_NORTH].state = GREEN;
            lights[DIRECTION_SOUTH].state = GREEN;
            lights[DIRECTION_EAST].state  = RED;
            lights[DIRECTION_WEST].state  = RED;
        }
        else
        {
            lights[DIRECTION_NORTH].state = RED;
            lights[DIRECTION_SOUTH].state = RED;
            lights[DIRECTION_EAST].state  = GREEN;
            lights[DIRECTION_WEST].state  = GREEN;
        }

        lastChange = now;
    }
}



Vehicle* createVehicle(Direction direction)
{
    Vehicle* v = new Vehicle{};
    v->direction = direction;
    v->active = true;
    v->canSkipLight = false;

    int roll = rand() % 100;
    if (roll < 5) v->type = AMBULANCE;
    else if (roll < 10) v->type = POLICE_CAR;
    else if (roll < 15) v->type = FIRE_TRUCK;
    else v->type = REGULAR_CAR;

    v->speed = (v->type == REGULAR_CAR) ? 2.0f : 4.0f;
    v->state = STATE_MOVING;
    v->turnDirection = TURN_NONE;

    if (direction == DIRECTION_NORTH || direction == DIRECTION_SOUTH)
    {
        v->rect.w = 20;
        v->rect.h = 30;
    }
    else
    {
        v->rect.w = 30;
        v->rect.h = 20;
    }

    switch (direction)
    {
    case DIRECTION_NORTH:
        v->x = INTERSECTION_X;
        v->y = WINDOW_HEIGHT;
        break;
    case DIRECTION_SOUTH:
        v->x = INTERSECTION_X;
        v->y = 0;
        break;
    case DIRECTION_EAST:
        v->x = 0;
        v->y = INTERSECTION_Y;
        break;
    case DIRECTION_WEST:
        v->x = WINDOW_WIDTH;
        v->y = INTERSECTION_Y;
        break;
    }

    v->rect.x = (int)v->x;
    v->rect.y = (int)v->y;
    return v;
}



void renderRoads(SDL_Renderer* r)
{
    SDL_SetRenderDrawColor(r, 128, 128, 128, 255);
    SDL_Rect intersection = {
        INTERSECTION_X - LANE_WIDTH,
        INTERSECTION_Y - LANE_WIDTH,
        LANE_WIDTH * 2,
        LANE_WIDTH * 2
    };
    SDL_RenderFillRect(r, &intersection);
}

void renderSimulation(SDL_Renderer* r,
                      Vehicle* vehicles,
                      TrafficLight* lights,
                      Statistics*)
{
    SDL_SetRenderDrawColor(r, 200, 200, 200, 255);
    SDL_RenderClear(r);

    renderRoads(r);

    for (int i = 0; i < 4; i++)
    {
        SDL_SetRenderDrawColor(r,
            lights[i].state == GREEN ? 0 : 255,
            lights[i].state == GREEN ? 255 : 0,
            0, 255);
        SDL_RenderFillRect(r, &lights[i].position);
    }

    for (int i = 0; i < MAX_VEHICLES; i++)
    {
        if (vehicles[i].active)
        {
            SDL_Color c = VEHICLE_COLORS[vehicles[i].type];
            SDL_SetRenderDrawColor(r, c.r, c.g, c.b, c.a);
            SDL_RenderFillRect(r, &vehicles[i].rect);
        }
    }

    SDL_RenderPresent(r);
}



void initQueue(Queue* q)
{
    q->front = q->rear = nullptr;
    q->size = 0;
}

void enqueue(Queue* q, Vehicle vehicle)
{
    Node* n = new Node{vehicle, nullptr};

    if (!q->rear)
        q->front = q->rear = n;
    else
    {
        q->rear->next = n;
        q->rear = n;
    }
    q->size++;
}

Vehicle dequeue(Queue* q)
{
    if (!q->front) return Vehicle{};

    Node* t = q->front;
    Vehicle v = t->vehicle;
    q->front = t->next;
    if (!q->front) q->rear = nullptr;
    delete t;
    q->size--;
    return v;
}

int isQueueEmpty(Queue* q)
{
    return q->front == nullptr;
}
