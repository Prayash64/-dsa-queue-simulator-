Assignment Information

Assignment Number: Assignment 1 - Queue Data Structure Implementation

Course: Data Structures and Algorithms

Student Name: Prayash BHattarai 

Roll Number: 15

Semester: 3rd semester

Date of Submission: December 28, 2025

Institution: Kathmandu University



## Traffic Junction Stimulation 

This project simulates traffic movement at an intersection using C++. The simulation models vehicle movement, traffic signals, and congestion patterns.

## Program output 

![demo](https://github.com/user-attachments/assets/6027c4ec-cd8d-4ddd-8e24-0dd8dba59deb)


## Program structure 


![program structure ](https://github.com/user-attachments/assets/aa747677-7263-4617-a5d1-9112fa8d8b13)




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

   ##  Key Accomplishments

- **Circular Logic:** Maximized memory efficiency by reusing space in the array after vehicles exit the queue.
  
- **High Performance:** Achieved **$O(1)$** time complexity for all core traffic operations.
  
- **Congestion Control:** Implemented logic to detect and prevent data overflow during peak traffic simulations.
  
- **OOP Design:** Built a modular system in C++ that separates data management from the user interface.
  

 ##  Data Structures Used in program 

| Module / File | Data Structure | Purpose |
|---------------|----------------|---------|
| `Queue.hpp` | Queue (Abstract/Base) | Defines queue interface (FIFO) |
| `Queue.cpp` | Queue Implementation | Implements enqueue/dequeue operations |
| `LaneQueue.hpp` | Traffic Lane Queue | Specialized queue for lane vehicle ordering |
| `vehicleQueue.hpp` | Vehicle Queue | Manages vehicles in a lane |
| `vehicle.hpp` | Vehicle Object | Stores attributes of a vehicle |
| `testqueue.cpp` | Queue Test Cases | Validates queue behavior |

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

A. Generator (generator.exe):

1. Generates vehicles with random properties

2. Writes vehicle data to a file for the main program to read

3.  Spawns new vehicles every 500 milliseconds

B. Main Simulation (main.exe):

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

1. main.c : Program entry point and main simulation loop
   
2. traffic_simulation.h : Header file containing structs and function declarations
   
3. traffic_simulation.c : Implementation of traffic simulation logic
   
4. generator.c : Vehicle generation logic
   




  ## Running the Simulation

1. First, start the vehicle generator:

   ```bash
   ./bin/generator.exe
   
2. In a separate terminal, start the main simulation:

   ```bash
   ./bin/main.exe

3.   Watch as vehicles spawn and navigate through the intersection
  
4. Use the close button (X) to exit the simulationControls 



---

## Detailed Algorithm

   ### 1. Initialize the Simulation

      - Include necessary headers for `Queue`, `Vehicle`, and `LaneQueue`.
  
      - Initialize individual lane queues for each traffic lane.
  
      - Set traffic light signals and simulation parameters (window size, lane width, etc.).
  

   ### 2. Vehicle Insertion

      - For each lane, create `Vehicle` objects with attributes like ID, speed, and arrival time.
  
      - Use `enqueue()` to add vehicles to the corresponding lane queue.
  
      - Maintain FIFO order to simulate real-world traffic arrival.
  

   ### 3. Traffic Signal Processing

      - Continuously check traffic light states for each lane.
  
      - Allow vehicles at green signals to move while holding vehicles at red signals.
  

   ### 4. Vehicle Movement

      - For each lane:
  
        - If the traffic signal is green, dequeue the front vehicle using `dequeue()`.
    
        - Update vehicle position and simulation visualization.
    
        - If lane queue becomes empty, wait for next vehicle insertion.
    

   ### 5. Congestion Handling

      - Monitor queue size for each lane.
  
      - Implement overflow checks to prevent exceeding `MAX_VEHICLES`.
  
      - Reuse memory efficiently for departed vehicles (circular queue logic).
  

   ### 6. Simulation Loop

      - Repeat the above steps in a loop until the simulation ends or user exits.
  
      - Update graphical visualization and lane states in real-time.
  
      - Ensure each core queue operation (enqueue, dequeue, front access) runs in constant time, O(1).
  

   ### 7. Termination

      -  End simulation gracefully.
  
      - Clear all queues and release allocated memory.
  
      - Optionally, display statistics such as vehicles passed and congestion level.
  

 ## Implementation Details

   ### Queue Data Structure
  
      typedef struct Node {
      
       Vehicle vehicle;
       
       struct Node* next;
       
      } Node;

      typedef struct {
      
       Node* front;
       
       Node* rear;
       
       int size;
       
      } Queue;
      
      ```

   ### Vehicle States

      typedef enum {
      
       STATE_MOVING,
       
       STATE_STOPPING,
       
       STATE_STOPPED,
       
       STATE_TURNING
       
      } VehicleState;


### Special Traffic Rules

The simulation implements realistic traffic rules including:

1. **Emergency Vehicle Priority**: Ambulances, police cars, and fire trucks automatically trigger green lights and can bypass red lights.
   
2. **Right Turn on Red**: Vehicles turning right can generally proceed even when the light is red (as in many real-world jurisdictions).
   
3. **Congestion Management**: If a lane becomes congested (more than 5 vehicles), the system prioritizes that lane.
   
4. **Wait Time Management**: Regular vehicles that have been waiting too long at a red light may eventually proceed (simulating real-world driver behavior).



## Source Codes 

Repository:  https://github.com/Prayash64/-dsa-queue-simulator-.git


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



