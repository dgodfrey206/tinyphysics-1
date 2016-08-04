#===============================================================================
# Header
#===============================================================================

CMAKE_MINIMUM_REQUIRED(VERSION 2.8.12)
#set(CMAKE_INSTALL_PREFIX /usr/local)
PROJECT(tinyphysics)

#===============================================================================
# Compiler flags
#===============================================================================

#Use C++11
SET(CMAKE_CXX_FLAGS  "-std=c++11" )
#Set debug flags
#These debug flags are used when invoking CMake this way:
#cmake -DCMAKE_BUILD_TYPE=Debug
SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")

#===============================================================================
# Libraries
#===============================================================================

INCLUDE_DIRECTORIES(src/cpp)

FILE(
    GLOB_RECURSE
    geometry_files
    src/cpp/tinyphysics/geometry/*
    )

ADD_LIBRARY(tinyphysics-geometry ${geometry_files})

FILE(
    GLOB_RECURSE
    sfml_files
    src/cpp/tinyphysics/sfml/*
    )

ADD_LIBRARY(tinyphysics-sfml ${sfml_files})

#===============================================================================
# Main program
#===============================================================================

ADD_EXECUTABLE(main src/cpp/main.cpp)
ADD_DEPENDENCIES(main tinyphysics-sfml tinyphysics-geometry)
TARGET_LINK_LIBRARIES(main tinyphysics-sfml tinyphysics-geometry sfml-graphics sfml-window sfml-system)

#===============================================================================
# Tests
#===============================================================================

ADD_SUBDIRECTORY(tests EXCLUDE_FROM_ALL)

