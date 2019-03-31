cmake_minimum_required(VERSION 3.0)

# Set compiler
find_program(g++-7 REQUIRED)
set(CMAKE_CXX_COMPILER g++-7)

# Find dependecies
find_package(Threads REQUIRED)

# Set variables
set(src_dir ${CMAKE_SOURCE_DIR}/src)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z -Wall")

# Build targets
file(GLOB_RECURSE cpp_files "${src_dir}/*.cpp")
foreach(cpp_file ${cpp_files})
    get_filename_component(exe_name ${cpp_file} NAME_WE)
    add_executable(${exe_name} ${cpp_file})
    target_link_libraries(${exe_name} Threads::Threads)
endforeach()
