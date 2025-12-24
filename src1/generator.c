#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include "traffic_simulation.h"

void writeVehicleToFile(FILE *file, Vehicle *vehicle)
{
    fprintf(file, "%f %f %d %d %d %d %d %d\n",
            vehicle->x,
            vehicle->y,
            vehicle->direction,
            vehicle->type,
            vehicle->turnDirection,
            vehicle->state,
            vehicle->speed,
            vehicle->canSkipLight);
}

int main(int argc, char *argv[])
{
    srand((unsigned int)time(NULL));

    if (SDL_Init(SDL_INIT_TIMER) != 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    FILE *file = fopen("bin/vehicles.txt", "w");
    if (!file)
    {
        perror("Failed to open vehicles.txt");
        SDL_Quit();
        return 1;
    }

    while (1)
    {
        Direction spawnDirection = (Direction)(rand() % 4);

        Vehicle *newVehicle = createVehicle(spawnDirection);
        if (!newVehicle) continue;

       
        writeVehicleToFile(file, newVehicle);
        fflush(file);

       
        free(newVehicle);

        
        SDL_Delay(2000);
    }

    fclose(file);
    SDL_Quit();
    return 0;
}
