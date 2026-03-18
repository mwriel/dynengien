cmake_minimum_required(VERSION 4.0)

project(MW70R)

if(EXISTS ${CMAKE_HOME_DIRECTORY}/CMAKE_PREFIX_LOCAL_PATHS.env)
    


    file(STRINGS ${CMAKE_HOME_DIRECTORY}/CMAKE_PREFIX_LOCAL_PATHS.env ENV_FILE)
    foreach(VAR ${ENV_FILE})
        string(REGEX MATCH "^[^=]*" KEY ${VAR})
        string(REGEX REPLACE "^[^=]*=" "" VALUE ${VAR})
        set(ENV{${KEY}} ${VALUE})
        message(STATUS env charged: ${KEY} = $ENV{${KEY}})
        list(APPEND CMAKE_PREFIX_PATH $ENV{${KEY}})
    endforeach()
endif()

#list(APPEND CMAKE_PREFIX_PATH $ENV{SDL_PREFIX})
find_package(SDL3 REQUIRED CONFIG)
# Después de find_package(SDL3...)
get_target_property(SDL3_DLL_PATH SDL3::SDL3 IMPORTED_LOCATION_RELEASE)
# O de forma más genérica para configuración Debug/Release:
set(SDL3_DLL_PATH $<TARGET_FILE:SDL3::SDL3>)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
include_directories(src)

add_subdirectory(src/ECS)
add_subdirectory(src/MPool)
add_subdirectory(src/test)