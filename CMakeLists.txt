cmake_minimum_required(VERSION 3.30)
project(PendulumSimulator)

set(CMAKE_CXX_STANDARD 20)

# Find Armadillo
find_package(Armadillo REQUIRED)

# Set OpenMP paths
set(OPENMP_ROOT "/opt/homebrew/opt/libomp")

# Include directories
include_directories(
    ${ARMADILLO_INCLUDE_DIRS}
    ./include
    ${OPENMP_ROOT}/include
)

# Gather source files
file(GLOB_RECURSE HEADER_FILES ./include/*)
file(GLOB_RECURSE SOURCE_FILES ./source/*)

# Create executables
add_executable(PendulumSimulator static_fractal.cpp ${HEADER_FILES} ${SOURCE_FILES})
add_executable(Comparison tests/compare_integrators/compare_integrators.cpp
        ${HEADER_FILES} ${SOURCE_FILES})

# Configure OpenMP for Apple Clang
if(CMAKE_CXX_COMPILER_ID MATCHES "AppleClang")
    # Apply OpenMP settings to both targets
    foreach(target PendulumSimulator Comparison)
        target_compile_options(${target} PRIVATE
            -Xpreprocessor
            -fopenmp
            -I${OPENMP_ROOT}/include
        )
        target_link_directories(${target} PRIVATE ${OPENMP_ROOT}/lib)
        target_link_libraries(${target} PRIVATE omp)
    endforeach()
endif()

# Link Armadillo for both targets
foreach(target PendulumSimulator Comparison)
    target_link_libraries(${target} PRIVATE ${ARMADILLO_LIBRARIES})
endforeach()