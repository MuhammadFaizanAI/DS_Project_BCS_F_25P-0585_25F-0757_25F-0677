# **MayDay-404 — Complete Project Blueprint**

Team planning document · CL1004 Data Structures · Fall 2026

This document is based on your actual **CL1004-DS-Fall-26-Project.pdf**, not just the files currently visible in VS Code.

It covers all **4 phases and 11 modules**, their responsibilities, required data structures, operations, file relationships, text files, and how the three team members can integrate their work.

**Important:** Read this before creating more files. The assignment specifies the modules and their required functionality, but it does not mandate every C++ filename below. The proposed filenames are an organizational plan that fits your existing project.

**Project at a glance**

# **4**

Phases

# **11**

Modules

# **3**

Team members

# **30**

Simulation ticks

**Game:** MayDay-404

**Objective:** Build a console-based Air Traffic Control game using custom data structures and algorithms. Each module must work independently through a clear interface, then integrate into one playable game.

## **1. Project scenario — What are we building?**

You are developing an Air Traffic Control (ATC) simulation game.

The player acts as a CRO (Controller/Radar Operator in the game scenario) and manages aircraft, emergencies, airspace, threats, and runway assignments.

The player must:

- Monitor incoming aircraft.
- Manage normal and emergency landings.
- Handle hijacks, cyberattacks, missing flights, and other incidents.
- Reroute flights through available airspace corridors.
- Search sectors for missing flights.
- Protect airspace and radar coverage.
- Maintain credibility and prevent aircraft crashes.
- Win by surviving the simulation until the required final tick.

The project is not simply a collection of data structures. It is a complete game in which the structures and algorithms interact.

## **2. All four phases and eleven modules**

The assignment organizes the project into the following phases.&#x20;

CL1004-DS-Fall-26-Project.pdf



Phase 1

**Linear Structures**

Modules 1–3 · Pointers, DMA, linked lists, stacks, queues, hashing

- Module 1: Aircraft and Crew Registry
- Module 2: Landing & Emergency Dispatch
- Module 3: Command History & Undo

Phase 2

**Searchable Structures**

Modules 4–5 · Binary Search Trees and AVL Trees

- Module 4: Flight Manifest
- Module 5: Balanced Flight Index

Phase 3

**Graphs & Algorithms**

Modules 6–9 · Graphs, BFS, DFS, Dijkstra and MST

- Module 6: Airspace Network
- Module 7: Radar Sweep
- Module 8: Fastest Intercept Route
- Module 9: Minimum Radar Coverage

Phase 4

**Integration**

Modules 10–11 · Game loop, UI, file handling and persistence

- Module 10: Game Loop & UI
- Module 11: File Persistence

The assignment expects these modules to be implemented as the corresponding concepts are taught and integrated into a complete game by the end.&#x20;

CL1004-DS-Fall-26-Project.pdf



# **Phase 1 — Linear Structures**

## **3. Module 1: Aircraft and Crew Registry**

Phase 1 · Module 1

**Main class:** `Registration`

**Purpose:** Maintain all active aircraft and their crew records.

This module is the foundation of the entire project. Other modules need to access flight information through it.

### **Required data structures**

| Data structure                 | Purpose                          |
| ------------------------------ | -------------------------------- |
| Singly linked list             | Store active flights             |
| Hash table with linear probing | Find flights quickly by callsign |

### **Required files**

| Filename                 | Folder                     | Responsibility              |
| ------------------------ | -------------------------- | --------------------------- |
| `flight.hpp`             | `include/models/`          | Flight record               |
| `crew.hpp`               | `include/models/`          | Crew record                 |
| `flight_linked_list.hpp` | `include/data_structures/` | Custom singly linked list   |
| `flight_hash_table.hpp`  | `include/data_structures/` | Custom hash table           |
| `registration.hpp`       | `include/modules/`         | Registration interface      |
| `registration.cpp`       | `src/modules/`             | Registration implementation |
| `flights.txt`            | `data/`                    | Flight input records        |
| `crew.txt`               | `data/`                    | Crew input records          |

### **Flight record fields**

The assignment specifies:

| Field            | Type   | Meaning                 |
| ---------------- | ------ | ----------------------- |
| `callsign`       | string | Flight identifier       |
| `aircraftType`   | string | Aircraft model          |
| `airline`        | string | Airline name            |
| `origin`         | string | Origin airport          |
| `destination`    | string | Destination airport     |
| `passengerCount` | int    | Number of passengers    |
| `fuelRemaining`  | int    | Remaining fuel in ticks |
| `currentSector`  | string | Current airspace sector |
| `assignedRunway` | string | Assigned runway         |
| `arrivalTick`    | int    | Arrival tick            |
| `priorityLevel`  | int    | Emergency priority      |

Priority values:

| Priority | Emergency  |
| -------- | ---------- |
| 1        | War        |
| 2        | Hijack     |
| 3        | Cyber      |
| 4        | Missing    |
| 5        | Fuel       |
| 6        | Medical    |
| 7        | Weather    |
| 8        | Mechanical |
| 9        | Normal     |

The assignment's exact Flight and Crew fields are specified in Module 1.&#x20;

CL1004-DS-Fall-26-Project.pdf



### **Crew record fields**

- `employeeID`
- `name`
- `role`
- `assignedCallsign`

Roles: Pilot, Co-Pilot, Cabin Crew.

### **Required operations**

**Registration**

| Function                 | What it does                                      |
| ------------------------ | ------------------------------------------------- |
| `addFlight(flight*)`     | Insert a flight at the tail                       |
| `removeFlight(callsign)` | Remove it from the list and hash table            |
| `updateAllFlights()`     | Traverse all flights and decrement fuel each tick |
| `displayAllFlights()`    | Display all active flights                        |
| `displayAllCrew()`       | Display crew records                              |
| `addCrew(crew)`          | Append a crew record                              |

**Hash table**

| Function                    | What it does                   |
| --------------------------- | ------------------------------ |
| `insert(callsign, flight*)` | Insert a callsign and pointer  |
| `find(callsign)`            | Return `Flight*`, or `nullptr` |
| `remove(callsign)`          | Remove the callsign            |
| `displayStats()`            | Display hash statistics        |

Hash table requirements:

- Use a prime table size, such as 101.
- Use linear probing.
- Do not use chaining.
- Design your own hash function.
- Display load factor, collision count, and longest probe chain.
- Use tombstones or rehashing for deletion.

### **How the files connect**

```
registration.cpp
       |
       v
registration.hpp
       |
       +----------------------+
       |                      |
       v                      v
flight_linked_list.hpp   flight_hash_table.hpp
       |                      |
       +-----------+----------+
                   |
                   v
                flight.hpp

crew.hpp --------------------/
```

