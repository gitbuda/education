cmake_minimum_required(VERSION 3.14)

set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)

project(fseek-binary-search)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()
message(STATUS "CMake build type: ${CMAKE_BUILD_TYPE}")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

add_executable(fbs fbs.cpp)
target_link_libraries(fbs stdc++fs)
target_compile_features(fbs PRIVATE cxx_std_17)

add_executable(rbs rbs.cpp)
target_link_libraries(rbs stdc++fs)
target_compile_features(rbs PRIVATE cxx_std_17)
