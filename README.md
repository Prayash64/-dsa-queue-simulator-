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

## Features of the Queue Simulator

1. Queue-Based Traffic Management

   Uses the Queue data structure (FIFO) to simulate real-world traffic flow where vehicles are processed in the order they arrive.

2. Vehicle Insertion and Removal
   
   Vehicles are added to the lane using enqueue() and removed using dequeue() when they pass the intersection.

3. Multiple Lane Support
   
   Supports independent queues for different traffic lanes, allowing simultaneous processing of multiple traffic streams.

4. Traffic Processing Algorithm
   
   Implements a loop-based algorithm that checks each lane and processes vehicles according to queue rules and traffic conditions.

5. Efficient Operations
   
   Core queue operations like insertion, deletion, and front access are performed in constant time for better performance.

6. Modular Design
   
   Separate files and classes are used for queues, vehicles, and lane logic, improving readability and maintainability.

7. Simulation Visualization Support
   
   Includes demo visuals (demo.gif) and structural diagrams to help understand program flow.

8. Testable Implementation
   
   Includes test files to validate correct behavior of queue operations.

   ## Time Complexity

| **Operation / Algorithm Step**       | **Data Structure Used** | **Time Complexity** | **Explanation**                                                               |
| ------------------------------------ | ----------------------- | ------------------- | ----------------------------------------------------------------------------- |
| `enqueue(vehicle)`                   | Queue                   | **O(1)**            | Vehicle is added directly to the rear of the queue without shifting elements. |
| `dequeue()`                          | Queue                   | **O(1)**            | Front vehicle is removed in constant time.                                    |
| `peek()` / `front()`                 | Queue                   | **O(1)**            | Accesses the front vehicle without removal.                                   |
| `isEmpty()`                          | Queue                   | **O(1)**            | Simple condition check on queue state.                                        |
| `size()`                             | Queue                   | **O(1)**            | Size is maintained as a variable in the queue.                                |
| `display()`                          | Queue                   | **O(n)**            | Iterates through all vehicles in the queue to display them.                   |
| Vehicle arrival processing           | Queue                   | **O(1)**            | Each arriving vehicle is enqueued once.                                       |
| Vehicle departure processing         | Queue                   | **O(1)**            | Each vehicle exits using dequeue operation.                                   |
| Processing one traffic lane per step | Queue                   | **O(1)**            | Only the front vehicle is checked and processed.                              |
| Processing all lanes per step        | Multiple Queues         | **O(L)**            | Each lane queue is processed once per simulation step.                        |
| Full traffic simulation              | Queues + Loop           | **O(T × L)**        | For `T` time steps and `L` lanes, each lane is processed per step.            |




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
   


##  Data Structures Used in program 

| Module / File | Data Structure | Purpose |
|---------------|----------------|---------|
| `Queue.hpp` | Queue (Abstract/Base) | Defines queue interface (FIFO) |
| `Queue.cpp` | Queue Implementation | Implements enqueue/dequeue operations |
| `LaneQueue.hpp` | Traffic Lane Queue | Specialized queue for lane vehicle ordering |
| `vehicleQueue.hpp` | Vehicle Queue | Manages vehicles in a lane |
| `vehicle.hpp` | Vehicle Object | Stores attributes of a vehicle |
| `testqueue.cpp` | Queue Test Cases | Validates queue behavior |


  ## Running the Simulation

1. First, start the vehicle generator:

   ```bash
   ./bin/generator.exe
   
2. In a separate terminal, start the main simulation:

   ```bash
   ./bin/main.exe

3.   Watch as vehicles spawn and navigate through the intersection
  
4. Use the close button (X) to exit the simulationControls 

##  Functions Using Data Structures

| Function | Returns | Data Structure | Purpose |
|----------|---------|----------------|---------|
| `enqueue(vehicle)` | void | Queue | Adds vehicle to queue |
| `dequeue()` | Vehicle | Queue | Removes front vehicle |
| `peek()` / `front()` | Vehicle | Queue | View next vehicle |
| `isEmpty()` | bool | Queue | Check if empty |
| `size()` | int | Queue | Count vehicles |
| `display()` | void | Queue | Print all vehicles |
| `processTraffic()` | void | Queue + Loop | Main traffic simulation logic |
| `loadVehicles()` | void | Queue | Initialize traffic |

## 🚦 Algorithm for Traffic Processing
Function processTraffic()

while simulation not complete

for each laneQueue

if laneQueue is not empty

frontVehicle = laneQueue.peek()

if signal allows move

laneQueue.dequeue()

recordPassedVehicle(frontVehicle)

end if

end if

end for

updateSignals()

displayState()

end while

end function




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



