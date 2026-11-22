
#include "modules/radar_mst.hpp"

#include <iostream>

// ==========================================
// UNION-FIND CONSTRUCTOR
// ==========================================

RadarMST::UnionFind::UnionFind(int count) {

    size = count;

    parent = new int[size];
    rank = new int[size];

    for (int i = 0; i < size; i++) {

        parent[i] = i;
        rank[i] = 0;
    }
}

// ==========================================
// UNION-FIND DESTRUCTOR
// ==========================================

RadarMST::UnionFind::~UnionFind() {

    delete[] parent;
    delete[] rank;
}

// ==========================================
// FIND WITH PATH COMPRESSION
// ==========================================

int RadarMST::UnionFind::find(int vertex) {

    if (parent[vertex] != vertex) {

        parent[vertex] = find(parent[vertex]);
    }

    return parent[vertex];
}

// ==========================================
// UNION BY RANK
// ==========================================

bool RadarMST::UnionFind::unite(
    int first,
    int second
) {

    int rootFirst = find(first);
    int rootSecond = find(second);

    // Both vertices already belong to the same component.
    if (rootFirst == rootSecond) {

        return false;
    }

    // Attach smaller tree below larger tree.
    if (rank[rootFirst] < rank[rootSecond]) {

        parent[rootFirst] = rootSecond;
    }
    else if (rank[rootFirst] > rank[rootSecond]) {

        parent[rootSecond] = rootFirst;
    }
    else {

        parent[rootSecond] = rootFirst;

        rank[rootFirst]++;
    }

    return true;
}

// ==========================================
// RADAR MST CONSTRUCTOR
// ==========================================

RadarMST::RadarMST(const SpaceGraph& airspace)
    : graph(airspace) {

    mstEdges = nullptr;

    mstEdgeCount = 0;
    totalCost = 0;
    vertexCount = graph.getSectorCount();

    mstComputed = false;
}

// ==========================================
// RADAR MST DESTRUCTOR
// ==========================================

RadarMST::~RadarMST() {

    delete[] mstEdges;
}

// ==========================================
// CUSTOM INSERTION SORT
// ==========================================

void RadarMST::sortEdges(
    Edge edges[],
    int count
) const {

    for (int i = 1; i < count; i++) {

        Edge current = edges[i];

        int j = i - 1;

        while (j >= 0 &&
               edges[j].weight > current.weight) {

            edges[j + 1] = edges[j];

            j--;
        }

        edges[j + 1] = current;
    }
}

// ==========================================
// COMPUTE MINIMUM SPANNING TREE
// KRUSKAL'S ALGORITHM
// ==========================================

bool RadarMST::computeMST() {

    // Reset previous MST.
    delete[] mstEdges;

    mstEdges = nullptr;

    mstEdgeCount = 0;
    totalCost = 0;
    mstComputed = false;

    vertexCount = graph.getSectorCount();

    if (vertexCount == 0) {

        std::cout << "Error: Airspace graph is empty.\n";

        return false;
    }

    // ======================================
    // STEP 1: COUNT MAXIMUM POSSIBLE EDGES
    // ======================================

    int maximumEdges =
        (vertexCount * (vertexCount - 1)) / 2;

    Edge* edges = new Edge[maximumEdges];

    int edgeCount = 0;

    // ======================================
    // STEP 2: COLLECT UNDIRECTED EDGES
    // ======================================

    // The adjacency matrix stores both directions.
    // Therefore, use j = i + 1 to avoid duplicates.

    for (int i = 0; i < vertexCount; i++) {

        for (int j = i + 1; j < vertexCount; j++) {

            int weight = graph.getWeight(i, j);

            if (weight != -1) {

                if (weight <= 0) {

                    std::cout << "Error: Invalid corridor weight.\n";

                    delete[] edges;

                    return false;
                }

                edges[edgeCount].source = i;
                edges[edgeCount].destination = j;
                edges[edgeCount].weight = weight;

                edgeCount++;
            }
        }
    }

    // ======================================
    // STEP 3: SORT EDGES BY WEIGHT
    // ======================================

    sortEdges(edges, edgeCount);

    // ======================================
    // STEP 4: INITIALIZE UNION-FIND
    // ======================================

    UnionFind sets(vertexCount);

    // MST can contain at most V - 1 edges.
    mstEdges = new Edge[vertexCount - 1];

    // ======================================
    // STEP 5: APPLY KRUSKAL'S ALGORITHM
    // ======================================

    for (int i = 0;
         i < edgeCount && mstEdgeCount < vertexCount - 1;
         i++) {

        int source = edges[i].source;
        int destination = edges[i].destination;

        // Select edge only if it does not create a cycle.
        if (sets.unite(source, destination)) {

            mstEdges[mstEdgeCount] = edges[i];

            mstEdgeCount++;

            totalCost += edges[i].weight;
        }
    }

    delete[] edges;

    // ======================================
    // STEP 6: CHECK GRAPH CONNECTIVITY
    // ======================================

    if (mstEdgeCount != vertexCount - 1) {

        std::cout << "Error: Airspace graph is disconnected.\n";

        delete[] mstEdges;

        mstEdges = nullptr;

        mstEdgeCount = 0;
        totalCost = 0;

        return false;
    }

    mstComputed = true;

    std::cout << "\nMinimum Spanning Tree computed successfully.\n";

    return true;
}

