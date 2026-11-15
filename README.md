# MayDay-404

## Team Members

| Name | Roll Number |
|---|---|
| Muhammad Faizan | 25P-0585 |
| Muhammad Soban | 25F-0757 |
| Hassan Muaviya | 25F-0677 |

## Project Structure

```text
DS_Project_BCS_F_25P-0585_25F-0757_25F-0677/
│
├── application/
│   ├── include/
│   │   ├── models/
│   │   ├── data_structures/
│   │   └── modules/
│   │
│   ├── src/
│   │   ├── modules/
│   │   └── main.cpp
│   │
│   └── data/
│
├── report/
├── CMakeLists.txt
├── README.md
└── LICENSE
```

## Build Instructions

Make sure CMake and a C++17-compatible compiler are installed.

Open a terminal in the project root directory (the directory containing `CMakeLists.txt`).

Configure the project:

```bash
cmake -S . -B build
```

Build the project:

```bash
cmake --build build
```

## Run Instructions

**Linux:**

```bash
./build/MayDay404
```

**Windows (Visual Studio Debug build):**

```powershell
.\build\Debug\MayDay404.exe
```

The executable location may vary depending on the selected CMake generator and build configuration.

## Known Limitations

- The project is under development.
- Only the functionality implemented so far is available.
- Modules and features that have not yet been implemented are not available.
- The complete simulation and integration of all project modules are not yet finished.
