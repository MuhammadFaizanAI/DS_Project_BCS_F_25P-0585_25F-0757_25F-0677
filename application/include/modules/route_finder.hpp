
#ifndef ROUTE_FINDER_HPP
#define ROUTE_FINDER_HPP

#include <string>
#include "../data_structures/space_graph.hpp"

class RouteFinder {

private:
    const SpaceGraph& graph;

    // One entry in the min-heap.
    struct HeapNode {
        int vertex;
        int distance;
    };

    // Custom binary min-heap.
    class MinHeap {
    private:
        HeapNode* data;
        int capacity;
        int heapSize;

        void swapNodes(int a, int b);
        void heapifyUp(int index);
        void heapifyDown(int index);

    public:
        explicit MinHeap(int size);
        ~MinHeap();

        bool isEmpty() const;

        bool insert(int vertex, int distance);

        HeapNode extractMin();
    };

    int findSector(const std::string& name) const;

public:
    explicit RouteFinder(const SpaceGraph& airspace);

    bool findFastestRoute(
        const std::string& source,
        const std::string& destination,
        std::string* path,
        int& pathLength,
        int& totalTravelTime
    ) const;
};

#endif
