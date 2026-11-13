# MayDay-404
### Air Traffic Control Simulation System

## 1. Introduction

We are developing **MayDay-404**, a C++ console-based Air Traffic Control simulation game.

In this project, the player takes the role of a Chief Routing Officer responsible for managing aircraft, handling landing requests and emergencies, navigating airspace, and keeping the simulation running successfully.

The main objective of this project is to implement Data Structures and Algorithms from scratch and use them in a practical simulation rather than implementing them as separate, unrelated examples.

Our repository contains two main components:

1. **DSA Library:** Our own reusable implementations of data structures and algorithms.
2. **MayDay-404 Application:** The actual game that will use our custom DSA library.

---

## 2. Team Members

We are a team of three students working collaboratively on this project.

| Team Member | Roll Numbes |
|---|---|
| Muhammad Faizan | 25P-0585 |
| Muhammad Soban | 25F-XXXX |
| Hassan Muaviya | 25F-XXXX |

Each team member will contribute to the implementation, testing, integration, and development of the project.

---

## 3. Our Development Environment

We are three team members working on the same project and repository. However, we do not all use the same operating system or code editor.

| Development Environment | Tools |
|---|---|
| Windows | VS Code |
| Windows | Visual Studio |
| Arch Linux (Omarchy) | Neovim |

This difference does not affect our project because we are using **C++, CMake, and Git**.

CMake manages the project build process, allowing each team member to configure and compile the project using their own development environment.

### Technologies We Are Using

- **Language:** C++
- **C++ Standard:** C++17
- **Build System:** CMake
- **Version Control:** Git
- **Remote Repository:** GitHub
- **DSA Implementation:** Custom C++ templates

---

## 4. Project Architecture

We have organized the project into separate components so that our DSA implementations remain reusable and the actual game logic stays independent.

### A. DSA Library

Location: `dsa-library/`

This directory contains the data structures and algorithms that we will implement ourselves.

Our library is designed to be independent of the MayDay-404 game. It should not contain aircraft, crew, flight, or other game-specific logic.

The planned implementations include:

- Singly Linked List
- Doubly Linked List
- Stack
- Queue
- Min Heap
- Hash Table
- Binary Search Tree
- AVL Tree
- Graph
- BFS and DFS
- Dijkstra's Algorithm
- Kruskal's Algorithm
- Union-Find

**Important:** We are using C++ templates for reusable data structures. Therefore, template implementations will normally be written in `.hpp` header files. We do not need separate `.cpp` files for those template implementations.

### B. MayDay-404 Application

Location: `application/`

This is where we will develop the actual simulation game.

The application will use our custom DSA library to implement the different requirements of the project.

The planned responsibilities include:

- Managing aircraft and crew information.
- Handling landing requests and emergencies.
- Maintaining command history.
- Searching and organizing flight information.
- Managing the airspace network.
- Exploring the airspace using graph traversal.
- Finding routes between locations.
- Optimizing airspace connections.
- Managing game progression and simulation rules.
- Saving and retrieving player scores.

These are planned responsibilities. We have prepared the project structure, but the actual application functionality still needs to be implemented.

---

## 5. Complete Repository Structure

We have organized the repository into separate sections for our custom DSA library, the actual game application, testing, documentation, and the final project report.

The following is our planned complete repository structure:

