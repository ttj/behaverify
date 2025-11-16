cmake_minimum_required(VERSION 3.10)
project(GridWorld)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find BehaviorTree.CPP
find_package(behaviortree_cpp REQUIRED)

# Add executable
add_executable(GridWorld
    main.cpp
    Environment.cpp
    at_key.cpp
    at_door.cpp
    at_target.cpp
    has_key_check.cpp
    door_unlocked_check.cpp
    need_move_to_key.cpp
    need_move_to_door.cpp
    need_move_to_target.cpp
    move_toward_key.cpp
    pick_up_key.cpp
    move_toward_door.cpp
    unlock_door.cpp
    move_toward_target.cpp
)

# Link libraries
target_link_libraries(GridWorld
    behaviortree_cpp
)

# Copy tree.xml to build directory
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/tree.xml ${CMAKE_CURRENT_BINARY_DIR}/tree.xml COPYONLY)
