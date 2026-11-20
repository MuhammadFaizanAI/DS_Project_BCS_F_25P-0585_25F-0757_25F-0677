#ifndef MIN_HEAP_HPP
#define MIN_HEAP_HPP

#include <iostream>
#include "./flight_linked_list.hpp"
using namespace std;

// Wrapper node for priority and arrivalTick comparison
struct HeapNode {
    int priority;
    int arrivalTick;
    Flight* flight;

    HeapNode() {
        priority = 999;
        arrivalTick = 999999;
        flight = nullptr;
    }

    HeapNode(Flight* f) {
        flight = f;
        priority = f->priorityLevel;
        arrivalTick = f->arrivalTick;
    }

    // Two-field comparison: priority first, then earliest arrivalTick
    bool operator<(const HeapNode& other) const {
        if (priority != other.priority) {
            return priority < other.priority;
        }
        return arrivalTick < other.arrivalTick;
    }
};

// Custom Array-Based Min-Heap (1-indexed, no STL)
template <typename T>
class MinHeap {
private:
    T* arr;
    int capacity;
    int heapSize;

    int parent(int i) const { return i / 2; }
    int leftChild(int i) const { return 2 * i; }
    int rightChild(int i) const { return 2 * i + 1; }

    // Move element up to restore min-heap property
    void percolateUp(int i) {
        while (parent(i) >= 1 && arr[i] < arr[parent(i)]) {
            T temp = arr[i];
            arr[i] = arr[parent(i)];
            arr[parent(i)] = temp;
            i = parent(i);
        }
    }

    // Move element down to restore min-heap property
    void minHeapify(int i) {
        int left = leftChild(i);
        int right = rightChild(i);
        int smallest = i;

        if (left <= heapSize && arr[left] < arr[smallest]) {
            smallest = left;
        }
        if (right <= heapSize && arr[right] < arr[smallest]) {
            smallest = right;
        }

        if (smallest != i) {
            T temp = arr[i];
            arr[i] = arr[smallest];
            arr[smallest] = temp;
            minHeapify(smallest);
        }
    }

public:
    MinHeap(int cap = 100) {
        capacity = cap;
        heapSize = 0;
        arr = new T[capacity + 1];
    }

    ~MinHeap() {
        delete[] arr;
    }

    bool isEmpty() const {
        return (heapSize == 0);
    }

    int size() const {
        return heapSize;
    }

    // Insert new element into heap
    void insert(T val) {
        if (heapSize == capacity) {
            cout << "[Warning] Emergency Heap is full!" << endl;
            return;
        }
        heapSize++;
        arr[heapSize] = val;
        percolateUp(heapSize);
    }

    // Extract highest-priority (minimum) element
    T extractMin() {
        if (isEmpty()) {
            cout << "[Warning] Emergency Heap is empty!" << endl;
            return T();
        }
        T minVal = arr[1];
        arr[1] = arr[heapSize];
        heapSize--;
        if (heapSize > 0) {
            minHeapify(1);
        }
        return minVal;
    }

    // View minimum element without removing
    T peekMin() const {
        if (isEmpty()) {
            return T();
        }
        return arr[1];
    }

    // Display all heap elements
    void display() const {
        if (isEmpty()) {
            cout << "Emergency Dispatch Heap is empty." << endl;
            return;
        }
        cout << "--- Emergency Dispatch Heap ---" << endl;
        for (int i = 1; i <= heapSize; i++) {
            if (arr[i].flight != nullptr) {
                cout << i << ". Callsign: " << arr[i].flight->callsign
                    << " | Priority: " << arr[i].priority
                    << " | Arrival Tick: " << arr[i].arrivalTick
                    << " | Runway: " << arr[i].flight->assignedRunway << endl;
            }
        }
    }
};

#endif