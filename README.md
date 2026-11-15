# MayDay-404
### Air Traffic Control Simulation Game

## 1. Project Overview

MayDay-404 is a single-player, console-based Air Traffic Control (ATC) simulation game developed in C++.

The player takes the role of a **Chief Routing Officer (CRO)** responsible for managing the air traffic of BlackBox airline during an island-wide emergency in BitLand.

The airspace is facing multiple threats, including:

- Routine aircraft arrivals.
- Low-fuel and medical emergencies.
- Weather diversions and mechanical failures.
- Aircraft hijackings.
- Missing flights.
- Cyber attacks on air traffic communications.
- Hostile military aircraft entering restricted airspace.

The CRO must manage these situations by issuing commands, assigning runways, rerouting aircraft, handling emergencies, and maintaining airspace security.

The project focuses on implementing custom Data Structures and Algorithms and integrating them into one complete simulation. Every data structure must serve a practical purpose within the game.

## 2. Game Objectives

The main objective is to survive all 30 simulation ticks without a critical failure.

### Win Condition

The player wins by surviving all 30 ticks without:

- Aircraft crashes.
- Successful hijackings.
- Cyber breaches.
- War mission failures.

### Lose Conditions

The game ends when any of the following occurs:

- An aircraft crashes.
- A hijacking succeeds.
- A cyber breach occurs.
- A war emergency is not handled within its allowed time.
- Credibility reaches zero.
- The player exits the game through the game menu.

## 3. Project Modules

The project consists of 11 modules divided into four phases according to the Data Structures concepts.

### Phase 1: Linear Structures

This phase focuses on pointers, dynamic memory allocation, linked lists, stacks, queues, and file handling.

#### Module 1: Aircraft and Crew Registry

**Class:** `Registration`

Maintains all active aircraft and crew records.

Required data structures:

- Singly Linked List
- Hash Table with Linear Probing

Main operations:

- `addFlight()` — Insert a flight at the tail of the linked list.
- `removeFlight(callsign)` — Remove a flight from the list and hash table.
- `updateAllFlights()` — Traverse flights and decrement their fuel.
- `displayAllFlights()` — Display registered flights.
- `displayAllCrew()` — Display crew records.
- `addCrew()` — Add a crew record.
- `insert(callsign, flight*)` — Insert a flight into the hash table.
- `find(callsign)` — Find a flight by callsign.
- `remove(callsign)` — Remove a flight from the hash table.
- `displayStats()` — Display load factor, collision count, and longest probe chain.

The aircraft linked list is the primary owner of flight records. The hash table provides fast flight lookup by callsign.

**Input files:** `flights.txt`, `crew.txt`

#### Module 2: Landing & Emergency Dispatch

**Class:** `EmergencyLanding`

Manages normal arrivals and emergency landing requests.

Required data structures:

- Custom Queue
- Custom Min Heap

Main operations:

- `enqueueNormal(flight*)`
- `dequeueNormal()`
- `frontNormal()`
- `isEmptyNormal()`
- `displayNormalQueue()`
- `insertEmergency(flight*)`
- `extractMin()`
- `peekMin()`
- `isEmptyHeap()`
- `displayHeap()`

Normal arrivals are processed using FIFO order. Emergency arrivals are dispatched according to their priority.

When two emergency flights have the same priority, the flight with the earlier arrival tick must be dispatched first.

If the normal queue is not empty, the next landing is taken from the queue. Otherwise, the highest-priority emergency is extracted from the heap.

**Input file:** `scenario.txt`

#### Module 3: Command History & Undo

**Class:** `CommandHistory`

Maintains a history of commands issued by the CRO and supports undo and redo operations.

Required data structures:

- Doubly Linked List
- Stack

Undoable commands:

- Clear flight for runway.
- Reroute flight to alternate runway.
- Escalate priority level.
- Intercept hijack.
- Counter cyber alert.

Main operations:

- `logCommand(action, callsign)`
- `pushSnapshot(flight*, priorState)`
- `undo()`
- `redo()`
- `displayHistory(count)`
- `displayLastCommand()`

The command history is maintained in a doubly linked list. Snapshots store the previous state of affected flights, including runway, priority, sector, and status.

