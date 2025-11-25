# NEIGHBOR: This file tells CMake how to build our project.
#           CMake reads this and generates the actual build files for your compiler.
# NEWTON: Build system configuration using CMake meta-build system.

cmake_minimum_required(VERSION 3.15)

# Project name and version
project(Vanguard VERSION 0.0 LANGUAGES CXX)

# Use C++17 standard (we need this for std::clamp and other features)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Compiler optimization flags
# NEIGHBOR: In Release mode, add optimization flags to make code run faster.
#           In Debug mode, add debugging symbols so we can troubleshoot.
# NEWTON: Conditional compilation flags based on build configuration.
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    # Optimize for speed
    if(MSVC)
        add_compile_options(/O2)
    else()
        add_compile_options(-O3 -march=native)
    endif()
else()
    # Debug mode - add debugging info
    if(MSVC)
        add_compile_options(/Zi)
    else()
        add_compile_options(-g)
    endif()
endif()

# Warning flags (help catch bugs)
if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra)
endif()

# Create the executable
# NEIGHBOR: This builds our program called "gt7_sim" from main.cpp.
#           Vector3.h and Drone.h are automatically included when main.cpp uses them.
# NEWTON: Define build target with source dependencies.
add_executable(vanguard_sim src/main.cpp)

# Add include directory (for math/, physics/, control/, simulation/)
target_include_directories(vanguard_sim
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)

# Installation rule
install(TARGETS vanguard_sim DESTINATION bin)

# Print configuration info
message(STATUS "Vanguard-0 Configuration:")
message(STATUS "  Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "  Compiler: ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "  C++ Standard: C++${CMAKE_CXX_STANDARD}")