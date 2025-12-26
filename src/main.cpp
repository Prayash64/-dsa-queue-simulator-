#include <SDL2/SDL.h>
#include <SDL.h>
#include <iostream>
#include "traffic_simulation.hpp"

int main(int argc, char* argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL could not initialize! SDL_Error: "
                  << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow(
        "Traffic Simulation",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN
    );

    if (!window) {
        std::cout << "Window could not be created! SDL_Error: "
                  << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(
        window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    if (!renderer) {
        std::cout << "Renderer could not be created! SDL_Error: "
                  << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Initialize traffic lights and statistics
    TrafficLight lights[4];
    Statistics stats = {};
    Vehicle vehicles[MAX_VEHICLES] = {};
    
    initializeTrafficLights(lights);
    stats.startTime = SDL_GetTicks();

    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                running = false;
        }

        // Update simulation
        updateTrafficLights(lights);
        
        // Render
        SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
        SDL_RenderClear(renderer);
        
        renderSimulation(renderer, vehicles, lights, &stats);
        
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
