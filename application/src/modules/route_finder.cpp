
#include "modules/route_finder.hpp"

#include <iostream>
#include <climits>

// ==========================================
// MIN-HEAP CONSTRUCTOR AND DESTRUCTOR
// ==========================================

RouteFinder::MinHeap::MinHeap(int size) {

    capacity = size;

    if (capacity < 1) {
        capacity = 1;
    }

    data = new HeapNode[capacity];

    heapSize = 0;
}

RouteFinder::MinHeap::~MinHeap() {
    delete[] data;
}

// ==========================================
// MIN-HEAP HELPER FUNCTIONS
// ==========================================

void RouteFinder::MinHeap::swapNodes(int a, int b) {

    HeapNode temp = data[a];

    data[a] = data[b];
    data[b] = temp;
}

void RouteFinder::MinHeap::heapifyUp(int index) {

    while (index > 0) {

        int parent = (index - 1) / 2;

        if (data[parent].distance <= data[index].distance) {
            break;
        }

        swapNodes(parent, index);

        index = parent;
    }
}

void RouteFinder::MinHeap::heapifyDown(int index) {

    while (true) {

        int smallest = index;

        int left = (2 * index) + 1;
        int right = (2 * index) + 2;

        if (left < heapSize &&
            data[left].distance < data[smallest].distance) {

            smallest = left;
        }

        if (right < heapSize &&
            data[right].distance < data[smallest].distance) {

            smallest = right;
        }

        if (smallest == index) {
            break;
        }

        swapNodes(index, smallest);

        index = smallest;
    }
}

// ==========================================
// MIN-HEAP OPERATIONS
// ==========================================

bool RouteFinder::MinHeap::isEmpty() const {
    return heapSize == 0;
}

bool RouteFinder::MinHeap::insert(
    int vertex,
    int distance
) {

    if (heapSize == capacity) {
        return false;
    }

    data[heapSize].vertex = vertex;
    data[heapSize].distance = distance;

    heapifyUp(heapSize);

    heapSize++;

    return true;
}

RouteFinder::HeapNode
RouteFinder::MinHeap::extractMin() {

    HeapNode result = data[0];

    data[0] = data[heapSize - 1];

    heapSize--;

    if (heapSize > 0) {
        heapifyDown(0);
    }

    return result;
}

// ==========================================
// ROUTE FINDER CONSTRUCTOR
// ==========================================

RouteFinder::RouteFinder(const SpaceGraph& airspace)
    : graph(airspace) {
}

// ==========================================
// FIND SECTOR INDEX
// ==========================================

int RouteFinder::findSector(
    const std::string& name
) const {

    for (int i = 0; i < graph.getSectorCount(); i++) {

        if (graph.getSectorName(i) == name) {
            return i;
        }
    }

    return -1;
}

// ==========================================
// DIJKSTRA'S SHORTEST PATH ALGORITHM
// ==========================================

bool RouteFinder::findFastestRoute(
    const std::string& source,
    const std::string& destination,
    std::string* path,
    int& pathLength,
    int& totalTravelTime
) const {

    pathLength = 0;
    totalTravelTime = -1;

    if (path == nullptr) {
        std::cout << "Error: Path array is null.\n";
        return false;
    }

    int sourceIndex = findSector(source);
    int destinationIndex = findSector(destination);

    if (sourceIndex == -1 || destinationIndex == -1) {

        std::cout << "Error: Source or destination not found.\n";

        return false;
    }

    int total = graph.getSectorCount();

    // Distance from source to every sector.
    int* distance = new int[total];

    // Previous sector in the shortest path.
    int* parent = new int[total];

    // Whether the shortest distance is finalized.
    bool* visited = new bool[total];

    for (int i = 0; i < total; i++) {

        distance[i] = INT_MAX;
        parent[i] = -1;
        visited[i] = false;
    }

    // At most one successful relaxation per directed edge.
    // A matrix with n vertices has at most n*n directed entries.
    MinHeap heap(total * total + 1);

    distance[sourceIndex] = 0;

    heap.insert(sourceIndex, 0);

    // ======================================
    // MAIN DIJKSTRA LOOP
    // ======================================

    while (!heap.isEmpty()) {

        HeapNode current = heap.extractMin();

        int u = current.vertex;

        // Ignore an outdated heap entry.
        if (visited[u]) {
            continue;
        }

        if (current.distance != distance[u]) {
            continue;
        }

        visited[u] = true;

        // Destination reached.
        if (u == destinationIndex) {
            break;
        }

        // Check every possible neighboring sector.
        for (int v = 0; v < total; v++) {

            int weight = graph.getWeight(u, v);

            // No corridor exists.
            if (weight == -1) {
                continue;
            }

            if (visited[v]) {
                continue;
            }

            // Avoid integer overflow.
            if (distance[u] > INT_MAX - weight) {
                continue;
            }

            int newDistance = distance[u] + weight;

            // Found a faster route.
            if (newDistance < distance[v]) {

                distance[v] = newDistance;

                parent[v] = u;

                heap.insert(v, newDistance);
            }
        }
    }

    // ======================================
    // CHECK WHETHER DESTINATION WAS REACHED
    // ======================================

    if (distance[destinationIndex] == INT_MAX) {

        std::cout << "\nNo route exists from "
                  << source << " to "
                  << destination << ".\n";

        delete[] distance;
        delete[] parent;
        delete[] visited;

        return false;
    }

    // ======================================
    // RECONSTRUCT THE SHORTEST PATH
    // ======================================

    int* reversePath = new int[total];

    int count = 0;
    int current = destinationIndex;

    while (current != -1 && count < total) {

        reversePath[count++] = current;

        if (current == sourceIndex) {
            break;
        }

        current = parent[current];
    }

    // Verify that reconstruction reached the source.
    if (count == 0 || reversePath[count - 1] != sourceIndex) {

        delete[] reversePath;
        delete[] distance;
        delete[] parent;
        delete[] visited;

        std::cout << "Error: Could not reconstruct route.\n";

        return false;
    }

    // Reverse the route into source-to-destination order.
    pathLength = count;

    for (int i = 0; i < count; i++) {

        int vertex = reversePath[count - 1 - i];

        path[i] = graph.getSectorName(vertex);
    }

    totalTravelTime = distance[destinationIndex];

    // ======================================
    // DISPLAY RESULT
    // ======================================

    std::cout << "\nFastest Route Found\n";
    std::cout << "--------------------------------\n";

    std::cout << "Source: " << source << '\n';

    std::cout << "Destination: "
              << destination << '\n';

    std::cout << "Route: ";

    for (int i = 0; i < pathLength; i++) {

        std::cout << path[i];

        if (i < pathLength - 1) {
            std::cout << " -> ";
        }
    }

    std::cout << "\nTotal Travel Time: "
              << totalTravelTime
              << " seconds\n";

    std::cout << "Total Hops: "
              << pathLength - 1 << '\n';

    // ======================================
    // RELEASE DYNAMIC MEMORY
    // ======================================

    delete[] reversePath;
    delete[] distance;
    delete[] parent;
    delete[] visited;

    return true;
}