```text
MayDay-404/
│
├── dsa-library/
│   ├── include/
│   │   └── dsa/
│   │       ├── singly_linked_list.hpp
│   │       ├── doubly_linked_list.hpp
│   │       ├── stack.hpp
│   │       ├── queue.hpp
│   │       ├── min_heap.hpp
│   │       ├── hash_table.hpp
│   │       ├── bst.hpp
│   │       ├── avl_tree.hpp
│   │       ├── graph.hpp
│   │       ├── dijkstra.hpp
│   │       ├── kruskal.hpp
│   │       └── union_find.hpp
│   │
│   ├── tests/
│   │   ├── test_linked_list.cpp
│   │   ├── test_doubly_linked_list.cpp
│   │   ├── test_stack.cpp
│   │   ├── test_queue.cpp
│   │   ├── test_heap.cpp
│   │   ├── test_hash_table.cpp
│   │   ├── test_bst.cpp
│   │   ├── test_avl.cpp
│   │   └── test_graph.cpp
│   │
│   └── CMakeLists.txt
│
├── application/
│   ├── include/
│   │   └── mayday/
│   │       ├── models/
│   │       │   ├── flight.hpp
│   │       │   ├── crew.hpp
│   │       │   └── command.hpp
│   │       │
│   │       ├── modules/
│   │       │   ├── registration.hpp
│   │       │   ├── emergency_dispatch.hpp
│   │       │   ├── command_history.hpp
│   │       │   ├── flight_index.hpp
│   │       │   ├── space_graph.hpp
│   │       │   ├── radar_sweep.hpp
│   │       │   ├── route_finder.hpp
│   │       │   └── radar_mst.hpp
│   │       │
│   │       ├── game/
│   │       │   └── game_engine.hpp
│   │       │
│   │       └── ui/
│   │           ├── menu.hpp
│   │           └── display.hpp
│   │
│   ├── src/
│   │   ├── models/
│   │   │   ├── flight.cpp
│   │   │   ├── crew.cpp
│   │   │   └── command.cpp
│   │   │
│   │   ├── modules/
│   │   │   ├── registration.cpp
│   │   │   ├── emergency_dispatch.cpp
│   │   │   ├── command_history.cpp
│   │   │   ├── flight_index.cpp
│   │   │   ├── space_graph.cpp
│   │   │   ├── radar_sweep.cpp
│   │   │   ├── route_finder.cpp
│   │   │   └── radar_mst.cpp
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
│   └── CMakeLists.txt
│
├── tests/
│   ├── test_registration.cpp
│   ├── test_emergency_dispatch.cpp
│   ├── test_command_history.cpp
│   ├── test_flight_index.cpp
│   ├── test_radar.cpp
│   ├── test_route_finder.cpp
│   └── test_game_engine.cpp
│
├── docs/
│   ├── architecture.md
│   ├── dsa-complexity.md
│   └── testing.md
│
├── report/
│   └── MayDay404_Final_Report.docx
│
├── CMakeLists.txt
├── README.md
└── .gitignore
```

### Understanding the Repository

| Directory / File | Responsibility |
|---|---|
| `dsa-library/` | Our independent, reusable custom DSA implementations. |
| `dsa-library/include/dsa/` | Template-based data structure and algorithm header files. |
| `dsa-library/tests/` | Tests for individual DSA implementations. |
| `application/include/` | Application class and module declarations. |
| `application/src/` | Actual game and module implementations. |
| `application/data/` | Text files containing game data and information. |
| `tests/` | Tests for application modules and game integration. |
| `docs/` | Technical documentation about architecture, complexity, and testing. |
| `report/` | Final university project report. |

### Important Notes

1. `.hpp` files in `dsa-library/` contain our template implementations. We do not need separate `.cpp` files for those templates.
2. Application `.hpp` files contain declarations, while their corresponding `.cpp` files contain implementations.
3. DSA tests and application tests have separate responsibilities.
4. The root `CMakeLists.txt` coordinates the complete project build.
5. This is our planned final structure. We will create implementation and test files as the corresponding work is developed; an empty placeholder file does not mean its functionality is complete.

---

## 6. Setting Up the Project

First, every team member must clone the same GitHub repository.

```bash
git clone https://github.com/MuhammadFaizanAI/DS_Project_BCS_F_25P-0585_25F-0757_25F-0677.git
cd MayDay-404
```


### A. Windows Setup

Our Windows team members can use either VS Code or Visual Studio.

**Required tools:**

- Git for Windows
- CMake
- A C++17-compatible compiler
- VS Code or Visual Studio

**For Visual Studio:**

1. Install Visual Studio with the Desktop development with C++ workload.
2. Open the cloned `MayDay-404` folder.
3. Allow Visual Studio to detect the root `CMakeLists.txt`.
4. Select the appropriate configuration.
5. Build and run the project through Visual Studio.

**For VS Code:**

1. Install VS Code.
2. Install the C/C++ extension.
3. Install the CMake Tools extension.
4. Open the `MayDay-404` folder.
5. Configure the project using CMake Tools.
6. Build and run the executable.

