cmake_minimum_required(VERSION 3.6)
project(DataBase)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp DataBase.h Error.h Logger/Logger.h FrontEnd/Parser.h Logger/Logger.cpp Tools.hpp ReorderBuffer.cpp ReorderBuffer.h FrontEnd/Instruction.hpp)
add_executable(DataBase ${SOURCE_FILES})