#ifndef TRAFFIC_SIMULATION_HPP
#define TRAFFIC_SIMULATION_HPP

#include <SDL.h>
#include <cstdint>


constexpr int WINDOW_WIDTH  = 800;
constexpr int WINDOW_HEIGHT = 600;
constexpr int LANE_WIDTH    = 80;
constexpr int MAX_VEHICLES  = 100;

constexpr int INTERSECTION_X = WINDOW_WIDTH / 2;
constexpr int INTERSECTION_Y = WINDOW_HEIGHT / 2;

constexpr int TRAFFIC_LIGHT_WIDTH  = LANE_WIDTH * 2;
constexpr int TRAFFIC_LIGHT_HEIGHT = LANE_WIDTH - LANE_WIDTH / 3;
constexpr int STOP_LINE_WIDTH = 5;


enum class Direction {
    NORTH,
    SOUTH,
    EAST,
    WEST
};

enum class TurnDirection {
    NONE,
    LEFT,
    RIGHT
};

enum class VehicleState {
    MOVING,
    STOPPING,
    STOPPED,
    TURNING
};

enum class VehicleType {
    REGULAR_CAR,
    AMBULANCE,
    POLICE_CAR,
    FIRE_TRUCK
};

enum class TrafficLightState {
    RED,
    GREEN
};


struct Vehicle {
    SDL_Rect rect{};

    VehicleType type{VehicleType::REGULAR_CAR};
    Direction direction{Direction::NORTH};
    TurnDirection turnDirection{TurnDirection::NONE};
    VehicleState state{VehicleState::STOPPED};

    float speed{0.0f};
    float x{0.0f};
    float y{0.0f};

    bool active{false};
    float turnAngle{0.0f};
    bool isInRightLane{false};
    bool turnProgress{false};
    bool canSkipLight{false};

    Vehicle() = default;
    Vehicle(Direction dir, VehicleType vType = VehicleType::REGULAR_CAR);
};


struct TrafficLight {
    TrafficLightState state{TrafficLightState::RED};
    int timer{0};
    SDL_Rect position{};
    Direction direction{Direction::NORTH};
};


struct Statistics {
    int vehiclesPassed{0};
    int totalVehicles{0};
    float vehiclesPerMinute{0.0f};
    Uint32 startTime{0};
};


struct Node {
    Vehicle vehicle;
    Node* next{nullptr};
};

class Queue {
public:
    Node* front{nullptr};
    Node* rear{nullptr};
    int size{0};

    Queue() = default;
    ~Queue();

    void init();
    void enqueue(const Vehicle& vehicle);
    Vehicle dequeue();
    bool isEmpty() const;
};


struct LanePosition {
    float position{0.0f};
    Vehicle* vehicle{nullptr};
};


extern Queue laneQueues[4];


void initializeTrafficLights(TrafficLight* lights);
void updateTrafficLights(TrafficLight* lights);

Vehicle* createVehicle(Direction direction);
void updateVehicle(Vehicle* vehicle, TrafficLight* lights);

float getDistanceBetweenVehicles(const Vehicle* v1, const Vehicle* v2);
int getVehicleLane(const Vehicle* vehicle);
void updateLanePositions(Vehicle* vehicles);

void renderSimulation(SDL_Renderer* renderer,
                      Vehicle* vehicles,
                      TrafficLight* lights,
                      Statistics* stats);

void renderRoads(SDL_Renderer* renderer);
void renderQueues(SDL_Renderer* renderer);

#endif 