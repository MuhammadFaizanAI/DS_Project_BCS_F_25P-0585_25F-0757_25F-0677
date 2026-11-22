
#pragma once

#include "../models/flight.hpp"
#include <iostream>
#include <string>

class BSTflight {
private:

    // Each node stores a pointer to a Flight object.
    struct BSTNode {
        Flight* flight;
        BSTNode* left;
        BSTNode* right;

        BSTNode(Flight* data) {
            flight = data;
            left = nullptr;
            right = nullptr;
        }
    };

    BSTNode* root;

    // Recursively inserts a new node at its correct position.
    BSTNode* insertNode(BSTNode* node, Flight* flight) {

        if (node == nullptr) {
            return new BSTNode(flight);
        }

        if (flight->callsign < node->flight->callsign) {
            node->left = insertNode(node->left, flight);
        }
        else if (flight->callsign > node->flight->callsign) {
            node->right = insertNode(node->right, flight);
        }

        return node;
    }

    // Recursively searches for a callsign.
    Flight* searchNode(BSTNode* node, const std::string& callsign) const {

        if (node == nullptr) {
            return nullptr;
        }

        if (callsign == node->flight->callsign) {
            return node->flight;
        }

        if (callsign < node->flight->callsign) {
            return searchNode(node->left, callsign);
        }

        return searchNode(node->right, callsign);
    }

    // Left -> Root -> Right gives alphabetical order.
    void inorder(BSTNode* node) const {

        if (node == nullptr) {
            return;
        }

        inorder(node->left);

        std::cout << "Callsign: "
                  << node->flight->callsign << '\n';

        inorder(node->right);
    }

    // Calculates tree height recursively.
    int calculateHeight(BSTNode* node) const {

        if (node == nullptr) {
            return 0;
        }

        int leftHeight = calculateHeight(node->left);
        int rightHeight = calculateHeight(node->right);

        if (leftHeight > rightHeight) {
            return leftHeight + 1;
        }

        return rightHeight + 1;
    }

    // Deletes tree nodes using postorder traversal.
    void destroy(BSTNode* node) {

        if (node == nullptr) {
            return;
        }

        destroy(node->left);
        destroy(node->right);

        // Flight objects are owned by Registration.
        // Only delete the BST node here.
        delete node;
    }

public:

    // Initializes an empty BST.
    BSTflight() {
        root = nullptr;
    }

    // Prevents copying because the tree manages dynamic nodes.
    BSTflight(const BSTflight&) = delete;
    BSTflight& operator=(const BSTflight&) = delete;

    // Automatically releases all BST nodes.
    ~BSTflight() {
        destroyTree();
    }

    // Inserts a flight into the BST.
    // Returns false for nullptr or duplicate callsigns.
    bool insert(Flight* flight) {

        if (flight == nullptr) {
            return false;
        }

        if (search(flight->callsign) != nullptr) {
            return false;
        }

        root = insertNode(root, flight);

        return true;
    }

    // Searches for a flight using its callsign.
    Flight* search(const std::string& callsign) const {
        return searchNode(root, callsign);
    }

    // Prints all flights in alphabetical callsign order.
    void inorderTraversal() const {

        if (root == nullptr) {
            std::cout << "BST is empty.\n";
            return;
        }

        std::cout << "\nFlight Manifest (Alphabetical Order)\n";
        std::cout << "-------------------------------------\n";

        inorder(root);
    }

    // Returns the height of the BST.
    int height() const {
        return calculateHeight(root);
    }

    // Deletes all dynamically allocated BST nodes.
    void destroyTree() {

        destroy(root);

        root = nullptr;
    }
};
