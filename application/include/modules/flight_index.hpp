
#pragma once

#include "../models/flight.hpp"
#include "../data_structures/avl_flight.hpp"
#include <string>

class FlightIndex {
private:

    AVLflight avlTree;

public:

    // Inserts a flight into the AVL index.
    bool insert(Flight* flight);

    // Searches for a flight by callsign.
    Flight* search(const std::string& callsign) const;

    // Displays flights alphabetically.
    void inorderTraversal() const;

    // Returns the AVL tree height.
    int height() const;

    // Destroys the AVL tree.
    void destroyTree();
};
