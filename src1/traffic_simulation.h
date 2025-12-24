#ifndef TRAFFIC_SIMULATION_HPP
#define TRAFFIC_SIMULATION_HPP

#include <SDL.h>



#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define LANE_WIDTH 80
#define MAX_VEHICLES 100

#define INTERSECTION_X (WINDOW_WIDTH / 2)
#define INTERSECTION_Y (WINDOW_HEIGHT / 2)

#define TRAFFIC_LIGHT_WIDTH (LANE_WIDTH * 2)
#define TRAFFIC_LIGHT_HEIGHT (LANE_WIDTH - LANE_WIDTH / 3)
#define STOP_LINE_WIDTH 5



enum Direction {
    DIRECTION_NORTH,
    DIRECTION_SOUTH,
    DIRECTION_EAST,
    DIRECTION_WEST
};

enum TurnDirection {
    TURN_NONE,
    TURN_LEFT,
    TURN_RIGHT
};

enum VehicleState {
    STATE_MOVING,
    STATE_STOPPING,
    STATE_STOPPED,
    STATE_TURNING
};

enum VehicleType {
    REGULAR_CAR,
    AMBULANCE,
    POLICE_CAR,
    FIRE_TRUCK
};

enum TrafficLightState {
    RED,
    GREEN
};



struct Vehicle {
    SDL_Rect rect{};
    VehicleType type{};
    Direction direction{};
    TurnDirection turnDirection{};
    VehicleState state{};
    float speed{};
    float x{};
    float y{};
    bool active{false};
    float turnAngle{};
    bool isInRightLane{false};
    bool turnProgress{false};
    bool canSkipLight{false};
};

struct TrafficLight {
    TrafficLightState state{};
    int timer{};
    SDL_Rect position{};
    Direction direction{};
};

struct Statistics {
    int vehiclesPassed{};
    int totalVehicles{};
    float vehiclesPerMinute{};
    Uint32 startTime{};
};


struct Node {
    Vehicle vehicle;
    Node* next{nullptr};
};

struct Queue {
    Node* front{nullptr};
    Node* rear{nullptr};
    int size{0};
};

struct LanePosition {
    float position{};
    Vehicle* vehicle{nullptr};
};



extern Queue laneQueues[4];




void initializeTrafficLights(TrafficLight* lights);
void updateTrafficLights(TrafficLight* lights);


Vehicle* createVehicle(Direction direction);
void updateVehicle(Vehicle* vehicle, TrafficLight* lights);
float getDistanceBetweenVehicles(Vehicle* v1, Vehicle* v2);
int getVehicleLane(Vehicle* vehicle);
void updateLanePositions(Vehicle* vehicles);


void renderSimulation(SDL_Renderer* renderer,
                      Vehicle* vehicles,
                      TrafficLight* lights,
                      Statistics* stats);
void renderRoads(SDL_Renderer* renderer);
void renderQueues(SDL_Renderer* renderer);


void initQueue(Queue* q);
void enqueue(Queue* q, Vehicle vehicle);
Vehicle dequeue(Queue* q);
int isQueueEmpty(Queue* q);

#endif 
