cmake_minimum_required(VERSION 3.29)
project(B_learning_Game)

set(CMAKE_CXX_STANDARD 20)

# Find SDL2 package
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# Add all source files
add_executable(B_learning_Game
        main.cpp
        xo_env.cpp    # Include the xo_env source file
        agent.cpp     # Include the agent source file
        utilities.cpp # Include utilities like calculate_average and save_multiple_vectors_to_file
)

# Link SDL2 with your target
target_link_libraries(B_learning_Game ${SDL2_LIBRARIES})
