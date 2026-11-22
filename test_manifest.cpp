
#include <iostream>
#include "application/include/modules/flight_manifest.hpp"

int main() {

    FlightManifest manifest;

    // Create three sample flights.
    Flight* f1 = new Flight();
    Flight* f2 = new Flight();
    Flight* f3 = new Flight();

    f1->callsign = "PK103";
    f2->callsign = "PK101";
    f3->callsign = "PK102";

    // Insert flights into BST.
    manifest.insert(f1);
    manifest.insert(f2);
    manifest.insert(f3);

    // Display flights alphabetically.
    manifest.inorderTraversal();

    // Search for a flight.
    Flight* result = manifest.search("PK102");

    if (result != nullptr) {
        std::cout << "\nFlight found: "
                  << result->callsign << '\n';
    }
    else {
        std::cout << "\nFlight not found.\n";
    }

    // Display tree height.
    std::cout << "\nBST Height: "
              << manifest.height() << '\n';

    // Destroy BST nodes.
    manifest.destroyTree();

    // The test owns these Flight objects.
    delete f1;
    delete f2;
    delete f3;

    return 0;
}