An undo operation restores the previous state. Redo reapplies an undone command.

---

### Phase 2: Searchable Structures

This phase focuses on Binary Search Trees and AVL Trees.

#### Module 4: Flight Manifest

**Class:** `BSTflight`

Maintains an ordered index of flights using a Binary Search Tree keyed by callsign.

Required data structure:

- Binary Search Tree (BST)

Main operations:

- `insert(flight*)`
- `search(callsign)`
- `inorderTraversal()`
- `height()`
- `destroyTree()`

The inorder traversal displays flights alphabetically by callsign.

#### Module 5: Balanced Flight Index

**Class:** `AVLflight`

Maintains a self-balancing flight index using an AVL Tree.

Required data structure:

- AVL Tree

Main operations:

- `insert()`
- `search()`
- `inorderTraversal()`
- `height()`
- `rotateLeft()`
- `rotateRight()`
- `rotateLeftRight()`
- `rotateRightLeft()`
- `destroyTree()`

The AVL Tree maintains balanced height through rotations.

**Required demonstration:** Insert at least 15 callsigns in alphabetical order into both the BST and AVL Tree, then compare their heights.

---

### Phase 3: Graphs & Algorithms

This phase focuses on graph representations, graph traversal, shortest paths, and minimum spanning trees.

#### Module 6: Airspace Network

**Class:** `SpaceGraph`

Represents the airspace as a weighted graph.

Required graph representations:

- Adjacency List
- Adjacency Matrix

Sectors represent vertices, while corridors represent weighted edges. Edge weights represent travel time in seconds.

Main operations:

- `addSector(name)`
- `addCorridor(from, to, weightSeconds)`
- `getWeight(from, to)`
- `displayAdjacencyList()`
- `displayAdjacencyMatrix()`
- `getSectorCount()`

Initial airspace sectors:

- Control Tower
- Air Segment (North)
- Cache Fly (East)
- Syntax Sector (West)
- Alpha Tree (South)
- Restricted Zone
- Holding Pattern Delta

Runways:

- Runway 12 (West) — Emergency-capable.
- Runway 04 (East) — High-traffic.
- Runway 17 (South).
- Runway 09 (North) — Emergency-capable, low-traffic.

The network must support the required connectivity conditions, including the Restricted Zone being reachable only through Alpha Tree.

**Input file:** `airspace.txt`

#### Module 7: Radar Sweep

**Class:** `RadarSweep`

Implements graph traversal to examine airspace connectivity and locate missing flights.

Required algorithms:

- Breadth-First Search (BFS)
- Depth-First Search (DFS)

Required data structures:

- Custom Queue for BFS.
- Custom Stack or recursion for DFS.

Main operations:

- `bfsFrom(sourceSector)`
- `dfsFrom(sourceSector)`
- `isReachable(from, to)`
- `searchMissingFlight(lastKnownSector)`

BFS examines sectors level by level. DFS explores sectors depth-first.

Missing-flight searches use the airspace graph to determine whether a missing aircraft can be located from its last known sector.

#### Module 8: Fastest Intercept Route

**Class:** `RouteFinder`

Calculates the fastest route from a source sector to a destination runway.

Required algorithm:

- Dijkstra's Algorithm

Required data structures:

- Weighted Graph
- Custom Min Heap
- Adjacency Matrix

Main operations:

- `findFastestRoute(sourceSector, destinationRunway)`
- `printRoute(route)`

The result must include the complete sector sequence and total travel time.

Parent-pointer tracing must be used to reconstruct the route.

#### Module 9: Minimum Radar Coverage

**Class:** `RadarMST`

Calculates the minimum-cost set of corridors needed to connect the airspace network.

Required algorithm:

- Minimum Spanning Tree (MST)

The implementation may use either:

- Kruskal's Algorithm with Union-Find and custom edge sorting.
- Prim's Algorithm with a custom Min Heap.

Main operations:

- `computeMST()`
- `displayMST()`
- `verifyConnectivity()`

The module must display the selected corridors and total cost and demonstrate that removing an MST edge disconnects the network.

---

### Phase 4: Integration

This phase combines all modules into one playable game.

#### Module 10: Game Loop & UI

**Class:** `GameEngine`