**Ownership rule:** The linked list owns dynamically allocated `Flight` nodes. The hash table stores non-owning pointers to those same nodes.

### **Input files**

- `flights.txt`: loaded into the flight linked list and hash table.
- `crew.txt`: loaded into the crew records.

### **Expected result**

After loading the files, the program should be able to display all flights and crew, find a flight by callsign, update fuel, and remove a flight consistently from both structures.

## **4. Module 2: Landing & Emergency Dispatch**

Phase 1 · Module 2

**Main class:** `EmergencyLanding`

**Purpose:** Manage normal arrivals and emergency arrivals and determine which flight should land next.

### **Required data structures**

| Data structure  | Purpose            |
| --------------- | ------------------ |
| Custom Queue    | Normal arrivals    |
| Custom Min-Heap | Emergency arrivals |

### **Required files**

| Filename                | Folder                     | Responsibility           |
| ----------------------- | -------------------------- | ------------------------ |
| `normal_queue.hpp`      | `include/data_structures/` | Custom FIFO queue        |
| `emergency_heap.hpp`    | `include/data_structures/` | Custom min-heap          |
| `emergency_landing.hpp` | `include/modules/`         | Class declaration        |
| `emergency_landing.cpp` | `src/modules/`             | Dispatch implementation  |
| `flight.hpp`            | `include/models/`          | Shared flight record     |
| `scenario.txt`          | `data/`                    | Flight spawning schedule |

### **Queue operations**

| Function                 | Purpose                             |
| ------------------------ | ----------------------------------- |
| `enqueueNormal(flight*)` | Add a normal flight                 |
| `dequeueNormal()`        | Remove and return the front flight  |
| `frontNormal()`          | Return front flight without removal |
| `isEmptyNormal()`        | Check whether queue is empty        |
| `displayNormalQueue()`   | Display normal arrivals             |

### **Heap operations**

| Function                   | Purpose                                   |
| -------------------------- | ----------------------------------------- |
| `insertEmergency(flight*)` | Insert emergency flight                   |
| `extractMin()`             | Remove and return highest-priority flight |
| `peekMin()`                | View the highest-priority flight          |
| `isEmptyHeap()`            | Check whether heap is empty               |
| `displayHeap()`            | Display emergency heap                    |

### **Important heap comparison**

The heap must compare two values:

1. `priorityLevel`
2. `arrivalTick`

The lower priority number wins. If two flights have the same priority, the earlier arrival wins.

Example:

| Flight | Priority | Arrival tick |
| ------ | -------- | ------------ |
| PK301  | 5        | 8            |
| PK402  | 2        | 10           |
| PK501  | 2        | 5            |

Dispatch order:

1. PK501
2. PK402
3. PK301

### **Landing decision**

The assignment specifies:

```
IF normal queue is not empty:
    dequeue from normal queue
ELSE:
    extract minimum from emergency heap
```

### **File linkage**

```
emergency_landing.cpp
        |
        v
emergency_landing.hpp
        |
        +------------------+
        |                  |
        v                  v
normal_queue.hpp     emergency_heap.hpp
        |                  |
        +---------+--------+
                  |
                  v
               flight.hpp
```

**Input file:** `scenario.txt` provides the spawn schedule. The Game Engine coordinates when scheduled flights enter the simulation.

### **Expected result**

The system must preserve FIFO order for normal flights and correct priority-plus-arrival order for emergency flights.

## **5. Module 3: Command History & Undo**

Phase 1 · Module 3

**Main class:** `CommandHistory`

**Purpose:** Record CRO commands and allow the most recent status-changing command to be undone.

The assignment explicitly adds redo as an additional requirement.

### **Required data structures**

| Data structure          | Purpose               |
| ----------------------- | --------------------- |
| Doubly linked list      | Store command history |
| Linked-list-based stack | Store undo snapshots  |
| Linked-list-based stack | Store redo snapshots  |

### **Required files**

| Filename                   | Folder                     | Responsibility             |
| -------------------------- | -------------------------- | -------------------------- |
| `command_history_list.hpp` | `include/data_structures/` | Doubly linked history list |
| `undo_stack.hpp`           | `include/data_structures/` | Snapshot and linked stack  |
| `command_history.hpp`      | `include/modules/`         | Module declaration         |
| `command_history.cpp`      | `src/modules/`             | Undo, redo and logging     |
| `flight.hpp`               | `include/models/`          | Flight state               |

### **Undoable commands**

- Clear flight for runway.
- Reroute flight to alternate runway.
- Escalate priority level.
- Intercept hijack.
- Counter cyber alert.

### **Snapshot fields**

Each snapshot stores:

| Field    | Purpose                    |
| -------- | -------------------------- |
| Callsign | Identifies affected flight |
| Runway   | Previous runway            |
| Priority | Previous priority          |
| Sector   | Previous sector            |
| Status   | Previous flight status     |

### **Required operations**

| Function                            | Purpose                                |
| ----------------------------------- | -------------------------------------- |
| `logCommand(action, callsign)`      | Append to doubly linked list           |
| `pushSnapshot(flight*, priorState)` | Save previous state                    |
| `undo()`                            | Restore previous state; false if empty |
| `displayHistory(count)`             | Display last commands in reverse order |
| `displayLastCommand()`              | Display latest command                 |
| `redo()`                            | Reapply an undone command              |

Undo costs one action according to the assignment.

### **File linkage**

```
command_history.cpp
        |
        v
command_history.hpp
        |
        +-------------------------+
        |                         |
        v                         v
command_history_list.hpp     undo_stack.hpp
        |                         |
        +------------+------------+
                     |
                     v
                  flight.hpp

command_history.cpp
        |
        v
registration.hpp
        |
        v
findFlight(callsign)
```

**Important:** Use callsigns in snapshots rather than storing raw pointers to flights that could later be deleted. Coordinate snapshot invalidation when a flight is removed.

### **Expected result**

A CRO should be able to execute a status-changing command, undo it, redo it, and inspect command history.

# **Phase 2 — Searchable Structures**

## **6. Module 4: Flight Manifest**

Phase 2 · Module 4

**Main class:** `BSTflight`

**Purpose:** Store flights in a Binary Search Tree ordered by callsign.

The hash table from Module 1 is excellent for direct lookup, but it does not provide efficient alphabetical traversal or ordered range queries. The BST provides those capabilities.

### **Required data structure**

- Binary Search Tree.
- Dynamically allocated tree nodes.
- Recursive operations.

### **Proposed files**

