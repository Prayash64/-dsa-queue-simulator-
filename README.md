Assignment: One 

Name: Prayash Bhattarai 

Rollno: 15 

## Traffic Junction Stimulation 

This project simulates traffic movement at an intersection using C. The simulation models vehicle movement, traffic signals, and congestion patterns.

## Program output 

![demo](https://github.com/user-attachments/assets/7a60f9bb-f57c-4951-a0e7-fad8209d8ce8)

## Program structure 

![program structure ](https://github.com/user-attachments/assets/b1259a8f-55f9-4707-abd5-e0a8b2d10519)

## Prerequisites

To run this simulation, you need:

GCC or G++ compiler
SDL2 library
MinGW (for Windows)






## How it Works

Program Components

The simulation consists of two separate programs:

Generator (generator.exe):

1. Generates vehicles with random properties

2. Writes vehicle data to a file for the main program to read

3.  Spawns new vehicles every 500 milliseconds

Main Simulation (main.exe):

1. Reads vehicle data from the generator
   
2. Renders the intersection and vehicles
   
3. Manages traffic flow and vehicle movement
   
4. Handles traffic light cycles.


  
   
## Vehicle Types

a. Blue: Regular cars

b. Red: Ambulances

c. Dark Blue: Police cars

d. Orange-Red: Fire trucks

## Code Structure

1. main.c: Program entry point and main simulation loop
   
2. traffic_simulation.h: Header file containing structs and function declarations
   
3. traffic_simulation.c: Implementation of traffic simulation logic
   
4. generator.c: Vehicle generation logic
   
Data Structure used in program 

## Data Structures Used

| Data Structure | File(s) Used | Description |
|---------------|-------------|-------------|
| Queue | Queue.h | Implements basic FIFO queue |
| VehicleQueue | VehicleQueue.h | Queue for storing vehicles |
| LaneQueue | LaneQueue.h | Queue for managing lanes |
| Vehicle | Vehicle.h | Stores vehicle information |

  ## Running the Simulation

1. First, start the vehicle generator:

   ```bash
   ./bin/generator.exe
   
2. In a separate terminal, start the main simulation:

   ```bash
   ./bin/main.exe

3.   Watch as vehicles spawn and navigate through the intersection
  
4. Use the close button (X) to exit the simulationControls 



## References

SDL2 Documentation: https://wiki.libsdl.org/

Queue Data Structure: Introduction to Algorithms, CLRS (Cormen, Leiserson, Rivest, Stein)

Traffic Flow Theory: Highway Capacity Manual (Transportation Research Board)

Intersection Management Algorithms: IEEE Intelligent Transportation Systems

## Technical Documentation

For detailed technical documentation about the implementation:

1. Vehicle Generation: Vehicles are spawned at regular intervals with randomized properties.

2. Traffic Light System: Uses a timer-based system with priority adjustments based on queue lengths and emergency vehicles.

3. Collision Avoidance: Vehicles maintain safe distances and respond to traffic signals and other vehicles.

4. Queue Management: Each lane maintains its own queue, with priority handling for emergency vehicles.

5. Red Light Skipping Logic: The canVehicleSkipLight() function determines when a non-emergency vehicle can proceed through a red light based on:

      a. Wait time at the intersection

      b. Type of turn being made

      c. Presence of other vehicles 


## Acknowledgments

1. SDL2 development team

2. Traffic simulation research community



