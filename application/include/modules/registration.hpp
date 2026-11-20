
#pragma once

#include "../models/crew.hpp"
#include "../models/flight.hpp"
#include "../data_structures/flight_linked_list.hpp"
#include "../data_structures/flight_hash_table.hpp"

#include <iostream>
#include <vector>
#include <string>

class Registration {
private:
    FlightLinkedList flights;
    FlightHashTable flightIndex;
    std::vector<Crew> crewMembers;

public:
    bool addFlight(Flight* flight);
    bool removeFlight(const std::string& callsign);

    Flight* findFlight(const std::string& callsign);

    void updateAllFlights();
    void displayAllFlights() const;

    void addCrew(const Crew& crew);
    void displayAllCrew() const;

    void displayHashStats() const;
};
