
#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class SpaceGraph
{
private:
    // One linked-list node represents one corridor.
    struct GraphNode
    {
        int destination;
        int weight;
        GraphNode *next;

        GraphNode(int dest, int cost)
        {
            destination = dest;
            weight = cost;
            next = nullptr;
        }
    };

    std::string *sectorNames;
    GraphNode **adjacencyHeads;
    int **adjacencyMatrix;

    int sectorCount;
    int capacity;

    // Finds the index of a sector using its name.
    int findSector(const std::string &name) const
    {

        for (int i = 0; i < sectorCount; i++)
        {
            if (sectorNames[i] == name)
            {
                return i;
            }
        }

        return -1;
    }

    // Doubles the storage capacity when necessary.
    void resizeStorage()
    {

        int newCapacity = capacity * 2;

        std::string *newNames = new std::string[newCapacity];

        GraphNode **newHeads = new GraphNode *[newCapacity];

        int **newMatrix = new int *[newCapacity];

        for (int i = 0; i < newCapacity; i++)
        {
            newHeads[i] = nullptr;
            newMatrix[i] = new int[newCapacity];

            for (int j = 0; j < newCapacity; j++)
            {
                newMatrix[i][j] = -1;
            }
        }

        // Copy existing sector names.
        for (int i = 0; i < sectorCount; i++)
        {
            newNames[i] = sectorNames[i];
            newHeads[i] = adjacencyHeads[i];

            for (int j = 0; j < sectorCount; j++)
            {
                newMatrix[i][j] = adjacencyMatrix[i][j];
            }
        }

        delete[] sectorNames;
        delete[] adjacencyHeads;

        for (int i = 0; i < capacity; i++)
        {
            delete[] adjacencyMatrix[i];
        }

        delete[] adjacencyMatrix;

        sectorNames = newNames;
        adjacencyHeads = newHeads;
        adjacencyMatrix = newMatrix;

        capacity = newCapacity;
    }

    // Finds a linked-list node for a particular destination.
    GraphNode *findNeighbor(int from, int to) const
    {

        GraphNode *current = adjacencyHeads[from];

        while (current != nullptr)
        {

            if (current->destination == to)
            {
                return current;
            }

            current = current->next;
        }

        return nullptr;
    }

    // Inserts a connection into one adjacency list.
    void insertEdge(int from, int to, int weight)
    {

        GraphNode *existing = findNeighbor(from, to);

        if (existing != nullptr)
        {
            existing->weight = weight;
            return;
        }

        GraphNode *newNode = new GraphNode(to, weight);

        newNode->next = adjacencyHeads[from];

        adjacencyHeads[from] = newNode;
    }

    // Releases all linked-list nodes.
    void clearAdjacencyLists()
    {

        for (int i = 0; i < sectorCount; i++)
        {

            GraphNode *current = adjacencyHeads[i];

            while (current != nullptr)
            {

                GraphNode *temp = current;

                current = current->next;

                delete temp;
            }

            adjacencyHeads[i] = nullptr;
        }
    }

public:
    // Constructor.
    SpaceGraph()
    {

        capacity = 5;
        sectorCount = 0;

        sectorNames = new std::string[capacity];

        adjacencyHeads = new GraphNode *[capacity];

        adjacencyMatrix = new int *[capacity];

        for (int i = 0; i < capacity; i++)
        {

            adjacencyHeads[i] = nullptr;

            adjacencyMatrix[i] = new int[capacity];

            for (int j = 0; j < capacity; j++)
            {
                adjacencyMatrix[i][j] = -1;
            }
        }
    }

    // Prevent accidental copying of dynamically allocated memory.
    SpaceGraph(const SpaceGraph &) = delete;
    SpaceGraph &operator=(const SpaceGraph &) = delete;

    // Destructor.
    ~SpaceGraph()
    {

        clearAdjacencyLists();

        delete[] sectorNames;
        delete[] adjacencyHeads;

        for (int i = 0; i < capacity; i++)
        {
            delete[] adjacencyMatrix[i];
        }

        delete[] adjacencyMatrix;
    }

    // Adds a new sector or runway and returns its index.
    int addSector(const std::string &name)
    {

        if (name.empty())
        {
            return -1;
        }

        int existingIndex = findSector(name);

        if (existingIndex != -1)
        {
            return existingIndex;
        }

        if (sectorCount == capacity)
        {
            resizeStorage();
        }

        int newIndex = sectorCount;

        sectorNames[newIndex] = name;

        adjacencyHeads[newIndex] = nullptr;

        adjacencyMatrix[newIndex][newIndex] = 0;

        sectorCount++;

        return newIndex;
    }

    // Adds a bidirectional weighted corridor.
    bool addCorridor(
        const std::string &from,
        const std::string &to,
        int weightSeconds)
    {

        if (weightSeconds <= 0)
        {
            return false;
        }

        int fromIndex = findSector(from);
        int toIndex = findSector(to);

        if (fromIndex == -1 || toIndex == -1)
        {
            return false;
        }

        if (fromIndex == toIndex)
        {
            return false;
        }

        // Update both adjacency lists.
        insertEdge(fromIndex, toIndex, weightSeconds);
        insertEdge(toIndex, fromIndex, weightSeconds);

        // Update both matrix positions.
        adjacencyMatrix[fromIndex][toIndex] = weightSeconds;
        adjacencyMatrix[toIndex][fromIndex] = weightSeconds;

        return true;
    }

    // Returns the weight between two sectors.
    // Returns -1 if either sector is missing or no corridor exists.
    int getWeight(
        const std::string &from,
        const std::string &to) const
    {

        int fromIndex = findSector(from);
        int toIndex = findSector(to);

        if (fromIndex == -1 || toIndex == -1)
        {
            return -1;
        }

        return adjacencyMatrix[fromIndex][toIndex];
    }

    // Returns weight using vertex indexes.
    int getWeight(int fromIndex, int toIndex) const
    {

        if (fromIndex < 0 || fromIndex >= sectorCount ||
            toIndex < 0 || toIndex >= sectorCount)
        {
            return -1;
        }

        return adjacencyMatrix[fromIndex][toIndex];
    }

    // Displays the adjacency list.
    void displayAdjacencyList() const
    {

        std::cout << "\n========== ADJACENCY LIST ==========\n";

        for (int i = 0; i < sectorCount; i++)
        {

            std::cout << sectorNames[i] << " -> ";

            GraphNode *current = adjacencyHeads[i];

            while (current != nullptr)
            {

                std::cout << sectorNames[current->destination]
                          << " (" << current->weight << ")";

                current = current->next;

                if (current != nullptr)
                {
                    std::cout << " -> ";
                }
            }

            std::cout << '\n';
        }
    }

    // Displays the adjacency matrix.
    void displayAdjacencyMatrix() const
    {

        std::cout << "\n========== ADJACENCY MATRIX ==========\n";

        std::cout << "\t";

        for (int i = 0; i < sectorCount; i++)
        {
            std::cout << i << "\t";
        }

        std::cout << '\n';

        for (int i = 0; i < sectorCount; i++)
        {

            std::cout << i << "\t";

            for (int j = 0; j < sectorCount; j++)
            {

                if (adjacencyMatrix[i][j] == -1)
                {
                    std::cout << "-\t";
                }
                else
                {
                    std::cout << adjacencyMatrix[i][j] << "\t";
                }
            }

            std::cout << "  " << sectorNames[i] << '\n';
        }
    }

    // Returns the number of vertices.
    int getSectorCount() const
    {
        return sectorCount;
    }

    // Returns a sector name using its index.
    std::string getSectorName(int index) const
    {

        if (index < 0 || index >= sectorCount)
        {
            return "";
        }

        return sectorNames[index];
    }

    // Loads sectors and corridors from airspace.txt.
    //
    // Format:
    // SECTOR|sector name
    // CORRIDOR|from|to|weight

    bool loadFromFile(const std::string &filename)
    {

        std::ifstream file(filename);

        if (!file.is_open())
        {
            std::cout << "Error: Cannot open " << filename << '\n';
            return false;
        }

        std::string line;

        // Skip the header.
        std::getline(file, line);

        int lineNumber = 1;

        while (std::getline(file, line))
        {

            lineNumber++;

            if (line.empty())
            {
                continue;
            }

            std::stringstream ss(line);

            std::string from;
            std::string to;
            std::string weightText;

            std::getline(ss, from, '|');
            std::getline(ss, to, '|');
            std::getline(ss, weightText);

            std::stringstream weightStream(weightText);

            int weight;
            char extra;

            if (from.empty() || to.empty() ||
                !(weightStream >> weight) ||
                (weightStream >> extra) ||
                weight <= 0)
            {

                std::cout << "Invalid data at line "
                          << lineNumber << '\n';

                file.close();
                return false;
            }

            // Automatically create vertices.
            addSector(from);
            addSector(to);

            // Add the corridor.
            if (!addCorridor(from, to, weight))
            {

                std::cout << "Could not add corridor at line "
                          << lineNumber << '\n';

                file.close();
                return false;
            }
        }

        file.close();

        std::cout << "Airspace loaded successfully.\n";

        return true;
    }
};
