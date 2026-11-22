
#pragma once

#include "../models/flight.hpp"
#include <iostream>
#include <string>

class AVLflight {
private:

    // Each AVL node stores a Flight pointer, two child pointers,
    // and its height.
    struct AVLNode {
        Flight* flight;
        AVLNode* left;
        AVLNode* right;
        int nodeHeight;

        AVLNode(Flight* data) {
            flight = data;
            left = nullptr;
            right = nullptr;
            nodeHeight = 1;
        }
    };

    AVLNode* root;

    // Returns the height of a node.
    int getHeight(AVLNode* node) const {
        if (node == nullptr) {
            return 0;
        }

        return node->nodeHeight;
    }

    // Returns the balance factor of a node.
    int getBalanceFactor(AVLNode* node) const {
        if (node == nullptr) {
            return 0;
        }

        return getHeight(node->left) - getHeight(node->right);
    }

    // Updates the height of a node.
    void updateHeight(AVLNode* node) {
        int leftHeight = getHeight(node->left);
        int rightHeight = getHeight(node->right);

        if (leftHeight > rightHeight) {
            node->nodeHeight = leftHeight + 1;
        }
        else {
            node->nodeHeight = rightHeight + 1;
        }
    }

    // Performs a right rotation.
    AVLNode* rotateRight(AVLNode* y) {

        AVLNode* x = y->left;
        AVLNode* temp = x->right;

        x->right = y;
        y->left = temp;

        updateHeight(y);
        updateHeight(x);

        return x;
    }

    // Performs a left rotation.
    AVLNode* rotateLeft(AVLNode* x) {

        AVLNode* y = x->right;
        AVLNode* temp = y->left;

        y->left = x;
        x->right = temp;

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    // Performs a left-right double rotation.
    AVLNode* rotateLeftRight(AVLNode* node) {

        node->left = rotateLeft(node->left);

        return rotateRight(node);
    }

    // Performs a right-left double rotation.
    AVLNode* rotateRightLeft(AVLNode* node) {

        node->right = rotateRight(node->right);

        return rotateLeft(node);
    }

    // Recursively inserts a flight and balances the tree.
    AVLNode* insertNode(AVLNode* node, Flight* flight) {

        // Normal BST insertion.
        if (node == nullptr) {
            return new AVLNode(flight);
        }

        if (flight->callsign < node->flight->callsign) {
            node->left = insertNode(node->left, flight);
        }
        else if (flight->callsign > node->flight->callsign) {
            node->right = insertNode(node->right, flight);
        }
        else {
            // Duplicate callsign: do not insert.
            return node;
        }

        // Update height after insertion.
        updateHeight(node);

        // Calculate balance factor.
        int balance = getBalanceFactor(node);

        // Left-Left case.
        if (balance > 1 &&
            flight->callsign < node->left->flight->callsign) {

            return rotateRight(node);
        }

        // Right-Right case.
        if (balance < -1 &&
            flight->callsign > node->right->flight->callsign) {

            return rotateLeft(node);
        }

        // Left-Right case.
        if (balance > 1 &&
            flight->callsign > node->left->flight->callsign) {

            return rotateLeftRight(node);
        }

        // Right-Left case.
        if (balance < -1 &&
            flight->callsign < node->right->flight->callsign) {

            return rotateRightLeft(node);
        }

        return node;
    }

    // Recursively searches for a callsign.
    Flight* searchNode(AVLNode* node,
                       const std::string& callsign) const {

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

    // Prints flights in alphabetical order.
    void inorder(AVLNode* node) const {

        if (node == nullptr) {
            return;
        }

        inorder(node->left);

        std::cout << "Callsign: "
                  << node->flight->callsign << '\n';

        inorder(node->right);
    }

    // Deletes AVL nodes using postorder traversal.
    void destroy(AVLNode* node) {

        if (node == nullptr) {
            return;
        }

        destroy(node->left);
        destroy(node->right);

        // Flight objects are owned by Registration.
        delete node;
    }

public:

    // Initializes an empty AVL tree.
    AVLflight() {
        root = nullptr;
    }

    // Prevents copying of dynamically allocated tree nodes.
    AVLflight(const AVLflight&) = delete;
    AVLflight& operator=(const AVLflight&) = delete;

    // Automatically destroys the AVL tree.
    ~AVLflight() {
        destroyTree();
    }

    // Inserts a flight into the AVL tree.
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

    // Displays flights alphabetically.
    void inorderTraversal() const {

        if (root == nullptr) {
            std::cout << "AVL tree is empty.\n";
            return;
        }

        std::cout << "\nAVL Flight Manifest (Alphabetical Order)\n";
        std::cout << "----------------------------------------\n";

        inorder(root);
    }

    // Returns the height of the AVL tree.
    int height() const {
        return getHeight(root);
    }

    // Deletes all AVL tree nodes.
    void destroyTree() {

        destroy(root);

        root = nullptr;
    }
};
