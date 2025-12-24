#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "traffic_simulation.h"

void initializeSDL(SDL_Window **window, SDL_Renderer **renderer)
{
    SDL_Init(SDL_INIT_VIDEO);

    *window = SDL_CreateWindow(
        "Traffic Simulation",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN
    );

    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(*renderer, 255, 255, 255, 255);
}

void cleanupSDL(SDL_Window *window, SDL_Renderer *renderer)
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void handleEvents(bool *running)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
            *running = false;
    }
}


Vehicle readVehicleFromFile(FILE *file)
{
    Vehicle vehicle;
    vehicle.active = false;

    if (fscanf(file, "%f %f %d %d %d %d %d %d",
               &vehicle.x,
               &vehicle.y,
               (int *)&vehicle.direction,
               (int *)&vehicle.type,
               (int *)&vehicle.turnDirection,
               (int *)&vehicle.state,
               &vehicle.speed,
               &vehicle.canSkipLight) == 8)
    {
        vehicle.active = true;

       
        if (vehicle.direction == DIRECTION_NORTH ||
            vehicle.direction == DIRECTION_SOUTH)
        {
            vehicle.rect.w = 20;
            vehicle.rect.h = 30;
        }
        else
        {
            vehicle.rect.w = 30;
            vehicle.rect.h = 20;
        }

        vehicle.rect.x = (int)vehicle.x;
        vehicle.rect.y = (int)vehicle.y;
    }

    return vehicle;
}


void simulationUpdate(Vehicle *vehicles, TrafficLight *lights)
{
    updateLanePositions(vehicles);

    for (int i = 0; i < MAX_VEHICLES; i++)
    {
        if (vehicles[i].active)
            updateVehicle(&vehicles[i], lights);
    }

    updateTrafficLights(lights);
}


int main(int argc, char *argv[])
{
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    bool running = true;

    Uint32 lastVehicleSpawn = 0;
    const Uint32 SPAWN_INTERVAL = 1000;

    srand((unsigned int)time(NULL));

    initializeSDL(&window, &renderer);

   
    Vehicle vehicles[MAX_VEHICLES] = {0};
    int vehicleCount = 0;

    
    TrafficLight lights[4];
    initializeTrafficLights(lights);

    
    Statistics stats;
    stats.vehiclesPassed = 0;
    stats.totalVehicles = 0;
    stats.vehiclesPerMinute = 0.0f;
    stats.startTime = SDL_GetTicks();

    for (int i = 0; i < 4; i++)
        initQueue(&laneQueues[i]);

    while (running)
    {
        handleEvents(&running);

        Uint32 currentTime = SDL_GetTicks();

        
        if (currentTime - lastVehicleSpawn >= SPAWN_INTERVAL &&
            vehicleCount < MAX_VEHICLES)
        {
            Direction spawnDirection = (Direction)(rand() % 4);
            Vehicle *newVehicle = createVehicle(spawnDirection);

            for (int i = 0; i < MAX_VEHICLES; i++)
            {
                if (!vehicles[i].active)
                {
                    vehicles[i] = *newVehicle;
                    vehicles[i].active = true;
                    vehicleCount++;
                    stats.totalVehicles++;
                    break;
                }
            }

            free(newVehicle);
            lastVehicleSpawn = currentTime;
        }

     
        for (int i = 0; i < MAX_VEHICLES; i++)
        {
            if (vehicles[i].active)
            {
                updateVehicle(&vehicles[i], lights);

                if (!vehicles[i].active)
                {
                    stats.vehiclesPassed++;
                    vehicleCount--;
                }
            }
        }

        updateTrafficLights(lights);

        
        float minutes = (SDL_GetTicks() - stats.startTime) / 60000.0f;
        if (minutes > 0)
            stats.vehiclesPerMinute = stats.vehiclesPassed / minutes;

        simulationUpdate(vehicles, lights);
        renderSimulation(renderer, vehicles, lights, &stats);

        SDL_Delay(16); /* ~60 FPS */
    }

    cleanupSDL(window, renderer);
    return 0;
}
