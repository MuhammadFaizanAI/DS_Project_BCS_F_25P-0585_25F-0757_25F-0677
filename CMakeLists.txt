cmake_minimum_required(VERSION 3.20)

project(MayDay404 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Automatically detect application source files
file(GLOB_RECURSE APP_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/application/src/*.cpp"
)

# Create the application executable
add_executable(MayDay404 ${APP_SOURCES})

# Include application headers
target_include_directories(MayDay404 PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/application/include"
)

# Copy data files beside the executable
add_custom_command(TARGET MayDay404 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_CURRENT_SOURCE_DIR}/application/data"
    "$<TARGET_FILE_DIR:MayDay404>/data"
)