| Filename              | Folder                     | Responsibility                      |
| --------------------- | -------------------------- | ----------------------------------- |
| `bst_flight.hpp`      | `include/data_structures/` | BST implementation                  |
| `flight_manifest.hpp` | `include/modules/`         | Module interface, if separated      |
| `flight_manifest.cpp` | `src/modules/`             | Module implementation, if separated |
| `flight.hpp`          | `include/models/`          | Shared Flight record                |

The assignment names the class `BSTflight`. Keeping its implementation in one header is also a reasonable option.

### **Required operations**

| Function             | Purpose                          |
| -------------------- | -------------------------------- |
| `insert(flight*)`    | Insert a flight by callsign      |
| `search(callsign)`   | Return matching flight pointer   |
| `inorderTraversal()` | Display callsigns alphabetically |
| `height()`           | Return tree height               |
| `destroyTree()`      | Free dynamically allocated nodes |

### **Example**

Suppose flights are inserted in this order:

```
PK301
PK501
PK201
PK401
PK601
```

The BST orders them according to callsign comparison.

Inorder traversal produces:

```
PK201
PK301
PK401
PK501
PK601
```

### **File linkage**

```
flight_manifest.cpp
       |
       v
flight_manifest.hpp
       |
       v
bst_flight.hpp
       |
       v
flight.hpp
```

### **Expected result**

The program should display an alphabetically ordered flight manifest and support searching by callsign.

## **7. Module 5: Balanced Flight Index**

Phase 2 · Module 5

**Main class:** `AVLflight`

**Purpose:** Maintain a self-balancing flight index.

A normal BST can become unbalanced when callsigns are inserted in alphabetical order. An AVL tree maintains balance through rotations.

### **Required data structure**

- AVL Tree.
- Recursive insertion.
- Single and double rotations.
- Dynamically allocated tree nodes.

### **Proposed files**

| Filename           | Folder                     | Responsibility                      |
| ------------------ | -------------------------- | ----------------------------------- |
| `avl_flight.hpp`   | `include/data_structures/` | AVL implementation                  |
| `flight_index.hpp` | `include/modules/`         | Module interface, if separated      |
| `flight_index.cpp` | `src/modules/`             | Module implementation, if separated |
| `flight.hpp`       | `include/models/`          | Shared flight record                |

### **Required operations**

| Function             | Purpose                    |
| -------------------- | -------------------------- |
| `insert(flight*)`    | Insert with AVL balancing  |
| `search(callsign)`   | Search by callsign         |
| `inorderTraversal()` | Display alphabetical order |
| `height()`           | Return tree height         |
| `destroyTree()`      | Free nodes                 |
| `rotateLeft()`       | Left rotation              |
| `rotateRight()`      | Right rotation             |
| `rotateLeftRight()`  | Left-right rotation        |
| `rotateRightLeft()`  | Right-left rotation        |

Rotation functions are private helpers in the assignment.

### **Required demonstration**

The assignment specifically asks you to:

1. Insert at least 15 callsigns in alphabetical order into the BST.
2. Insert the same 15 callsigns into the AVL tree.
3. Show both heights side by side.

**Required comparison**

**BST**

May become skewed

**AVL**

Self-balancing

Record the actual heights produced by your implementation; do not assume fixed values.

### **File linkage**

```
flight_index.cpp
       |
       v
flight_index.hpp
       |
       v
avl_flight.hpp
       |
       v
flight.hpp
```

### **Relationship with Module 4**

Both trees index the same flight records, but they serve different purposes:

- BST demonstrates ordinary ordered tree behavior.
- AVL demonstrates predictable balanced search performance.

When a flight is added or removed, both indexes must be updated consistently.

# **Phase 3 — Graphs & Algorithms**

## **8. Module 6: Airspace Network**

Phase 3 · Module 6

**Main class:** `SpaceGraph`

**Purpose:** Represent the entire airspace as a weighted graph.

This is the spatial foundation for radar traversal, route finding, and radar coverage.

### **Required data structures**

The assignment requires two graph representations:

1. Adjacency list — used for graph traversal.
2. Adjacency matrix — used for constant-time edge-weight lookup in Dijkstra.

### **Proposed files**

| Filename               | Folder                     | Responsibility                            |
| ---------------------- | -------------------------- | ----------------------------------------- |
| `space_graph.hpp`      | `include/data_structures/` | Graph structures and operations           |
| `airspace_network.hpp` | `include/modules/`         | Module interface, if separated            |
| `airspace_network.cpp` | `src/modules/`             | Graph module implementation, if separated |
| `airspace.txt`         | `data/`                    | Sectors, corridors and weights            |

### **Graph concepts**

- Vertices represent airspace sectors.
- Edges represent corridors between sectors.
- Edge weights represent travel time in seconds.

### **Initial airspace sectors**

The assignment specifies:

1. Control Tower
2. Air Segment (North Sector)
3. Cache Fly (East Sector)
4. Syntax Sector (West Sector)
5. Alpha Tree (South Sector)
6. Restricted Zone

It also specifies four runways:

- Runway 12 — West, emergency.
- Runway 04 — East, high-traffic.
- Runway 17 — South.
- Runway 09 — North, low-traffic.

### **Required operations**

| Function                               | Purpose                                    |
| -------------------------------------- | ------------------------------------------ |
| `addSector(name)`                      | Add a vertex and return its index          |
| `addCorridor(from, to, weightSeconds)` | Add/update an edge in both representations |
| `getWeight(from, to)`                  | Return edge weight                         |
| `displayAdjacencyList()`               | Display linked adjacency list              |
| `displayAdjacencyMatrix()`             | Display matrix                             |
| `getSectorCount()`                     | Return vertex count                        |

### **Required network conditions**

The network must ensure:

- At least one path from every sector to at least one runway.
- At least one sector is reachable only through two or more hops.
- Weights vary enough to make shortest-path calculations meaningful.
- Restricted Zone is reachable only through Alpha Tree.

These are important test conditions, not merely suggestions.&#x20;

CL1004-DS-Fall-26-Project.pdf



### **File linkage**

```
airspace_network.cpp
        |
        v
airspace_network.hpp
        |
        v
space_graph.hpp
        |
        v
airspace.txt
```

### **Expected result**

The program should load the airspace and display its adjacency list and adjacency matrix.

## **9. Module 7: Radar Sweep**

Phase 3 · Module 7

**Main class:** `RadarSweep`

**Purpose:** Search and traverse the airspace graph using BFS and DFS.

This module uses the graph created in Module 6.

### **Required algorithms and structures**

| Algorithm | Required structure        | Purpose                  |
| --------- | ------------------------- | ------------------------ |
| BFS       | Custom queue              | Level-by-level traversal |
| DFS       | Custom stack or recursion | Depth-first traversal    |

