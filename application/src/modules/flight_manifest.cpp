
#include "../../include/modules/flight_manifest.hpp"

// Inserts a flight into the BST.
bool FlightManifest::insert(Flight* flight) {
    return flightTree.insert(flight);
}

// Searches for a flight using its callsign.
Flight* FlightManifest::search(const std::string& callsign) const {
    return flightTree.search(callsign);
}

// Displays the manifest in alphabetical order.
void FlightManifest::inorderTraversal() const {
    flightTree.inorderTraversal();
}

// Returns the BST height.
int FlightManifest::height() const {
    return flightTree.height();
}

// Deletes all BST nodes.
void FlightManifest::destroyTree() {
    flightTree.destroyTree();
}
