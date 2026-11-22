
#include "../../include/modules/flight_index.hpp"

// Inserts a flight into the AVL tree.
bool FlightIndex::insert(Flight* flight) {
    return avlTree.insert(flight);
}

// Searches for a flight by callsign.
Flight* FlightIndex::search(const std::string& callsign) const {
    return avlTree.search(callsign);
}

// Displays flights in alphabetical order.
void FlightIndex::inorderTraversal() const {
    avlTree.inorderTraversal();
}

// Returns the height of the AVL tree.
int FlightIndex::height() const {
    return avlTree.height();
}

// Deletes all AVL tree nodes.
void FlightIndex::destroyTree() {
    avlTree.destroyTree();
}
