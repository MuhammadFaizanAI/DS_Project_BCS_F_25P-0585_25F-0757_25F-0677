
#include "../../include/modules/radar_sweep.hpp"

#include <iostream>

// ==========================================
// CUSTOM QUEUE IMPLEMENTATION
// ==========================================

RadarSweep::IntQueue::IntQueue(int size) {
    capacity = size;
    data = new int[capacity];

    front = 0;
    rear = 0;
    count = 0;
}

RadarSweep::IntQueue::~IntQueue() {
    delete[] data;
}

bool RadarSweep::IntQueue::isEmpty() const {
    return count == 0;
}

bool RadarSweep::IntQueue::enqueue(int value) {

    if (count == capacity) {
        return false;
    }

    data[rear] = value;
    rear = (rear + 1) % capacity;
    count++;

    return true;
}

bool RadarSweep::IntQueue::dequeue(int& value) {

    if (isEmpty()) {
        return false;
    }

    value = data[front];
    front = (front + 1) % capacity;
    count--;

    return true;
}

// ==========================================
// CUSTOM STACK IMPLEMENTATION
// ==========================================

RadarSweep::IntStack::IntStack(int size) {
    capacity = size;
    data = new int[capacity];
    top = -1;
}

RadarSweep::IntStack::~IntStack() {
    delete[] data;
}

bool RadarSweep::IntStack::isEmpty() const {
    return top == -1;
}

bool RadarSweep::IntStack::push(int value) {

    if (top == capacity - 1) {
        return false;
    }

    data[++top] = value;

    return true;
}

bool RadarSweep::IntStack::pop(int& value) {

    if (isEmpty()) {
        return false;
    }

    value = data[top--];

    return true;
}

// ==========================================
// RADAR SWEEP CONSTRUCTOR
// ==========================================

RadarSweep::RadarSweep(const SpaceGraph& airspace)
    : graph(airspace) {
}

// ==========================================
// FIND SECTOR INDEX
// ==========================================

int RadarSweep::findSector(const std::string& name) const {

    for (int i = 0; i < graph.getSectorCount(); i++) {

        if (graph.getSectorName(i) == name) {
            return i;
        }
    }

    return -1;
}

// ==========================================
// BREADTH-FIRST SEARCH
// ==========================================

int RadarSweep::bfsFrom(
    const std::string& sourceSector
) const {

    int source = findSector(sourceSector);

    if (source == -1) {
        std::cout << "Error: Source sector not found.\n";
        return 0;
    }

    int total = graph.getSectorCount();

    bool* visited = new bool[total];
    int* level = new int[total];

    for (int i = 0; i < total; i++) {
        visited[i] = false;
        level[i] = -1;
    }

    IntQueue queue(total);

    visited[source] = true;
    level[source] = 0;

    queue.enqueue(source);

    std::cout << "\nBFS Radar Sweep\n";
    std::cout << "Source: " << sourceSector << '\n';
    std::cout << "--------------------------------\n";

    int current;
    int visitedCount = 0;

    while (queue.dequeue(current)) {

        visitedCount++;

        // Visit all adjacent sectors.
        for (int i = 0; i < total; i++) {

            int weight = graph.getWeight(current, i);

            if (weight != -1 && !visited[i]) {

                visited[i] = true;
                level[i] = level[current] + 1;

                queue.enqueue(i);
            }
        }
    }

    // Display sectors level by level.
    int maximumLevel = 0;

    for (int i = 0; i < total; i++) {

        if (level[i] > maximumLevel) {
            maximumLevel = level[i];
        }
    }

    for (int currentLevel = 0;
         currentLevel <= maximumLevel;
         currentLevel++) {

        std::cout << "Level " << currentLevel << ": ";

        for (int i = 0; i < total; i++) {

            if (level[i] == currentLevel) {

                std::cout << graph.getSectorName(i);

                if (i < total - 1) {
                    std::cout << " | ";
                }
            }
        }

        std::cout << '\n';
    }

    std::cout << "\nSectors within 2 hops of Control Tower:\n";

    int tower = findSector("Control Tower");

    if (tower != -1) {

        // Run a separate BFS from Control Tower.
        for (int i = 0; i < total; i++) {
            visited[i] = false;
            level[i] = -1;
        }

        IntQueue towerQueue(total);

        visited[tower] = true;
        level[tower] = 0;
        towerQueue.enqueue(tower);

        while (towerQueue.dequeue(current)) {

            for (int i = 0; i < total; i++) {

                int weight = graph.getWeight(current, i);

                if (weight != -1 && !visited[i]) {

                    visited[i] = true;
                    level[i] = level[current] + 1;

                    towerQueue.enqueue(i);
                }
            }
        }

        for (int i = 0; i < total; i++) {

            if (level[i] >= 0 && level[i] <= 2) {
                std::cout << "- "
                          << graph.getSectorName(i)
                          << " ("
                          << level[i]
                          << " hops)\n";
            }
        }
    }

    std::cout << "\nTotal visited sectors: "
              << visitedCount << '\n';

    delete[] visited;
    delete[] level;

    return visitedCount;
}

