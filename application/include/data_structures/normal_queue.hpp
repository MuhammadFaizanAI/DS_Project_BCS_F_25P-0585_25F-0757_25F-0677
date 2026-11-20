#pragma once
#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <iostream>
using namespace std;

// Queue ke liye apna custom Node structure
template <typename T>
struct QueueNode {
    T data;
    QueueNode<T>* next;

    QueueNode(T val) {
        data = val;
        next = nullptr;
    }
};

// Custom FIFO Queue Class (Linked-List based, bina STL ke)
template <typename T>
class Queue {
private:
    QueueNode<T>* frontPtr; // Queue ka shuru (jahan se flight niklegi)
    QueueNode<T>* rearPtr;  // Queue ka aakhir (jahan nayi flight lagegi)
    int count;              // Total elements ginne ke liye

public:
    // Constructor: Khali queue initialize karna
    Queue() {
        frontPtr = nullptr;
        rearPtr = nullptr;
        count = 0;
    }

    // Destructor: Memory leaks se bachne ke liye saaray nodes delete karna
    ~Queue() {
        while (!isEmpty()) {
            dequeue();
        }
    }

    // Check karna ke queue khali hai ya nahi
    bool isEmpty() const {
        return (frontPtr == nullptr);
    }

    // Queue mein kitne elements hain
    int size() const {
        return count;
    }

    // Enqueue: Line ke aakhir (rear) mein naya element add karna
    void enqueue(T val) {
        QueueNode<T>* newNode = new QueueNode<T>(val);

        if (isEmpty()) {
            frontPtr = rearPtr = newNode;
        }
        else {
            rearPtr->next = newNode;
            rearPtr = newNode;
        }
        count++;
    }

    // Dequeue: Line ke shuru (front) se element nikalna aur return karna
    T dequeue() {
        if (isEmpty()) {
            cout << "[Warning] Normal Queue is empty! Cannot dequeue." << endl;
            return nullptr; // Pointer types ke liye safe return
        }

        QueueNode<T>* temp = frontPtr;
        T removedData = temp->data;

        frontPtr = frontPtr->next;
        if (frontPtr == nullptr) {
            rearPtr = nullptr; // Agar aakhri element bhi nikal gaya
        }

        delete temp; // Dynamic memory free karna
        count--;
        return removedData;
    }

    // Front: Line ke pehle element ko sirf dekhna (nikalna nahi)
    T front() const {
        if (isEmpty()) {
            return nullptr;
        }
        return frontPtr->data;
    }

    // Display: Queue mein maujood saaray items print karna (Flight* ke liye)
    void display() const {
        if (isEmpty()) {
            cout << "Normal Landing Queue is empty." << endl;
            return;
        }

        cout << "--- Normal Landing Queue (FIFO) ---" << endl;
        QueueNode<T>* current = frontPtr;
        int position = 1;
        while (current != nullptr) {
            cout << position << ". Callsign: " << current->data->callsign
                << " | Type: " << current->data->aircraftType
                << " | Runway: " << current->data->assignedRunway
                << " | Arrival Tick: " << current->data->arrivalTick << endl;
            current = current->next;
            position++;
        }
    }
};

#endif