The queue concept can be reused from Module 2, or a dedicated queue can be implemented. DFS can use a custom stack or explicit recursion.

### **Proposed files**

| Filename           | Folder                     | Responsibility               |
| ------------------ | -------------------------- | ---------------------------- |
| `radar_sweep.hpp`  | `include/modules/`         | RadarSweep declaration       |
| `radar_sweep.cpp`  | `src/modules/`             | BFS, DFS and search logic    |
| `space_graph.hpp`  | `include/data_structures/` | Graph interface              |
| `normal_queue.hpp` | `include/data_structures/` | Reusable queue               |
| `radar_stack.hpp`  | `include/data_structures/` | Optional dedicated DFS stack |

A dedicated `radar_stack.hpp` is optional because the assignment permits recursive DFS.

### **Required operations**

| Function                               | Purpose                                  |
| -------------------------------------- | ---------------------------------------- |
| `bfsFrom(sourceSector)`                | Print BFS order and return visited count |
| `dfsFrom(sourceSector)`                | Print DFS traversal order                |
| `isReachable(from, to)`                | Return whether a path exists             |
| `searchMissingFlight(lastKnownSector)` | Search for a missing flight              |

### **Required BFS tests**

- Print sectors level by level.
- Determine which sectors are within two hops of the Control Tower.

### **Required DFS tests**

- Print depth-first order from a source.
- Check whether Runway 27 is reachable from Alpha Tree.
- Check whether a path exists from the last known sector of a missing flight to Restricted Zone.

### **Missing-flight search**

When a flight is declared missing:

1. Record its last known sector.
2. The CRO can request a search.
3. Run BFS from the Control Tower to the last known sector.
4. If a path is found, locate the flight and mark it resolved.
5. If it is not found within its tick window, trigger a hijack-style alarm.

### **Important separate missing-flight storage**

The assignment specifically says missing flights are not stored in:

- Active flight registry.
- Flight hash table.
- BST.
- AVL.

They must live in their own list. This becomes especially important in Module 10.

Suggested supporting files:

| Filename                  | Folder                     | Responsibility               |
| ------------------------- | -------------------------- | ---------------------------- |
| `missing_flight.hpp`      | `include/models/`          | Missing-flight record        |
| `missing_flight_list.hpp` | `include/data_structures/` | Separate missing-flight list |

These are proposed supporting files for the required separate list.

### **File linkage**

```
radar_sweep.cpp
       |
       v
radar_sweep.hpp
       |
       +---------------------+
       |                     |
       v                     v
space_graph.hpp        normal_queue.hpp
       |
       v
missing_flight_list.hpp
       |
       v
missing_flight.hpp
```

### **Expected result**

The CRO can traverse sectors, check reachability, search for missing aircraft, and detect a Restricted Zone breach.

## **10. Module 8: Fastest Intercept Route**

Phase 3 · Module 8

**Main class:** `RouteFinder`

**Purpose:** Calculate the fastest route from a source sector to a destination runway.

### **Required algorithm**

**Dijkstra's shortest-path algorithm**, implemented from scratch.

### **Required data structures**

- Weighted graph from Module 6.
- Custom min-heap for shortest-distance selection.
- Adjacency matrix for edge-weight lookup.
- Parent pointers for route reconstruction.

### **Proposed files**

| Filename             | Folder                     | Responsibility                    |
| -------------------- | -------------------------- | --------------------------------- |
| `route_finder.hpp`   | `include/modules/`         | RouteFinder declaration           |
| `route_finder.cpp`   | `src/modules/`             | Dijkstra implementation           |
| `route.hpp`          | `include/models/`          | Route result structure, if needed |
| `space_graph.hpp`    | `include/data_structures/` | Weighted graph                    |
| `emergency_heap.hpp` | `include/data_structures/` | Reusable heap concept             |

The emergency heap from Module 2 has a different comparison rule. You may reuse the concept, but Dijkstra's heap must prioritize shortest distance, not emergency priority.

### **Required operations**

| Function                                            | Purpose                                     |
| --------------------------------------------------- | ------------------------------------------- |
| `findFastestRoute(sourceSector, destinationRunway)` | Calculate route                             |
| `printRoute(route)`                                 | Print sector sequence and total travel time |

A route contains:

- List of sectors.
- Total route cost.

### **Required demonstrations**

The assignment requires screenshots of:

1. Fastest route from Alpha Tree to Runway 12.
2. Fastest route from Restricted Zone, if reachable, to the nearest emergency runway.
3. Fastest route after a cyber alert disables a corridor.

**Parent-pointer tracing is required.** Showing only the final distance is not sufficient.&#x20;

CL1004-DS-Fall-26-Project.pdf



### **File linkage**

```
route_finder.cpp
       |
       v
route_finder.hpp
       |
       +--------------------+
       |                    |
       v                    v
space_graph.hpp       custom min-heap
       |
       v
route.hpp
```

### **Expected result**

The CRO can select a flight's current sector and assigned runway and receive the fastest available route with its complete sector sequence and travel time.

## **11. Module 9: Minimum Radar Coverage**

Phase 3 · Module 9

**Main class:** `RadarMST`

**Purpose:** Calculate the minimum-cost set of corridors required to connect the airspace for radar coverage.

### **Required algorithm**

Minimum Spanning Tree (MST).

The assignment allows either:

- Kruskal's algorithm.
- Prim's algorithm.

### **Proposed files**

| Filename          | Folder                     | Responsibility               |
| ----------------- | -------------------------- | ---------------------------- |
| `radar_mst.hpp`   | `include/modules/`         | RadarMST declaration         |
| `radar_mst.cpp`   | `src/modules/`             | MST implementation           |
| `union_find.hpp`  | `include/data_structures/` | Required if using Kruskal    |
| `edge_list.hpp`   | `include/data_structures/` | Optional custom edge storage |
| `space_graph.hpp` | `include/data_structures/` | Airspace graph               |

### **Required operations**

| Function               | Purpose                                          |
| ---------------------- | ------------------------------------------------ |
| `computeMST()`         | Compute minimum spanning tree                    |
| `displayMST()`         | Display selected corridors and total cost        |
| `verifyConnectivity()` | Verify connectivity and demonstrate edge removal |

### **Choose your implementation**

**Option A — Kruskal's algorithm**

Requires:

- Custom edge storage.
- Edge sorting implemented without `std::sort`.
- Custom Union-Find data structure.

**Option B — Prim's algorithm**

Requires:

- Custom min-heap.
- Graph traversal.
- Minimum edge selection.

### **Required demonstration**

1. Run MST on the full airspace network.
2. Display selected corridors.
3. Display total cost.
4. Demonstrate that removing any one MST edge disconnects the tree.

