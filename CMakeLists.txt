cmake_minimum_required(VERSION 3.10)
project(System2018_Database)

set(CMAKE_CXX_STANDARD 17)

add_executable(System2018_Database SingleThread/main.cpp SingleThread/BpTree/bpt.h SingleThread/BpTree/bpt.cc SingleThread/BpTree/predefined.h SingleThread/BpTree/BpTree.hpp)
#add_executable(System2018_Database MultiThread/main.cpp MultiThread/BpTree/bpt.h MultiThread/BpTree/bpt.cc MultiThread/BpTree/predefined.h MultiThread/BpTree/BpTree.hpp)
