cmake_minimum_required(VERSION 3.1)

# set directory name as the project name
# get directory name
get_filename_component(ProjectId ${CMAKE_SOURCE_DIR} NAME)
# replace whitespaces with underscores
string(REPLACE " " "_" ProjectId ${ProjectId})
# set project name
project(${ProjectId})

# modules path
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake)

set(include_dir "${CMAKE_SOURCE_DIR}/include")
include_directories(${include_dir})
message(STATUS "Included directory is: ${include_dir}")

set(CMAKE_CXX_STANDARD 14)

# TESTING
include(gtest)
# include(gbenchmark)
enable_testing()
add_subdirectory(test)

find_package(Threads REQUIRED)

# third-party code
# compiler options
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -fmessage-length=0")

# add all cpp file recursive into sourceFiles varibale
file(GLOB_RECURSE sourceFiles ${CMAKE_SOURCE_DIR}/src/*.cpp)

# print list of source files
message(STATUS "Source files are: ${sourceFiles}")

# set exe name
set(EXE_NAME "enter")

# add all source files into executable
add_executable(${EXE_NAME} ${sourceFiles})
target_link_libraries(${EXE_NAME} Threads::Threads)
