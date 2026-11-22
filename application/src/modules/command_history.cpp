
#include "../../include/modules/command_history.hpp"
#include "../../include/modules/registration.hpp"

#include <iostream>

CommandHistory::CommandHistory() = default;


// Capture the current flight state
FlightState CommandHistory::captureState(
    const Flight* flight
) const {

    FlightState state;

    state.assignedRunway = flight->assignedRunway;
    state.priorityLevel = flight->priorityLevel;
    state.currentSector = flight->currentSector;
    state.status = flight->status;

    return state;
}


// Restore a saved flight state
void CommandHistory::restoreState(
    Flight* flight,
    const FlightState& state
) {

    flight->assignedRunway = state.assignedRunway;
    flight->priorityLevel = state.priorityLevel;
    flight->currentSector = state.currentSector;
    flight->status = state.status;
}


// Log a command in the doubly linked list
void CommandHistory::logCommand(
    const std::string& action,
    const std::string& callsign
) {

    history.append(action, callsign);
}


// Save the previous state before changing a flight
void CommandHistory::pushSnapshot(
    Flight* flight,
    const FlightState& priorState
) {

    if (flight == nullptr)
        return;

    std::string action = history.getLastAction();

    if (action.empty())
        action = "Flight command";

    // Save the previous state for undo
    undoStack.push(
        flight->callsign,
        action,
        priorState
    );

    // A new undoable command invalidates redo history
    redoStack.clear();
}


// Undo the latest status-changing command
bool CommandHistory::undo(Registration& registry) {

    Snapshot snapshot;

    // Check whether undo stack is empty
    if (!undoStack.pop(snapshot))
        return false;

    // Find the flight using its callsign
    Flight* flight = registry.findFlight(snapshot.callsign);

    if (flight == nullptr) {
        // Put snapshot back if flight does not exist
        undoStack.push(
            snapshot.callsign,
            snapshot.action,
            snapshot.state
        );

        return false;
    }

    // Save current state so it can be restored by redo
    FlightState currentState = captureState(flight);

    redoStack.push(
        snapshot.callsign,
        snapshot.action,
        currentState
    );

    // Restore the previous state
    restoreState(flight, snapshot.state);

    // Record undo operation
    history.append(
        "UNDO: " + snapshot.action,
        snapshot.callsign
    );

    return true;
}


// Redo the latest undone command
bool CommandHistory::redo(Registration& registry) {

    Snapshot snapshot;

    // Check whether redo stack is empty
    if (!redoStack.pop(snapshot))
        return false;

    // Find the flight
    Flight* flight = registry.findFlight(snapshot.callsign);

    if (flight == nullptr) {
        // Put snapshot back if flight does not exist
        redoStack.push(
            snapshot.callsign,
            snapshot.action,
            snapshot.state
        );

        return false;
    }

    // Save current state for future undo
    FlightState currentState = captureState(flight);

    undoStack.push(
        snapshot.callsign,
        snapshot.action,
        currentState
    );

    // Apply the saved state
    restoreState(flight, snapshot.state);

    // Record redo operation
    history.append(
        "REDO: " + snapshot.action,
        snapshot.callsign
    );

    return true;
}


// Display the last N commands
void CommandHistory::displayHistory(int count) const {

    if (count <= 0) {
        std::cout << "\nInvalid history count.\n";
        return;
    }

    history.displayLast(count);
}


// Display the most recent command
void CommandHistory::displayLastCommand() const {

    history.displayLastCommand();
}
