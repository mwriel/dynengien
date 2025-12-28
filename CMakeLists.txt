cmake_minimum_required(VERSION 3.10)

project(MW70R)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
include_directories(src)

add_subdirectory(src/ECS)
add_subdirectory(src/MPool)
add_subdirectory(src/test)