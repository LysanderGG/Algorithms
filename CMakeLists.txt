cmake_minimum_required(VERSION 3.6)
project (Algorithms)

add_subdirectory (Algorithms)
add_subdirectory (DataStructures)
add_subdirectory (UnitTests)

SET(CMAKE_DEFAULT_STARTUP_PROJECT UnitTests)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT UnitTests)