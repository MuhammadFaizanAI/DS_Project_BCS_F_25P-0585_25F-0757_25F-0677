

#pragma once

#include <string>

struct Flight {
    // Flight information
    std::string callsign;
    std::string aircraftType;
    std::string airline;
    std::string origin;
    std::string destination;

    int passengerCount;
    int fuelRemaining;

    std::string currentSector;
    std::string assignedRunway;

    int arrivalTick;
    int priorityLevel;

    // Linked list connection
    Flight* next;

    Flight()
        : passengerCount(0),
          fuelRemaining(0),
          arrivalTick(0),
          priorityLevel(9),
          next(nullptr) {}
};

