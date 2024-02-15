cmake_minimum_required(VERSION 3.12)

project(game_experiment)

add_subdirectory(raylib)
include_directories(raylib/src)

add_executable(game main.cpp ecs.cpp)

set_property(TARGET game PROPERTY CXX_STANDARD 20)

target_link_libraries(game raylib)
