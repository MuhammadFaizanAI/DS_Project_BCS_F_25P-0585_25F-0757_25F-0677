
#ifndef RADAR_SWEEP_HPP
#define RADAR_SWEEP_HPP

#include <string>
#include "../data_structures/space_graph.hpp"

class RadarSweep {

private:
    const SpaceGraph& graph;

    // Custom queue for BFS.
    class IntQueue {
    private:
        int* data;
        int capacity;
        int front;
        int rear;
        int count;

    public:
        IntQueue(int size);
        ~IntQueue();

        bool isEmpty() const;
        bool enqueue(int value);
        bool dequeue(int& value);
    };

    // Custom stack for DFS.
    class IntStack {
    private:
        int* data;
        int capacity;
        int top;

    public:
        IntStack(int size);
        ~IntStack();

        bool isEmpty() const;
        bool push(int value);
        bool pop(int& value);
    };

    int findSector(const std::string& name) const;

public:
    explicit RadarSweep(const SpaceGraph& airspace);

    int bfsFrom(const std::string& sourceSector) const;

    void dfsFrom(const std::string& sourceSector) const;

    bool isReachable(
        const std::string& from,
        const std::string& to
    ) const;

    bool searchMissingFlight(
        const std::string& lastKnownSector
    ) const;
};

#endif
