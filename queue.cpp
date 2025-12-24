#include "Queue.h"
#include <iostream> 


Queue::Queue() : front(nullptr), rear(nullptr), size(0) {}


Queue::~Queue() {
    while (!isEmpty()) {
        
        delete dequeue();
    }
}


void Queue::enqueue(int id, int arrival_time) {
    
    Vehicle* newVehicle = new Vehicle(id, arrival_time);
    
    if (rear == nullptr) {
        front = rear = newVehicle;
    } else {
        rear->next = newVehicle;
        rear = newVehicle;
    }
    size++;
}


Vehicle* Queue::dequeue() {
    if (front == nullptr) return nullptr;

    Vehicle* temp = front;
    front = front->next;
    
    if (front == nullptr) {
        rear = nullptr;
    }
    
    size--;
    return temp;  
}


bool Queue::isEmpty() const {
    return (front == nullptr);
}


void Queue::displayQueue() const {
    Vehicle* temp = front;
    while (temp) {
        std::cout << "Vehicle ID: " << temp->id 
                  << ", Arrival Time: " << temp->arrival_time << "\n";
        temp = temp->next;
    }
}