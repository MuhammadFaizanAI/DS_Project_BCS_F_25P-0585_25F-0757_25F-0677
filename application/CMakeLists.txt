# It will createthe MayDay404 executable file
add_executable(MayDay404
    # Main program entery point
    src/main.cpp 

    # ----- Members Editing Area ----- 
    # NOTE: You have to add the files location everytime 
    # u have a created a new file like below with their
    # respective folder 

    # Model implementations 
    # src/models/filename.cpp 

    # Modules implementations
    # src/modules/filename.cpp 
    src/modules/registration.cpp 

    # Game Engine 
    src/game/game_engine.cpp 

    # User Interface 
    src/ui/menu.cpp 
    src/ui/display.cpp
)

# Give the application access to its own headers 

target_include_directories(MayDay404
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Link the custom DSA Library to the application

target_include_libraries(MayDay404
    PRIVATE
    dsa-library
)

# Copy the data directories beside the executable after building 

add_custome_command(TARGET MayDay404 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directories
    ${CMAKE_CURRENT_SOURCE_DIR}/data 
    $<TARGET_FILE_DIR:MayDay404>/data
)
