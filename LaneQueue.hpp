#ifndef LANE_QUEUE_H
#define LANE_QUEUE_H

#include <queue>
#include <vector>

struct Lane {
    int lane_id;
    int vehicle_count;
    
    bool operator<(const Lane& other) const {
        return vehicle_count < other.vehicle_count; // Higher count = Higher priority
    }
};

class LaneQueue {
private:
    std::priority_queue<Lane> pq;
public:
    void addLane(int lane_id, int vehicle_count);
    Lane getHighestPriorityLane();
    bool isEmpty();
};

#endif