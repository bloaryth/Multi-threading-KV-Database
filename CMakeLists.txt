cmake_minimum_required(VERSION 3.10)
project(System2018_Database)

set(CMAKE_CXX_STANDARD 17)

add_executable(System2018_Database src/main.cpp src/BpTree/bpt.h src/BpTree/bpt.cc src/BpTree/predefined.h src/BpTree/BpTree.hpp)
