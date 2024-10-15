cmake_minimum_required(VERSION 3.29)
project(B_learning_Game)

set(CMAKE_CXX_STANDARD 20)

# Find SDL2 package
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(B_learning_Game main.cpp)

# Link SDL2 with your target
target_link_libraries(B_learning_Game ${SDL2_LIBRARIES})
