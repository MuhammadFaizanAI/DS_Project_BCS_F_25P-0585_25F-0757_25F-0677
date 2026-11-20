

#pragma once

#include "../models/flight.hpp"
#include <iostream>
#include <string>

class FlightHashTable {
private:
    static const int TABLE_SIZE = 101;

    struct Entry {
        std::string key;
        Flight* flight;
        bool deleted;

        Entry() : flight(nullptr), deleted(false) {}
    };

    Entry table[TABLE_SIZE];

    int count;
    int collisionCount;
    int longestProbeChain;

    int hashFunction(const std::string& key) const {
        unsigned long hash = 0;

        for (char ch : key)
            hash = (hash * 31 + ch) % TABLE_SIZE;

        return static_cast<int>(hash);
    }

public:
    FlightHashTable()
        : count(0), collisionCount(0), longestProbeChain(0) {}

    bool insert(const std::string& callsign, Flight* flight) {
        if (flight == nullptr || count == TABLE_SIZE)
            return false;

        int index = hashFunction(callsign);
        int probes = 0;

        for (int i = 0; i < TABLE_SIZE; i++) {
            int position = (index + i) % TABLE_SIZE;
            Entry& entry = table[position];

            if (entry.flight != nullptr &&
                !entry.deleted &&
                entry.key == callsign) {
                return false;
            }

            if (entry.flight == nullptr || entry.deleted) {
                entry.key = callsign;
                entry.flight = flight;
                entry.deleted = false;

                count++;
                longestProbeChain =
                    (probes > longestProbeChain)
                    ? probes : longestProbeChain;

                return true;
            }

            probes++;
            collisionCount++;
        }

        return false;
    }

    Flight* find(const std::string& callsign) const {
        int index = hashFunction(callsign);

        for (int i = 0; i < TABLE_SIZE; i++) {
            int position = (index + i) % TABLE_SIZE;
            const Entry& entry = table[position];

            if (entry.flight == nullptr && !entry.deleted)
                return nullptr;

            if (!entry.deleted && entry.key == callsign)
                return entry.flight;
        }

        return nullptr;
    }

    bool remove(const std::string& callsign) {
        int index = hashFunction(callsign);

        for (int i = 0; i < TABLE_SIZE; i++) {
            int position = (index + i) % TABLE_SIZE;
            Entry& entry = table[position];

            if (entry.flight == nullptr && !entry.deleted)
                return false;

            if (!entry.deleted && entry.key == callsign) {
                entry.flight = nullptr;
                entry.deleted = true;
                count--;
                return true;
            }
        }

        return false;
    }

    void displayStats() const {
        std::cout << "\nHash Table Statistics";
        std::cout << "\nCapacity: " << TABLE_SIZE;
        std::cout << "\nEntries: " << count;
        std::cout << "\nLoad factor: "
                  << static_cast<double>(count) / TABLE_SIZE;
        std::cout << "\nCollisions: " << collisionCount;
        std::cout << "\nLongest probe chain: " << longestProbeChain;
        std::cout << '\n';
    }
};