// ==========================================
// DISPLAY MINIMUM SPANNING TREE
// ==========================================

void RadarMST::displayMST() const {

    if (!mstComputed) {

        std::cout << "Error: Compute MST first.\n";

        return;
    }

    std::cout << "\n====================================\n";
    std::cout << "       MINIMUM RADAR COVERAGE\n";
    std::cout << "====================================\n";

    for (int i = 0; i < mstEdgeCount; i++) {

        int source = mstEdges[i].source;

        int destination = mstEdges[i].destination;

        int weight = mstEdges[i].weight;

        std::cout << i + 1 << ". "
                  << graph.getSectorName(source)
                  << " <-> "
                  << graph.getSectorName(destination)
                  << " | Cost: "
                  << weight
                  << '\n';
    }

    std::cout << "------------------------------------\n";

    std::cout << "Total sectors: "
              << vertexCount << '\n';

    std::cout << "Selected corridors: "
              << mstEdgeCount << '\n';

    std::cout << "Minimum total cost: "
              << totalCost << '\n';

    std::cout << "====================================\n";
}

// ==========================================
// CHECK CONNECTIVITY WITHOUT ONE MST EDGE
// ==========================================

bool RadarMST::isConnectedWithoutEdge(
    int excludedEdge
) const {

    bool* visited = new bool[vertexCount];

    int* queue = new int[vertexCount];

    for (int i = 0; i < vertexCount; i++) {

        visited[i] = false;
    }

    int front = 0;
    int rear = 0;

    // Start BFS from vertex 0.
    visited[0] = true;

    queue[rear++] = 0;

    int visitedCount = 0;

    while (front < rear) {

        int current = queue[front++];

        visitedCount++;

        // Explore all MST edges.
        for (int i = 0; i < mstEdgeCount; i++) {

            // Ignore the edge currently being tested.
            if (i == excludedEdge) {

                continue;
            }

            int next = -1;

            if (mstEdges[i].source == current) {

                next = mstEdges[i].destination;
            }
            else if (mstEdges[i].destination == current) {

                next = mstEdges[i].source;
            }

            if (next != -1 && !visited[next]) {

                visited[next] = true;

                queue[rear++] = next;
            }
        }
    }

    delete[] visited;
    delete[] queue;

    return visitedCount == vertexCount;
}

// ==========================================
// VERIFY MST CONNECTIVITY
// ==========================================

bool RadarMST::verifyConnectivity() const {

    if (!mstComputed) {

        std::cout << "Error: Compute MST first.\n";

        return false;
    }

    std::cout << "\n====================================\n";
    std::cout << "       MST CONNECTIVITY TEST\n";
    std::cout << "====================================\n";

    bool allEdgesEssential = true;

    for (int i = 0; i < mstEdgeCount; i++) {

        bool connected = isConnectedWithoutEdge(i);

        std::cout << "\nRemoving corridor: "
                  << graph.getSectorName(mstEdges[i].source)
                  << " <-> "
                  << graph.getSectorName(mstEdges[i].destination)
                  << '\n';

        if (!connected) {

            std::cout << "Result: Network disconnected.\n";
        }
        else {

            std::cout << "Result: Network still connected.\n";

            allEdgesEssential = false;
        }
    }

    std::cout << "\n------------------------------------\n";

    if (allEdgesEssential) {

        std::cout << "PASS: Every MST edge is essential.\n";

        std::cout << "Removing any selected corridor "
                  << "disconnects the MST.\n";
    }
    else {

        std::cout << "FAIL: At least one edge was not essential.\n";
    }

    return allEdgesEssential;
}
