
#pragma once

#include "../models/flight.hpp"
#include "../data_structures/bst_flight.hpp"
#include <string>

class FlightManifest {
private:

    BSTflight flightTree;

public:

    // Inserts a flight into the manifest.
    bool insert(Flight* flight);

    // Searches for a flight by callsign.
    Flight* search(const std::string& callsign) const;

    // Displays flights alphabetically.
    void inorderTraversal() const;

    // Returns the height of the BST.
    int height() const;

    // Destroys the BST.
    void destroyTree();
};
