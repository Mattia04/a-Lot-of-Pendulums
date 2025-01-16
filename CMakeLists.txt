cmake_minimum_required(VERSION 3.30)
project(PendulumSimulator)

set(CMAKE_CXX_STANDARD 20)

include_directories(/opt/homebrew/Cellar/opencl-headers/2024.10.24/include)
include_directories(/opt/homebrew/Cellar/armadillo/14.2.2/include)
include_directories(./include)
include_directories(./source)
find_library(OpenCL_LIB OpenCL)
add_executable(PendulumSimulator main.cpp
        include/MyRK4.h
        include/MyDoublePendulum.h
        source/MyDoublePendulum.cpp
        include/MyFunctor.h
        include/MyODEIntegrator.h)
target_link_libraries(PendulumSimulator ${OpenCL_LIB})