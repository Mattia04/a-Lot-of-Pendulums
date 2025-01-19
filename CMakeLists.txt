cmake_minimum_required(VERSION 3.30)
project(PendulumSimulator)

set(CMAKE_CXX_STANDARD 20)

include_directories(/opt/homebrew/Cellar/opencl-headers/2024.10.24/include)
include_directories(/opt/homebrew/Cellar/armadillo/14.2.2/include)
include_directories(./include)

find_library(OpenCL_LIB OpenCL)

file(GLOB_RECURSE HEADER_FILES ./include/*.h)
file(GLOB_RECURSE SOURCE_FILES ./source/*.cpp)

add_executable(PendulumSimulator main.cpp ${HEADER_FILES} ${SOURCE_FILES})

target_link_libraries(PendulumSimulator ${OpenCL_LIB})