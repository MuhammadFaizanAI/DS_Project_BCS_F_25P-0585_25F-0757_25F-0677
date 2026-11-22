
#include <iostream>
#include "application/include/modules/flight_manifest.hpp"
#include "application/include/modules/flight_index.hpp"

int main() {

    FlightManifest bst;
    FlightIndex avl;

    const int SIZE = 15;

    const char* callsigns[SIZE] = {
        "PK101", "PK102", "PK103",
        "PK104", "PK105", "PK106",
        "PK107", "PK108", "PK109",
        "PK110", "PK111", "PK112",
        "PK113", "PK114", "PK115"
    };

    // Create and insert the same flights into both trees.
    Flight* flights[SIZE];

    for (int i = 0; i < SIZE; i++) {

        flights[i] = new Flight();

        flights[i]->callsign = callsigns[i];

        bst.insert(flights[i]);
        avl.insert(flights[i]);
    }

    // Display both tree heights.
    std::cout << "\n========== HEIGHT COMPARISON ==========\n";

    std::cout << "BST Height: " << bst.height() << '\n';
    std::cout << "AVL Height: " << avl.height() << '\n';

    // Display AVL traversal.
    avl.inorderTraversal();

    // Test AVL search.
    Flight* result = avl.search("PK108");

    if (result != nullptr) {
        std::cout << "\nFlight found: "
                  << result->callsign << '\n';
    }
    else {
        std::cout << "\nFlight not found.\n";
    }

    // Destroy tree nodes before deleting Flight objects.
    bst.destroyTree();
    avl.destroyTree();

    for (int i = 0; i < SIZE; i++) {
        delete flights[i];
    }

    return 0;
}
