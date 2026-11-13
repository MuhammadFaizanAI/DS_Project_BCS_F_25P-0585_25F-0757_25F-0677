# Add the header-only DSA library target: It tells CMake that this
# library provides usage requirements (such as include directories)
# rather than a compiled library binary
add_library(dsa-library INTERFACE)

# Tell other targets where the DSA headers are located 
target_include_directories(dsa-library
    INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/inlcude
)