### **File linkage**

For Kruskal:

```
radar_mst.cpp
       |
       v
radar_mst.hpp
       |
       +-------------------+
       |                   |
       v                   v
space_graph.hpp       union_find.hpp
       |
       v
edge_list.hpp
```

For Prim, use the graph and a custom min-heap instead.

### **Expected result**

The game can display the minimum-cost radar coverage network and demonstrate its connectivity properties.

# **Phase 4 — Integration**

## **12. Module 10: Game Loop & UI**

Phase 4 · Module 10

**Main class:** `GameEngine`

**Purpose:** Connect all the modules and turn the project into a playable ATC game.

This is where the separate data structures become one complete application.

### **Proposed files**

| Filename          | Folder          | Responsibility                     |
| ----------------- | --------------- | ---------------------------------- |
| `game_engine.hpp` | `include/game/` | GameEngine declaration             |
| `game_engine.cpp` | `src/game/`     | Simulation and game logic          |
| `menu.hpp`        | `include/ui/`   | Menu declarations, if separated    |
| `menu.cpp`        | `src/ui/`       | User menu                          |
| `display.hpp`     | `include/ui/`   | Display declarations, if separated |
| `display.cpp`     | `src/ui/`       | Game display                       |
| `main.cpp`        | `src/`          | Program entry point                |

You already have `game_engine.cpp`, `menu.cpp`, `display.cpp`, and `main.cpp`. The header files are proposed additions if you want separate class declarations.

### **Modules used**

GameEngine coordinates:

1. Registration.
2. EmergencyLanding.
3. CommandHistory.
4. BSTflight.
5. AVLflight.
6. SpaceGraph.
7. RadarSweep.
8. RouteFinder.
9. RadarMST.
10. LeaderBoard.

### **Startup process**

When the game starts:

- Load `flights.txt`.
- Load `crew.txt`.
- Load `airspace.txt`.
- Load `scenario.txt`.
- Load `rules.txt`.
- Load `about.txt`.
- Load `gamemenu.txt`.
- Display the main menu.

### **Game tick**

The assignment specifies:

1 tick = 1 turn = 30 simulated seconds

The game ends at Tick 30 if no failure occurs.

Each iteration performs the following work:

**Step 1 — Automatic flight advance**

For every active flight:

- Check that the runway is adjacent to the current sector; otherwise, use hops.
- Move one step along its precomputed route toward its assigned runway.
- Decrement `fuelRemaining` by one.
- If fuel reaches zero, mark the flight crashed, log the event, decrement credibility, and check the lose condition.

**Step 2 — Automatic escalation**

| Emergency  | Failure condition                                                              |
| ---------- | ------------------------------------------------------------------------------ |
| War        | Not countered within 2 ticks                                                   |
| Hijack     | Not intercepted within 3 ticks                                                 |
| Cyber      | Not countered within 3 ticks: corridor disabled; after 4 ticks: tower disabled |
| Missing    | Not located within its tick window                                             |
| Fuel       | Not landed within 5 ticks                                                      |
| Medical    | Not landed within 4 ticks: passenger casualty and credibility loss             |
| Weather    | Not rerouted within 4 ticks                                                    |
| Mechanical | Not landed within 5 ticks                                                      |

**Step 3 — Automatic spawning**

- Every 3–5 ticks, a new flight appears according to `scenario.txt`.
- Register it in the flight linked list.
- Insert it into the hash table.
- Insert it into BST and AVL.
- Send it to the normal queue or emergency heap according to priority.

**Step 4 — Missing-flight handling**

Missing flights are stored in a separate list, not in the active registry, hash table, BST, or AVL.

Each missing-flight record stores:

- Flight name.
- Last known sector.
- Tick window.
- Credibility threshold.
- Spawn tick.

Missing flights do not consume fuel.

**Step 5 — Display current state**

Display:

- Radar.
- Flight count.
- Fuel warnings.
- Pending emergencies.
- Current credibility.

**Step 6 — Player actions**

The CRO can use up to two actions from the game menu per turn.

Viewing the radar, manifest, and airspace map is free and does not consume an action.

**Step 7 — Landing**

When a flight lands:

- Remove it from Registration.
- Remove it from the hash table.
- Remove it from BST.
- Remove it from AVL.
- Increase credibility by 2.

**Step 8 — Win/lose check**

- Win: Reach Tick 30 without failure.
- Lose: Crash, hijack, cyber breach, War failure, or credibility reaching zero.

At the end, display final credibility, tick count, flights landed, emergencies resolved, and failure cause if lost. Then return to the main menu.

These game-loop requirements are from the assignment's Module 10 description.&#x20;

CL1004-DS-Fall-26-Project.pdf



### **Required game menus**

The assignment references a main menu and game menu. The game menu should expose the specified game actions, including the missing-flight search. Do not invent additional game mechanics before checking the supplied `gamemenu.txt` and full menu specification.

### **File linkage**

```
main.cpp
    |
    v
GameEngine
    |
    +---- Registration
    |
    +---- EmergencyLanding
    |
    +---- CommandHistory
    |
    +---- BSTflight
    |
    +---- AVLflight
    |
    +---- SpaceGraph
    |
    +---- RadarSweep
    |
    +---- RouteFinder
    |
    +---- RadarMST
    |
    +---- LeaderBoard
    |
    +---- menu.cpp
    |
    +---- display.cpp
```

### **Expected result**

The user should be able to start a new game, play through 30 ticks, issue commands, inspect the airspace, handle emergencies, and see a win/lose result.

## **13. Module 11: File Persistence**

Phase 4 · Module 11

**Main class:** `LeaderBoard`

**Purpose:** Load initial game data and save the results of completed games.

### **Proposed files**

| Filename          | Folder             | Responsibility                        |
| ----------------- | ------------------ | ------------------------------------- |
| `leaderboard.hpp` | `include/modules/` | LeaderBoard declaration               |
| `leaderboard.cpp` | `src/modules/`     | File loading and result persistence   |
| `flights.txt`     | `data/`            | Initial flight data                   |
| `crew.txt`        | `data/`            | Initial crew data                     |
| `airspace.txt`    | `data/`            | Airspace network                      |
| `scenario.txt`    | `data/`            | Flight spawn schedule                 |
| `rules.txt`       | `data/`            | Game rules                            |
| `about.txt`       | `data/`            | Game and development team information |
| `gamemenu.txt`    | `data/`            | Game menu content                     |
| `leaderboard.txt` | `data/`            | Saved game results                    |

### **Input files**

The assignment says these files are read at startup:

