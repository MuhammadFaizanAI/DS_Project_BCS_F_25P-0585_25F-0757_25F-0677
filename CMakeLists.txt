# Minimum CMake version required
cmake_minimum_required(VERSION 3.20)

# Main project name and programming language 
project(MayDay404 LANGUAGES CXX)

# Use C++17 throughout the project
set(CMAKE_CXX_STANDARD 17)

# Required the selected C++ standard 
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#include the custome DSA library
add_subdirectory(dsa-library)

#include the main game application 
add_subdirectory(application)