// ==========================================
// DEPTH-FIRST SEARCH
// ==========================================

void RadarSweep::dfsFrom(
    const std::string& sourceSector
) const {

    int source = findSector(sourceSector);

    if (source == -1) {
        std::cout << "Error: Source sector not found.\n";
        return;
    }

    int total = graph.getSectorCount();

    bool* visited = new bool[total];

    for (int i = 0; i < total; i++) {
        visited[i] = false;
    }

    IntStack stack(total);

    stack.push(source);
    visited[source] = true;

    std::cout << "\nDFS Sector Traversal\n";
    std::cout << "Source: " << sourceSector << '\n';
    std::cout << "--------------------------------\n";

    int current;
    int order = 1;

    while (stack.pop(current)) {

        std::cout << order++ << ". "
                  << graph.getSectorName(current)
                  << '\n';

        // Push neighbours in reverse index order.
        // This makes lower-index neighbours get visited first.
        for (int i = total - 1; i >= 0; i--) {

            int weight = graph.getWeight(current, i);

            if (weight != -1 && !visited[i]) {

                visited[i] = true;
                stack.push(i);
            }
        }
    }

    delete[] visited;
}

// ==========================================
// CHECK REACHABILITY USING BFS
// ==========================================

bool RadarSweep::isReachable(
    const std::string& from,
    const std::string& to
) const {

    int source = findSector(from);
    int destination = findSector(to);

    if (source == -1 || destination == -1) {
        return false;
    }

    int total = graph.getSectorCount();

    bool* visited = new bool[total];

    for (int i = 0; i < total; i++) {
        visited[i] = false;
    }

    IntQueue queue(total);

    visited[source] = true;
    queue.enqueue(source);

    int current;

    while (queue.dequeue(current)) {

        if (current == destination) {
            delete[] visited;
            return true;
        }

        for (int i = 0; i < total; i++) {

            int weight = graph.getWeight(current, i);

            if (weight != -1 && !visited[i]) {

                visited[i] = true;
                queue.enqueue(i);
            }
        }
    }

    delete[] visited;

    return false;
}

// ==========================================
// MISSING FLIGHT SEARCH
// ==========================================

bool RadarSweep::searchMissingFlight(
    const std::string& lastKnownSector
) const {

    std::cout << "\nMissing Flight Search\n";
    std::cout << "--------------------------------\n";

    std::cout << "Starting BFS from Control Tower...\n";
    std::cout << "Last known sector: "
              << lastKnownSector << '\n';

    bool found = isReachable(
        "Control Tower",
        lastKnownSector
    );

    if (found) {

        std::cout << "\nMissing flight located!\n";

        std::cout << "A BFS path exists from Control Tower "
                  << "to the last known sector.\n";

        std::cout << "Credibility reward: +20\n";
    }
    else {

        std::cout << "\nMissing flight could not be located.\n";

        std::cout << "No path exists from Control Tower "
                  << "to the last known sector.\n";
    }

    return found;
}