**Alternatively, build through PowerShell:**

```powershell
cmake -S . -B build
cmake --build build
```

### B. Arch Linux / Omarchy Setup

My development environment is Arch Linux (Omarchy), and I use Neovim.

Install the required packages:

```bash
sudo pacman -S git cmake gcc make
```

Clone the repository:

```bash
git clone YOUR_REPOSITORY_URL
cd MayDay-404
```

Configure and build:

```bash
cmake -S . -B build
cmake --build build
```

After the executable is successfully generated, run it from the build directory.

The exact executable path depends on our CMake configuration and build setup.

---

## 7. How We Will Work Together on GitHub

We are using **one shared GitHub repository and one `main` branch**.

We are keeping our collaboration workflow simple. We do not need feature branches or a complicated pull-request process for this project.

### Before starting work

Always update your local repository:

```bash
git pull origin main
```

### After completing your work

Add your changes:

```bash
git add .
```

Create a commit:

```bash
git commit -m "feat: implement linked list"
```

Push your changes:

```bash
git push origin main
```

### Important Collaboration Rules

1. Always pull the latest changes before starting your work.
2. Do not work on the same files simultaneously without coordinating.
3. Before pushing, make sure your local repository is updated.
4. Use meaningful commit messages.
5. Tell the other team members when you are making changes to shared files.
6. If Git reports a conflict, coordinate with the teammate involved and resolve it before pushing.

**Our goal:** Keep one updated project that all three of us can work on, regardless of the operating system or editor we use.

---

## 8. Understanding Our File Types

We will use different file types for different responsibilities.

| Extension | Purpose |
|---|---|
| `.hpp` | Header files, including our template-based DSA implementations. |
| `.cpp` | Source files containing application and non-template implementations. |
| `.txt` | Game data and other text-based files. |
| `.md` | Project documentation. |
| `CMakeLists.txt` | Build configuration. |

For example, our linked list implementation will be placed in:

```text
dsa-library/include/dsa/singly_linked_list.hpp
```

An application module will have its declaration and implementation separated:

```text
application/include/mayday/modules/
application/src/modules/
```

---

## 9. Testing

We have separated testing into two levels.

### A. DSA Library Tests

These will verify that our individual data structures and algorithms work correctly.

Examples:

- Linked list insertion and deletion.
- Stack push and pop.
- Queue enqueue and dequeue.
- BST searching and traversal.
- AVL balancing.
- Graph traversal and shortest paths.

### B. Application Tests

These will verify that our DSA implementations work correctly when used in the actual game.

Examples:

- Aircraft registration.
- Emergency dispatch.
- Command history.
- Flight searching.
- Route finding.
- Game progression.

We will add the actual test programs as we implement each component.

---

## 10. Current Development Status

This is where we currently stand.

### Completed / Prepared

- [x] GitHub repository created.
- [x] Main project directory structure prepared.
- [x] DSA library and application separated.
- [x] Header and source directory organization prepared.
- [x] Root CMake configuration prepared.
- [x] DSA library CMake configuration prepared.
- [x] Application CMake configuration prepared.
- [x] Development environments identified for all three members.

### Still To Do

- [ ] Implement custom data structures.
- [ ] Test individual DSA implementations.
- [ ] Implement application models and modules.
- [ ] Integrate the DSA library with the game.
- [ ] Implement the complete game engine.
- [ ] Test the complete simulation.
- [ ] Prepare the final report and project documentation.

**Important:** The current repository preparation is the foundation of our project. The actual DSA implementations and game functionality will be developed collaboratively from this point onward.

---

## 11. Final Note for Our Team

We are building one project together, not three separate implementations.

Our editors and operating systems may be different, but our code, project structure, build system, and GitHub repository are shared.

Before implementing a data structure or application module, we should agree on its interface and expected behavior. This will make integration easier and prevent our individual implementations from conflicting with one another.

Let's keep the code understandable, implement the required structures ourselves, test our work, and make sure every team member understands the complete project before the final demonstration.

**MayDay-404 — Built together, from scratch.**