| File           | Loaded information                                       |
| -------------- | -------------------------------------------------------- |
| `flights.txt`  | Flight records                                           |
| `crew.txt`     | Crew records                                             |
| `airspace.txt` | Graph sectors and corridors                              |
| `scenario.txt` | Flight spawn schedule                                    |
| `rules.txt`    | Maximum ticks, starting credibility, win/lose conditions |
| `about.txt`    | Game and development team information                    |
| `gamemenu.txt` | Game menu content                                        |

### **Output file**

`leaderboard.txt` stores game results.

It is appended to at the end of a game.

### **Required operations**

| Function                 | Purpose                        |
| ------------------------ | ------------------------------ |
| `loadFlights(filename)`  | Read flights into Registration |
| `loadCrew(filename)`     | Read crew records              |
| `loadAirspace(filename)` | Build the graph                |
| `loadScenario(filename)` | Read spawn schedule            |
| `saveResult(...)`        | Append a completed result      |
| `displayLeaderboard()`   | Read and print past results    |

The assignment specifies this leaderboard format:

```
#|CRO|Result|Cred|Ticks|Crash|Hijack|Breach|Date
```

The `saveResult` operation must record:

- Commander/CRO name.
- Win or lose result.
- Credibility.
- Ticks.
- Crashes.
- Hijacks.
- Breaches.

### **File linkage**

```
leaderboard.cpp
       |
       v
leaderboard.hpp
       |
       +----------------------+
       |                      |
       v                      v
Registration             SpaceGraph
       |                      |
       v                      v
flights.txt              airspace.txt

crew.txt --------------------> Registration
scenario.txt ----------------> GameEngine
rules.txt -------------------> GameEngine
about.txt -------------------> UI / GameEngine
gamemenu.txt ----------------> UI
leaderboard.txt -------------> LeaderBoard
```

**Important distinction:** Module 11 handles file persistence, but the game engine coordinates when data is loaded and when results are saved.

### **Expected result**

The game loads all required data at startup, runs the simulation, and appends completed results to the leaderboard.

# **14. Complete proposed project directory**

This is the recommended organization combining your existing files with the files needed for all eleven modules.

It is a planning structure, not a requirement to create every file immediately.

```
MayDay-404/
│
├── application/
│   │
│   ├── include/
│   │   │
│   │   ├── models/
│   │   │   ├── flight.hpp
│   │   │   ├── crew.hpp
│   │   │   ├── missing_flight.hpp
│   │   │   └── route.hpp
│   │   │
│   │   ├── data_structures/
│   │   │   ├── flight_linked_list.hpp
│   │   │   ├── flight_hash_table.hpp
│   │     ├── normal_queue.hpp
│   │   │   ├── emergency_heap.hpp
│   │   │   ├── command_history_list.hpp
│   │   │   ├── undo_stack.hpp
│   │   │   ├── bst_flight.hpp
│   │   │   ├── avl_flight.hpp
│   │   │   ├── space_graph.hpp
│   │   │   ├── missing_flight_list.hpp
│   │   │   ├── radar_stack.hpp
│   │   │   ├── union_find.hpp
│   │   │   └── edge_list.hpp
│   │   │
│   │   ├── modules/
│   │   │   ├── registration.hpp
│   │   │   ├── emergency_landing.hpp
│   │   │   ├── command_history.hpp
│   │   │   ├── flight_manifest.hpp
│   │   │   ├── flight_index.hpp
│   │   │   ├── airspace_network.hpp
│   │   │   ├── radar_sweep.hpp
│   │   │   ├── route_finder.hpp
│   │   │   ├── radar_mst.hpp
│   │   │   └── leaderboard.hpp
│   │   │
│   │   ├── game/
│   │   │   └── game_engine.hpp
│   │   │
│   │   └── ui/
│   │       ├── menu.hpp
│   │       └── display.hpp
│   │
│   ├── src/
│   │   │
│   │   ├── modules/
│   │   │   ├── registration.cpp
│   │   │   ├── emergency_landing.cpp
│   │   │   ├── command_history.cpp
│   │   │   ├── flight_manifest.cpp
│   │   │   ├── flight_index.cpp
│   │   │   ├── airspace_network.cpp
│   │   │   ├── radar_sweep.cpp
│   │   │   ├── route_finder.cpp
│   │   │   ├── radar_mst.cpp
│   │   │   └── leaderboard.cpp
│   │   │
│   │   ├── game/
│   │   │   └── game_engine.cpp
│   │   │
│   │   ├── ui/
│   │   │   ├── menu.cpp
│   │   │   └── display.cpp
│   │   │
│   │   └── main.cpp
│   │
│   ├── data/
│   │   ├── flights.txt
│   │   ├── crew.txt
│   │   ├── airspace.txt
│   │   ├── scenario.txt
│   │   ├── rules.txt
│   │   ├── about.txt
│   │   ├── gamemenu.txt
│   │   └── leaderboard.txt
│   │
│   └── tests/
│       ├── test_registration.cpp
│       ├── test_emergency_landing.cpp
│       ├── test_command_history.cpp
│       ├── test_bst.cpp
│       ├── test_avl.cpp
│       ├── test_graph.cpp
│       ├── test_radar_sweep.cpp
│       ├── test_route_finder.cpp
│       └── test_radar_mst.cpp
│
├── CMakeLists.txt
├── CMakePresets.json
├── README.md
├── LICENSE
└── .gitignore
```

### **Which files are essential and which are optional?**

| Category                                           | Status                                                         |
| -------------------------------------------------- | -------------------------------------------------------------- |
| Module classes and required data structures        | Required functionality                                         |
| Eight `.txt` data files                            | Required by the assignment                                     |
| `route.hpp`                                        | Suggested helper model                                         |
| `missing_flight.hpp` and `missing_flight_list.hpp` | Suggested implementation for the separate missing-flight list  |
| `union_find.hpp`                                   | Required if choosing Kruskal                                   |
| `edge_list.hpp`                                    | Suggested helper for Kruskal                                   |
| `radar_stack.hpp`                                  | Optional; DFS may use recursion                                |
| Separate module `.hpp` and `.cpp` pairs            | Organizational choice                                          |
| `tests/` files                                     | Recommended, not explicitly listed as a submission requirement |

**Do not create all these files just because they appear here.** Some structures can be implemented directly inside their module headers if that is clearer. Avoid creating duplicate classes or duplicate implementations.

## **15. All TXT files — Complete responsibility map**

There are eight data files in the assignment's Module 11 input/output requirements.&#x20;

CL1004-DS-Fall-26-Project.pdf



