#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <SDL.h>

#include "traffic_simulation.hpp"

void writeVehicleToFile(std::ofstream& file, const Vehicle& vehicle) {
    file << vehicle.x << " "
         << vehicle.y << " "
         << static_cast<int>(vehicle.direction) << " "
         << static_cast<int>(vehicle.type) << " "
         << static_cast<int>(vehicle.turnDirection) << " "
         << static_cast<int>(vehicle.state) << " "
         << vehicle.speed << " "
         << vehicle.canSkipLight << "\n";
}

int main(int argc, char* argv[]) {

    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    std::ofstream file("bin/vehicles.txt", std::ios::out | std::ios::trunc);

    if (!file.is_open()) {
        std::cerr << "Failed to open bin/vehicles.txt. Make sure the 'bin' folder exists!\n";
        return 1;
    }

    if (SDL_Init(SDL_INIT_TIMER) < 0) {
        std::cerr << "SDL Init Error: " << SDL_GetError() << "\n";
        return 1;
    }

    std::cout << "Starting Vehicle Generator... (Ctrl+C to stop)\n";

    while (true) {
        Direction spawnDirection =
            static_cast<Direction>(std::rand() % 4);

        Vehicle newVehicle(spawnDirection); 
        newVehicle.active = true;

        writeVehicleToFile(file, newVehicle);
        file.flush();

        std::cout << "Generated Vehicle at "
                  << SDL_GetTicks() << " ms\n";

        SDL_Delay(2000);
    }

    file.close();
    SDL_Quit();
    return 0;
}
