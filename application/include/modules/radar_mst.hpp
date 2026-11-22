
#ifndef RADAR_MST_HPP
#define RADAR_MST_HPP

#include "../data_structures/space_graph.hpp"

class RadarMST {

private:

    struct Edge {
        int source;
        int destination;
        int weight;
    };

    Edge* mstEdges;

    int mstEdgeCount;
    int totalCost;
    int vertexCount;

    bool mstComputed;

    // Union-Find data structure.
    class UnionFind {

    private:
        int* parent;
        int* rank;
        int size;

    public:
        explicit UnionFind(int count);
        ~UnionFind();

        int find(int vertex);

        bool unite(int first, int second);
    };

    // Custom insertion sort.
    void sortEdges(Edge edges[], int count) const;

    // Check connectivity after excluding one MST edge.
    bool isConnectedWithoutEdge(int excludedEdge) const;

    const SpaceGraph& graph;

public:

    explicit RadarMST(const SpaceGraph& airspace);

    ~RadarMST();

    // Compute Minimum Spanning Tree using Kruskal.
    bool computeMST();

    // Display selected corridors and total cost.
    void displayMST() const;

    // Verify that removing any MST edge disconnects the tree.
    bool verifyConnectivity() const;

    // Prevent shallow copying of dynamically allocated memory.
    RadarMST(const RadarMST&) = delete;
    RadarMST& operator=(const RadarMST&) = delete;
};

#endif