Integrates the modules and manages the complete simulation.

Main responsibilities:

- Display the main menu and game menu.
- Advance the simulation by ticks.
- Move aircraft toward assigned runways.
- Decrement fuel.
- Escalate emergencies.
- Spawn new flights according to the scenario.
- Handle missing flights.
- Process player commands.
- Display the current game state.
- Check win and lose conditions.

Each iteration represents one tick of 30 simulated seconds.

The player can issue up to two actions per turn. Viewing radar, manifests, and the airspace map does not consume an action.

#### Module 11: File Persistence

**Class:** `LeaderBoard`

Handles loading game data and saving game results.

Input files:

- `flights.txt`
- `crew.txt`
- `airspace.txt`
- `scenario.txt`
- `rules.txt`
- `about.txt`
- `gamemenu.txt`

Output file:

- `leaderboard.txt`

Main operations:

- `loadFlights(filename)`
- `loadCrew(filename)`
- `loadAirspace(filename)`
- `loadScenario(filename)`
- `saveResult(...)`
- `displayLeaderboard()`

The leaderboard stores previous game results and displays them according to the required ranking:

1. WIN entries rank above LOSE entries.
2. Higher credibility ranks higher.
3. More ticks used rank higher when result and credibility are equal.
4. More recent dates rank higher as the final tiebreaker.

## 4. Data Structures and Algorithms

The following table summarizes the required concepts and their applications in MayDay-404.

| Data Structure / Algorithm | Application |
|---|---|
| Singly Linked List | Aircraft registry |
| Doubly Linked List | Command history |
| Stack | Undo and redo |
| Queue | Normal landing sequence and BFS |
| Min Heap | Emergency dispatch and Dijkstra |
| Hash Table with Probing | Fast flight lookup by callsign |
| Binary Search Tree | Ordered flight manifest |
| AVL Tree | Balanced flight index |
| Graph | Airspace network |
| BFS | Radar sweep and missing-flight search |
| DFS | Sector traversal |
| Dijkstra's Algorithm | Fastest route to a runway |
| Minimum Spanning Tree | Minimum radar coverage |
| Union-Find | Kruskal's algorithm, if selected |

**Important:** Built-in STL templates, functions, and libraries are forbidden for the required data structures and algorithms. These must be implemented from scratch.

## 5. Game Mechanics

### Simulation Ticks

- Tick 0 represents the beginning of the game.
- Each turn advances the simulation by one tick.
- Each tick represents 30 simulated seconds.
- The game ends at Tick 30.
- All emergency timers are measured in ticks.

### Actions Per Turn

Each turn allows a maximum of two player actions.

Free actions:

- View radar.
- View manifest.
- View airspace map.
- View pending arrivals.

Action-consuming commands include:

- Register aircraft.
- Clear flight for runway.
- Reroute flight.
- Escalate priority.
- Undo.
- Search for missing flight.
- Intercept hijack.
- Counter cyber attack.
- Run BFS or DFS.
- Run Dijkstra.
- Run MST.

After two actions are used, the turn ends automatically. The player may also advance the tick using the End Turn option.

### Credibility

Starting credibility is 100. It can increase up to 200.

| Event | Credibility Change |
|---|---:|
| Flight lands safely | +2 |
| Hijack countered | +20 |
| Cyber alert countered | +15 |
| War aircraft intercepted or cleared | +30 |
| Missing flight located | +20 |
| Wrong command | -5 |
| Failed hijack counter | -20 |
| Failed cyber counter | -15 |
| Emergency landing on Runway 04 or 17 | -10 |
| Aircraft crash | -50 |

Reaching zero credibility results in game over.

### Emergency Priority

| Priority | Emergency | Escalation / Failure |
|---:|---|---|
| 1 | War | Mission failure after 2 ticks |
| 2 | Hijack | Mission failure after 3 ticks |
| 3 | Cyber Attack | Radar relay disabled |
| 4 | Missing Flight | Restricted Zone breach |
| 5 | Fuel | Crash after 5 ticks |
| 6 | Medical | Passenger casualty after 4 ticks |
| 7 | Weather | Forced crash after 4 ticks |
| 8 | Mechanical | Crash after 5 ticks |
| 9 | Normal | Routine arrival |

