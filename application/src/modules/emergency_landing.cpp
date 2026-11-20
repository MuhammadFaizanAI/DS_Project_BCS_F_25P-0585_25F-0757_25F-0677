#include "../../include/modules/emergency_landing.hpp"

EmergencyLanding::EmergencyLanding() : emergencyHeap(100) {}

// Normal Queue operations
void EmergencyLanding::enqueueNormal(Flight* f) {
    normalQueue.enqueue(f);
}

Flight* EmergencyLanding::dequeueNormal() {
    return normalQueue.dequeue();
}

Flight* EmergencyLanding::frontNormal() const {
    return normalQueue.front();
}

bool EmergencyLanding::isEmptyNormal() const {
    return normalQueue.isEmpty();
}

void EmergencyLanding::displayNormalQueue() const {
    normalQueue.display();
}

// Emergency Min-Heap operations
void EmergencyLanding::insertEmergency(Flight* f) {
    HeapNode node(f);
    emergencyHeap.insert(node);
}

Flight* EmergencyLanding::extractMin() {
    HeapNode minNode = emergencyHeap.extractMin();
    return minNode.flight;
}

Flight* EmergencyLanding::peekMin() const {
    HeapNode minNode = emergencyHeap.peekMin();
    return minNode.flight;
}

bool EmergencyLanding::isEmptyHeap() const {
    return emergencyHeap.isEmpty();
}

void EmergencyLanding::displayHeap() const {
    emergencyHeap.display();
}

// Process next landing: normal queue first, otherwise highest-priority emergency
Flight* EmergencyLanding::processNextLanding() {
    if (!normalQueue.isEmpty()) {
        return normalQueue.dequeue();
    }
    if (!emergencyHeap.isEmpty()) {
        return extractMin();
    }
    return nullptr;
}