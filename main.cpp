#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <SDL.h>

#include "traffic_simulation.hpp"


bool initializeSDL(SDL_Window*& window, SDL_Renderer*& renderer) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL Init Error: " << SDL_GetError() << "\n";
        return false;
    }

    window = SDL_CreateWindow(
        "Traffic Simulation",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN
    );

    if (!window) {
        std::cerr << "Window Error: " << SDL_GetError() << "\n";
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Renderer Error: " << SDL_GetError() << "\n";
        return false;
    }

    return true;
}

void cleanupSDL(SDL_Window* window, SDL_Renderer* renderer) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}


Vehicle readVehicleFromFile(std::ifstream& file) {
    Vehicle vehicle;
    int dir, type, turn, state, skip;

    if (file >> vehicle.x >> vehicle.y
             >> dir >> type >> turn >> state
             >> vehicle.speed >> skip) {   

        vehicle.direction     = static_cast<Direction>(dir);
        vehicle.type          = static_cast<VehicleType>(type);
        vehicle.turnDirection = static_cast<TurnDirection>(turn);
        vehicle.state         = static_cast<VehicleState>(state);
        vehicle.canSkipLight  = (skip != 0);
        vehicle.active        = true;

        if (vehicle.direction == Direction::NORTH ||
            vehicle.direction == Direction::SOUTH) {
            vehicle.rect = { (int)vehicle.x, (int)vehicle.y, 20, 30 };
        } else {
            vehicle.rect = { (int)vehicle.x, (int)vehicle.y, 30, 20 };
        }
    }
    return vehicle;
}


void simulationUpdate(std::vector<Vehicle>& vehicles,
                      std::vector<TrafficLight>& lights) {

    for (auto& light : lights)
        light.update();

    for (auto& v : vehicles)
        if (v.active)
            v.update(lights.data());
}


int main(int argc, char* argv[]) {

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    if (!initializeSDL(window, renderer))
        return 1;

    std::srand((unsigned)std::time(nullptr));

    std::vector<Vehicle> vehicles(MAX_VEHICLES);
    std::vector<TrafficLight> lights;

    lights.emplace_back(Direction::NORTH, SDL_Rect{380, 250, 20, 20});
    lights.emplace_back(Direction::SOUTH, SDL_Rect{420, 550, 20, 20});
    lights.emplace_back(Direction::EAST,  SDL_Rect{550, 380, 20, 20});
    lights.emplace_back(Direction::WEST,  SDL_Rect{250, 420, 20, 20});

    Statistics stats;
    stats.startTime = SDL_GetTicks();

    Uint32 lastSpawn = 0;
    const Uint32 SPAWN_INTERVAL = 1000;

    SDL_Event event;
    bool running = true;

    while (running) {

        while (SDL_PollEvent(&event))
            if (event.type == SDL_QUIT)
                running = false;

        Uint32 now = SDL_GetTicks();

        int activeCount = 0;
        for (const auto& v : vehicles)
            if (v.active) activeCount++;

        if (now - lastSpawn >= SPAWN_INTERVAL &&
            activeCount < MAX_VEHICLES) {

            Direction dir = static_cast<Direction>(std::rand() % 4);

            for (auto& v : vehicles) {
                if (!v.active) {
                    v = Vehicle(dir);
                    v.active = true;
                    stats.totalVehicles++;
                    break;