When emergencies have equal priority, earlier arrival time determines dispatch order.

### Cyber Attack

- The affected sector or corridor becomes degraded.
- If not countered within two ticks, one corridor is disabled.
- If not countered within three ticks, the Control Tower becomes degraded.
- When the tower is degraded, routing operations cost two actions instead of one.
- Wrong-move credibility penalties increase by an additional five points.

### War Event

- A hostile military aircraft from NullAir enters the airspace.
- The CRO has two ticks to clear or intercept it.
- If the aircraft is not handled within the allowed time, the mission fails.

### Missing Flight

- A missing aircraft disappears from the active flight registry.
- Its last known sector and tick window are recorded separately.
- The CRO must have the required credibility to attempt a search.
- BFS is used from the Control Tower to the last known sector.
- Successful location gives 20 credibility.
- Failure to locate the aircraft within its tick window results in a Restricted Zone breach.

## 6. Game Menus

### Main Menu

The main menu contains:

- New Game
- View Leaderboard
- About
- Rules
- Exit

### Game Menu

| Option | Command |
|---:|---|
| 01 | Register Aircraft |
| 02 | Register Crew Member |
| 03 | Search Flight by Call Sign |
| 04 | Add Normal Arrival |
| 05 | Add Emergency Arrival |
| 06 | Process Next Landing |
| 07 | Clear Flight for Runway |
| 08 | Reroute Flight |
| 09 | Intercept Aircraft |
| 10 | Escalate Priority |
| 11 | Counter Cyber Attack |
| 12 | Undo Last Command |
| 13 | Display Pending Arrivals |
| 14 | Display Crew Members |
| 15 | Display Flight Records |
| 16 | Display Airspace Network |
| 17 | BFS Radar Sweep |
| 18 | DFS Sector Traversal |
| 19 | Search for Missing Flight |
| 20 | Find Fastest Route to Runway |
| 21 | Generate Minimum Radar Coverage |
| 22 | Compare BST and AVL Heights |
| 23 | End Turn / Advance Tick |
| 24 | Exit to Main Menu |

## 7. Game World Entities

The simulation includes the following categories of entities:

- Aircraft types and their characteristics.
- Pilots and crew members.
- Runways and airspace sectors.
- Threat actors responsible for hijack and cyber events.
- Missing flights.
- Emergency categories.
- Aviation calls and terminology.

The project description provides sample aircraft, pilot profiles, threat actors, missing flights, airspace sectors, corridors, and emergency categories. These details are used to make the simulation realistic and meaningful.

## 8. Input and Output Files

### Input Files

| File | Purpose |
|---|---|
| `flights.txt` | Initial aircraft records |
| `crew.txt` | Crew and pilot records |
| `airspace.txt` | Airspace sectors and corridors |
| `scenario.txt` | Flight and emergency spawn schedule |
| `rules.txt` | Game rules, ticks, credibility, and win/lose conditions |
| `about.txt` | Game and development team information |
| `gamemenu.txt` | Game menu options |

### Output File

| File | Purpose |
|---|---|
| `leaderboard.txt` | Stores completed game results |

The leaderboard format is:

```text
#|CRO|Result|Cred|Ticks|Crash|Hijack|Breach|Date
```

## 9. Project Requirements

The completed project must demonstrate:

- Custom implementation of the required data structures.
- Dynamic memory allocation and pointer management.
- Integration of all 11 project modules.
- Correct application of searching, traversal, and graph algorithms.
- File handling for game input and output.
- A playable, menu-driven simulation.
- Handling of invalid input and invalid moves through console messages.
- Correct win and lose conditions.
- Persistent leaderboard across sessions.
- Proper documentation and demonstration of the project.

## 10. Build and Run

The project uses C++17 and CMake.

Configure the project:

```bash
cmake -S . -B build
```

Build:

```bash
cmake --build build
```

Run on Linux:

```bash
./build/MayDay404
```

On Windows, the executable location depends on the selected CMake generator and build configuration. For a Visual Studio Debug build:

```powershell
.\build\Debug\MayDay404.exe
```

## 11. Known Limitations

The implementation status and any deviations from the project requirements should be documented here as development progresses.

