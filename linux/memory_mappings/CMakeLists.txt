cmake_minimum_required(VERSION 3.15)

set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)

project(memory_mappings)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

set(PROJECT_WARNINGS
    "-Wall -Wextra -Wpedantic -Wunused -Wold-style-cast -Werror")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${PROJECT_WARNINGS}")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2")

add_executable(p1 p1.cpp)
target_compile_features(p1 PRIVATE cxx_std_20)

add_executable(p2 p2.cpp)
target_compile_features(p2 PRIVATE cxx_std_20)
