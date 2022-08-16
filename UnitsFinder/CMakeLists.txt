cmake_minimum_required(VERSION 3.5)

project(UnitsFinder LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(SOURCES csv.h IsSeeUnit.hpp)

add_executable(UnitsFinder main.cpp)

find_package(Threads REQUIRED)
target_link_libraries(UnitsFinder PRIVATE Threads::Threads)

