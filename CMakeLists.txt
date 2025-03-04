cmake_minimum_required(VERSION 3.10)
project(raytracingInAWeekend)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 23)

# Enable optimizations in Release mode
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

# Add source files
add_executable(raytracingInAWeekend src/main.cpp)
