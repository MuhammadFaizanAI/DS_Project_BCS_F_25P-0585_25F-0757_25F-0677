
#pragma once

#include <iostream>
#include <string>

struct HistoryNode {
    std::string action;
    std::string callsign;

    HistoryNode* prev;
    HistoryNode* next;

    HistoryNode(const std::string& action,
                const std::string& callsign)
        : action(action),
          callsign(callsign),
          prev(nullptr),
          next(nullptr) {}
};

class CommandHistoryList {
private:
    HistoryNode* head;
    HistoryNode* tail;
    int length;

public:
    CommandHistoryList()
        : head(nullptr), tail(nullptr), length(0) {}

    // Insert a command at the tail
    void append(const std::string& action,
                const std::string& callsign) {

        HistoryNode* newNode =
            new HistoryNode(action, callsign);

        if (head == nullptr) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }

        length++;
    }

    // Get the latest command's action
    std::string getLastAction() const {
        if (tail == nullptr)
            return "";

        return tail->action;
    }

    // Display the last N commands in reverse order
    void displayLast(int count) const {
        HistoryNode* current = tail;
        int displayed = 0;

        if (current == nullptr) {
            std::cout << "\nNo command history available.\n";
            return;
        }

        std::cout << "\n========== COMMAND HISTORY ==========\n";

        while (current != nullptr && displayed < count) {
            std::cout << displayed + 1 << ". "
                      << current->action
                      << " | Flight: "
                      << current->callsign << '\n';

            current = current->prev;
            displayed++;
        }

        std::cout << "=====================================\n";
    }

    // Display the most recent command
    void displayLastCommand() const {
        if (tail == nullptr) {
            std::cout << "\nNo commands have been executed.\n";
            return;
        }

        std::cout << "\nLast Command: "
                  << tail->action
                  << " | Flight: "
                  << tail->callsign << '\n';
    }

    bool isEmpty() const {
        return head == nullptr;
    }

    int getLength() const {
        return length;
    }

    // Release all dynamically allocated nodes
    ~CommandHistoryList() {
        HistoryNode* current = head;

        while (current != nullptr) {
            HistoryNode* temp = current;
            current = current->next;
            delete temp;
        }

        head = nullptr;
        tail = nullptr;
        length = 0;
    }

    // Prevent shallow copying
    CommandHistoryList(const CommandHistoryList&) = delete;
    CommandHistoryList& operator=(const CommandHistoryList&) = delete;
};
