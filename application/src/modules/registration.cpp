

#include "../../include/modules/registration.hpp"

bool Registration::addFlight(Flight* flight) {
    if (flight == nullptr)
        return false;

    // Prevent duplicate callsigns
    if (flightIndex.find(flight->callsign) != nullptr)
        return false;

    // Insert into hash table first
    if (!flightIndex.insert(flight->callsign, flight))
        return false;

    // Insert into linked list
    flights.insertAtTail(flight);

    return true;
}

bool Registration::removeFlight(const std::string& callsign) {
    // Find the flight
    Flight* flight = flightIndex.find(callsign);

    if (flight == nullptr)
        return false;

    // Remove its hash table entry
    flightIndex.remove(callsign);

    // Remove it from the linked list
    Flight* removed = flights.removeFlight(callsign);

    // Delete the dynamically allocated node
    delete removed;

    return true;
}

Flight* Registration::findFlight(const std::string& callsign) {
    return flightIndex.find(callsign);
}

void Registration::updateAllFlights() {
    flights.updateAllFlights();
}

void Registration::displayAllFlights() const {
    flights.displayAllFlights();
}

void Registration::addCrew(const Crew& crew) {
    crewMembers.push_back(crew);
}

void Registration::displayAllCrew() const {
    for (const Crew& crew : crewMembers) {
        std::cout << "\nEmployee ID: " << crew.employeeID;
        std::cout << "\nName: " << crew.name;
        std::cout << "\nRole: " << crew.role;
        std::cout << "\nAssigned Flight: "
                  << crew.assignedCallsign;
        std::cout << "\n------------------------";
    }
}

void Registration::displayHashStats() const {
    flightIndex.displayStats();
}
