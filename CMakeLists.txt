cmake_minimum_required(VERSION 3.30)
project(untitled)

set(CMAKE_CXX_STANDARD 20)

include_directories(/opt/homebrew/Cellar/opencl-headers/2024.10.24/include)
find_library(OpenCL_LIB OpenCL)
add_executable(PendulumSimulator main.cpp)
target_link_libraries(PendulumSimulator ${OpenCL_LIB})