| File              | Type   | Primary module   | Purpose                               |
| ----------------- | ------ | ---------------- | ------------------------------------- |
| `flights.txt`     | Input  | Module 1         | Initial flight records                |
| `crew.txt`        | Input  | Module 1         | Crew and pilot records                |
| `airspace.txt`    | Input  | Module 6         | Sectors and corridors                 |
| `scenario.txt`    | Input  | Modules 2 and 10 | Scheduled events and flight spawning  |
| `rules.txt`       | Input  | Module 10        | Game rules and thresholds             |
| `about.txt`       | Input  | Module 10 / UI   | Game and development team information |
| `gamemenu.txt`    | Input  | Module 10 / UI   | Game menu content                     |
| `leaderboard.txt` | Output | Module 11        | Saved game results                    |

### **File lifecycle**

**When the program starts**

`flights.txt` · `crew.txt` · `airspace.txt` · `scenario.txt` · `rules.txt` · `about.txt` · `gamemenu.txt`

**Module 11 loads the data into the relevant modules**

**GameEngine runs the simulation**

**When a game finishes**

`leaderboard.txt` — append the new result

### **Very important: Use the supplied sample data**

The assignment's Appendix B says that a combined sample `.txt` file named for MayDay-404 is provided in the project folder. It contains the samples for the required text files. You may use the samples as-is or modify names, callsigns, and weights, but the required modules and game entities must remain present.&#x20;

CL1004-DS-Fall-26-Project.pdf



Therefore:

- Do not invent a new format for every file.
- First inspect the supplied combined sample text file.
- Extract the relevant sections into their individual `.txt` files.
- Keep the parser and file format consistent.
- Use the exact leaderboard format specified in Module 11.

The leaderboard header is:

```
#|CRO|Result|Cred|Ticks|Crash|Hijack|Breach|Date
```

## **16. How the eleven modules depend on each other**

This is the most important integration diagram for your team.

```
                         main.cpp
                            |
                            v
                         GameEngine
                            |
        +-------------------+--------------------+
        |                   |                    |
        v                   v                    v
   Registration      EmergencyLanding      CommandHistory
        |                   |                    |
        v                   v                    v
   Flight List           Queue + Heap       History List
   Hash Table                                  Undo/Redo
        |                   |                    |
        +-------------------+--------------------+
                            |
                            v
                     Flight Records
                            |
          +-----------------+-----------------+
          |                 |                 |
          v                 v                 v
       BSTflight         AVLflight         SpaceGraph
          |                 |                 |
          +-----------------+                 |
                            |                 |
                            |          +------+-------+
                            |          |      |       |
                            |          v      v       v
                            |       Radar  Route    Radar
                            |       Sweep  Finder   MST
                            |          |      |       |
                            +----------+------+-------+
                                       |
                                       v
                                  GameEngine
                                       |
                                       v
                                   LeaderBoard
```

### **Integration rules**

These rules will prevent many bugs:

1. **Registration owns active flight records.** Other modules should use `Flight*` references rather than independently owning copies.
2. **Hash table, BST and AVL are indexes.** When a flight is added or removed, keep all three synchronized.
3. **EmergencyLanding does not own flight records.** It manages pointers to flights.
4. **CommandHistory must locate flights through Registration.** Do not restore through an old pointer after a flight has been deleted.
5. **SpaceGraph is shared.** RadarSweep, RouteFinder and RadarMST must work with the same airspace network.
6. **GameEngine coordinates ticks and actions.** Do not let individual modules independently advance the simulation.
7. **LeaderBoard handles persistence.** It should not become a second owner of flight records.
8. **Missing flights have separate storage.** Do not insert them into the active flight indexes.

# **17. Game mechanics your team must not overlook**

The assignment includes rules outside the eleven module descriptions. These are important because your implementation must respect them.

## **Main menu**

The required main menu is:

```
======= MayDay-404 =======
======= MAIN MENU =======

[1] New Game
[2] View Leader Board
[3] About
[4] Rules
[5] Exit

==========================
```

## **Game menu**

The assignment provides this game menu in its specification:

```
======================= MayDay-404 ===============================

[01] Register Aircraft                [13] Display Pending Arrivals
[02] Register Crew Member             [14] Display Crew Members
[03] Search Flight by Call Sign       [15] Display Flight Records
[04] Add Normal Arrival               [16] Display Airspace Network
[05] Add Emergency Arrival            [17] BFS Radar Sweep
[06] Process Next Landing             [18] DFS Sector Traversal
[07] Clear Flight for Runway          [19] Search for Missing Flight
[08] Reroute Flight                   [20] Find Fastest Route to Runway
[09] Intercept Aircraft               [21] Generate Minimum Radar Coverage
[10] Escalate Priority                [22] Compare BST and AVL Heights
[11] Counter Cyber Attack             [23] End Turn/Advance Tick
[12] Undo Last Command                [24] Exit to Main Menu

=================================================================
```

The menu content is loaded from `gamemenu.txt`. The assignment also identifies options 4 and 5 as manual testing options, and options 7–11 as undoable commands.&#x20;

CL1004-DS-Fall-26-Project.pdf



## **Actions and credibility**

| Rule                 | Requirement                                                                   |
| -------------------- | ----------------------------------------------------------------------------- |
| Actions per turn     | 2                                                                             |
| Free actions         | View radar, manifest, airspace map, pending arrivals, crew and flight records |
| End turn             | Option 23                                                                     |
| Starting credibility | 100                                                                           |
| Maximum credibility  | 200                                                                           |
| Maximum ticks        | 30                                                                            |
| Win                  | Reach Tick 30 without a failure                                               |
| Lose                 | Crash, hijack, cyber breach, War failure, or credibility reaching zero        |

Credibility changes:

| Event                                | Change |
| ------------------------------------ | ------ |
| Flight lands safely                  | +2     |
| Hijack countered                     | +20    |
| Cyber alert countered                | +15    |
| War aircraft intercepted or cleared  | +30    |
| Missing flight located               | +20    |
| Wrong command                        | -5     |
| Failed hijack counter                | -20    |
| Failed cyber counter                 | -15    |
| Emergency landing on runway 04 or 17 | -10    |
| Crash                                | -50    |

The full game mechanics also include special rules for missing flights, cyberattacks, and War events. Implement them from the assignment's game mechanics section rather than making up alternative rules.&#x20;

CL1004-DS-Fall-26-Project.pdf



# **18. Technical rules and restrictions**

These are important for implementation and evaluation.

