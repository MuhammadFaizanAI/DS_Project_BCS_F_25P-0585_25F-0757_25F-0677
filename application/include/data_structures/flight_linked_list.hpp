
#pragma once

#include "../models/flight.hpp"
#include <iostream>
#include <string>

class FlightLinkedList {
private:
    Flight* head;
    Flight* tail;
    int length;

public:
    FlightLinkedList()
        : head(nullptr), tail(nullptr), length(0) {}

    // Insert flight at the end
    void insertAtTail(Flight* data) {
        if (data == nullptr)
            return;

        data->next = nullptr;

        if (head == nullptr) {
            head = data;
            tail = data;
        }
        else {
            tail->next = data;
            tail = data;
        }

        length++;
    }

    // Find flight by callsign
    Flight* findFlight(const std::string& callsign) {
        Flight* current = head;

        while (current != nullptr) {
            if (current->callsign == callsign)
                return current;

            current = current->next;
        }

        return nullptr;
    }

    // Remove flight by callsign
    Flight* removeFlight(const std::string& callsign) {
        Flight* current = head;
        Flight* previous = nullptr;

        while (current != nullptr) {
            if (current->callsign == callsign) {

                if (previous == nullptr)
                    head = current->next;
                else
                    previous->next = current->next;

                if (current == tail)
                    tail = previous;

                current->next = nullptr;
                length--;

                return current;
            }

            previous = current;
            current = current->next;
        }

        return nullptr;
    }

    // Update fuel for every flight
    void updateAllFlights() {
        Flight* current = head;

        while (current != nullptr) {
            if (current->fuelRemaining > 0)
                current->fuelRemaining--;

            current = current->next;
        }
    }

    // Display all flights
    void displayAllFlights() const {
        Flight* current = head;

        while (current != nullptr) {
            std::cout << "\nCallsign: " << current->callsign;
            std::cout << "\nAircraft: " << current->aircraftType;
            std::cout << "\nAirline: " << current->airline;
            std::cout << "\nFuel: " << current->fuelRemaining;
            std::cout << "\nPriority: " << current->priorityLevel;
            std::cout << "\n------------------------";

            current = current->next;
        }
    }

    int getLength() const {
        return length;
    }

    Flight* getHead() const {
        return head;
    }

    // Destructor
    ~FlightLinkedList() {
        Flight* current = head;

        while (current != nullptr) {
            Flight* nextNode = current->next;
            delete current;
            current = nextNode;
        }

        head = nullptr;
        tail = nullptr;
        length = 0;
    }
};
