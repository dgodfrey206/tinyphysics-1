CMAKE_MINIMUM_REQUIRED(VERSION 2.8.12)
#set(CMAKE_INSTALL_PREFIX /usr/local)
PROJECT(tinyphysics)

ADD_EXECUTABLE(main src/cpp/main.cpp)

#===============================================================================
# TESTS
#===============================================================================

ADD_SUBDIRECTORY(tests EXCLUDE_FROM_ALL)