| Area            | Requirement                              |
| --------------- | ---------------------------------------- |
| Language        | C++                                      |
| Data structures | Implement from scratch                   |
| Memory          | Use dynamic memory where required        |
| Linked lists    | Custom implementations                   |
| Stack           | Custom linked stack                      |
| Queue           | Custom queue                             |
| Heap            | Custom min-heap                          |
| Hashing         | Custom linear probing                    |
| Trees           | Custom BST and AVL                       |
| Graphs          | Custom adjacency list and matrix         |
| BFS/DFS         | Implement from scratch                   |
| Dijkstra        | Implement from scratch                   |
| MST             | Implement Kruskal or Prim                |
| Edge sorting    | No `std::sort` if using Kruskal          |
| File handling   | Read and write the supplied `.txt` files |

The rubric explicitly emphasizes data structures implemented from scratch without STL containers. You can still use ordinary standard-library facilities such as `std::string` and file streams where appropriate; avoid replacing required custom structures with `std::vector`, `std::list`, `std::queue`, `std::priority_queue`, `std::map`, or similar containers.&#x20;

CL1004-DS-Fall-26-Project.pdf



Also remember:

- Every dynamically allocated structure needs proper cleanup.
- Define who owns each pointer.
- Avoid double deletion.
- Handle empty structures and missing records.
- Validate input from text files.
- Use clear error messages for invalid operations.

# **19. Testing plan for all modules**

Do not wait until Phase 4 to discover that an earlier data structure is broken.

Test each module independently first, then test its integration.

| Module                | Essential tests                                                                 |
| --------------------- | ------------------------------------------------------------------------------- |
| 1. Registration       | Insert, find, remove, duplicate callsign, fuel update, hash statistics          |
| 2. Emergency Dispatch | FIFO order, heap priority, equal-priority arrival tie-break                     |
| 3. Command History    | Log, undo, redo, empty stack, multiple operations                               |
| 4. Flight Manifest    | Insert, search, alphabetical traversal, height                                  |
| 5. Balanced Index     | All four rotation cases, alphabetical insertion, height comparison              |
| 6. Airspace Network   | Add sectors, add corridors, display both representations, required connectivity |
| 7. Radar Sweep        | BFS order, DFS order, reachability, missing-flight search                       |
| 8. Fastest Intercept  | Shortest route, unreachable destination, parent tracing, disabled corridor      |
| 9. Radar Coverage     | MST edges, total cost, connectivity, edge-removal demonstration                 |
| 10. Game Loop & UI    | Menus, two actions, tick advancement, spawning, emergencies, win/lose           |
| 11. File Persistence  | Load every input file, missing/corrupt files, append and display leaderboard    |

**Recommended testing order:**

```
Individual data structure tests
             |
             v
Individual module tests
             |
             v
Module-to-module integration
             |
             v
Full GameEngine tests
             |
             v
Complete game demonstration
```

# **20. Team collaboration and deliverables**

Your team has three members. The assignment requires one shared GitHub repository, individual GitHub accounts, and at least 4–5 meaningful commits from each member's own account.

Do not share one GitHub account. The repository README must contain the team members' names, build/run instructions, and known limitations.&#x20;

CL1004-DS-Fall-26-Project.pdf



### **Suggested division of work**

This is a suggested division, not an assignment-mandated allocation.

| Team member | Primary responsibility                      | Modules |
| ----------- | ------------------------------------------- | ------- |
| Member 1    | Linear structures and flight management     | 1, 2, 3 |
| Member 2    | Searchable structures and graph foundations | 4, 5, 6 |
| Member 3    | Graph algorithms and routing                | 7, 8, 9 |
| All three   | Integration, game loop, UI and persistence  | 10, 11  |

Module 10 and Module 11 require cooperation from everyone because they connect all the previous modules.

### **GitHub commit examples**

Use meaningful commits such as:

```
Implemented flight linked list
Added hash table with linear probing
Implemented emergency min heap
Added command history and undo
Implemented AVL rotations
Added airspace adjacency matrix
Implemented BFS and DFS
Added Dijkstra shortest path
Implemented Kruskal MST
Integrated GameEngine with all modules
Added leaderboard persistence
```

### **Final submission requirements**

The assignment expects:

1. Complete GitHub repository.
2. README with team names, build/run instructions and known limitations.
3. Microsoft Word project report using the supplied template.
4. GitHub repository link in the report.
5. Source code and output screenshots.
6. Screenshots showing the relevant `.txt` filenames and their contents.
7. Console output screenshots, including exception handling and win/lose conditions.
8. Individual contribution explanation: 7–10 lines per member.
9. Individual learning outcomes: 3–5 lines per member.
10. Three to five project limitations.
11. Viva presentation and live demonstration, with all team members present.

The report also has formatting requirements: Times New Roman, black text, justified alignment, 1.15 line spacing, page numbers, and specified heading sizes.&#x20;

CL1004-DS-Fall-26-Project.pdf



# **21. Recommended implementation roadmap**

Here is the order I recommend your team follow. It respects the assignment's four phases while reducing integration problems.

1. **Phase 1 — Build the foundation**
   - Finish Flight and Crew models.
   - Finish Registration and its two structures.
   - Finish normal queue and emergency heap.
   - Finish command history and undo/redo.
   - Test all three modules.
2. **Phase 2 — Build searchable indexes**
   - Implement BST.
   - Implement AVL.
   - Connect both to Registration.
   - Demonstrate BST versus AVL heights.
3. **Phase 3 — Build airspace intelligence**
   - Implement SpaceGraph.
   - Implement BFS and DFS.
   - Implement missing-flight search.
   - Implement Dijkstra.
   - Implement MST.
   - Test all graph conditions.
4. **Phase 4 — Build the playable game**
   - Implement LeaderBoard and file loading.
   - Integrate all modules in GameEngine.
   - Implement menus and displays.
   - Implement game rules, actions and ticks.
   - Test complete win and lose scenarios.
5. **Final submission**
   - Test the full game.
   - Prepare screenshots.
   - Complete README.
   - Complete the report.
   - Prepare each team member for the viva.

## **22. Before creating any new file — team agreement checklist**

I recommend that all three of you agree on these points first:

- We understand all four phases and eleven modules.
- We agree on the responsibilities of each module.
- We agree on the shared `Flight` structure.
- We agree that Registration owns the active flight records.
- We agree that other modules use `Flight*` rather than owning duplicate flight objects.
- We agree on the interface names and function signatures.
- We agree on the text-file formats using the supplied sample data.
- We agree on the folder and filename conventions.
- We agree on how GameEngine coordinates actions and ticks.
- We agree on how all three team members will integrate their code.

**My strongest recommendation:** Before writing more code, agree on the shared interfaces for `Flight`, `Registration`, `EmergencyLanding`, `SpaceGraph`, and `GameEngine`. These are the connections on which most of the project depends. A well-defined interface now will save you from rewriting several modules later.

*Source document: CL1004-DS-Fall-26-Project.pdf, particularly Sections 4–8 and Appendices B–C.*