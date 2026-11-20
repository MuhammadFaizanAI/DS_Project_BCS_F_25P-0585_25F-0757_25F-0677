#ifndef EMERGENCY_DISPATCH
#define EMERGENCY_DISPACH
#include"../data_structures/flight_linked_list.hpp"
#include"../data_structures/normal_queue.hpp"
#include"../data_structures/emergency_heap.hpp"

class EmergencyLanding
{
	Queue<Flight*> normalQueue;
	MinHeap<HeapNode> emergencyHeap;
public:
    EmergencyLanding();

    // Normal Queue functions
    void enqueueNormal(Flight* f);
    Flight* dequeueNormal();
    Flight* frontNormal() const;
    bool isEmptyNormal() const;
    void displayNormalQueue() const;

    // Emergency Min-Heap functions
    void insertEmergency(Flight* f);
    Flight* extractMin();
    Flight* peekMin() const;
    bool isEmptyHeap() const;
    void displayHeap() const;

    // Main dispatch decision function
    Flight* processNextLanding();
};
#endif