
#pragma once

#include <string>

// Previous or current state of a flight
struct FlightState {
    std::string assignedRunway;
    int priorityLevel;
    std::string currentSector;
    std::string status;

    FlightState()
        : priorityLevel(9) {}
};

// One node of the snapshot stack
struct Snapshot {
    std::string callsign;
    std::string action;
    FlightState state;

    Snapshot* next;

    Snapshot(const std::string& callsign,
             const std::string& action,
             const FlightState& state)
        : callsign(callsign),
          action(action),
          state(state),
          next(nullptr) {}

    Snapshot()
        : next(nullptr) {}
};

// Custom linked-list-based stack
class UndoStack {
private:
    Snapshot* top;
    int length;

public:
    UndoStack()
        : top(nullptr), length(0) {}

    // Push a snapshot onto the stack
    void push(const std::string& callsign,
              const std::string& action,
              const FlightState& state) {

        Snapshot* newNode =
            new Snapshot(callsign, action, state);

        newNode->next = top;
        top = newNode;

        length++;
    }

    // Remove the top snapshot
    bool pop(Snapshot& result) {
        if (top == nullptr)
            return false;

        Snapshot* temp = top;

        result.callsign = temp->callsign;
        result.action = temp->action;
        result.state = temp->state;

        top = top->next;

        delete temp;
        length--;

        return true;
    }

    bool isEmpty() const {
        return top == nullptr;
    }

    int getLength() const {
        return length;
    }

    // Remove all snapshots
    void clear() {
        while (top != nullptr) {
            Snapshot* temp = top;
            top = top->next;
            delete temp;
        }

        length = 0;
    }

    ~UndoStack() {
        clear();
    }

    // Prevent shallow copying
    UndoStack(const UndoStack&) = delete;
    UndoStack& operator=(const UndoStack&) = delete;
};
