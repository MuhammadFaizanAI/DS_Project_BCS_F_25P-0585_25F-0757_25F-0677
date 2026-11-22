
#include <iostream>

#include "application/include/data_structures/space_graph.hpp"
#include "application/include/modules/radar_sweep.hpp"

int main() {

    SpaceGraph graph;

    if (!graph.loadFromFile("application/data/airspace.txt")) {
        return 1;
    }

    RadarSweep radar(graph);

    // Test 1: BFS
    radar.bfsFrom("Control Tower");

    // Test 2: DFS
    radar.dfsFrom("Control Tower");

    // Test 3: Reachability
    std::cout << "\nReachability Tests\n";
    std::cout << "--------------------------------\n";

    std::cout << "Alpha Tree -> Restricted Zone: "
              << (radar.isReachable(
                     "Alpha Tree (South)",
                     "Restricted Zone"
                 ) ? "Reachable" : "Not Reachable")
              << '\n';

    std::cout << "Alpha Tree -> Runway 27: "
              << (radar.isReachable(
                     "Alpha Tree (South)",
                     "Runway 27"
                 ) ? "Reachable" : "Not Reachable")
              << '\n';

    // Test 4: Missing flight
    radar.searchMissingFlight("Restricted Zone");

    return 0;
}
