
#pragma once

#include "../data_structures/command_history_list.hpp"
#include "../data_structures/undo_stack.hpp"
#include "../models/flight.hpp"

class Registration;

class CommandHistory {
private:
    CommandHistoryList history;

    UndoStack undoStack;
    UndoStack redoStack;

    // Capture the current state of a flight
    FlightState captureState(const Flight* flight) const;

    // Restore a saved state
    void restoreState(Flight* flight,
                      const FlightState& state);

public:
    CommandHistory();

    // Record a CRO command
    void logCommand(const std::string& action,
                    const std::string& callsign);

    // Save the previous flight state
    void pushSnapshot(Flight* flight,
                      const FlightState& priorState);

    // Undo the latest status-changing command
    bool undo(Registration& registry);

    // Redo the latest undone command
    bool redo(Registration& registry);

    // Display recent commands
    void displayHistory(int count) const;

    // Display latest command
    void displayLastCommand() const;

    ~CommandHistory() = default;

    CommandHistory(const CommandHistory&) = delete;
    CommandHistory& operator=(const CommandHistory&) = delete;
};
