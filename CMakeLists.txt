cmake_minimum_required(VERSION 3.0)

# set directory name as the project name
# get directory name
get_filename_component(ProjectId ${CMAKE_SOURCE_DIR} NAME)
# replace whitespaces with underscores
string(REPLACE " " "_" ProjectId ${ProjectId})
# set project name
project(${ProjectId})

# compiler options
set(COMPILE_OPTIONS "-O2 -Wall -Werror -fmessage-length=0")

# add all cpp file recursive into sourceFiles varibale
file(GLOB_RECURSE sourceFiles ${CMAKE_HOME_DIRECTORY}/src/*.cpp)

# print list of source files
message(STATUS "Source files are: ${sourceFiles}")

# set exe name
set(EXE_NAME ${ProjectId})

# add all source files into executable
add_executable(${EXE_NAME} ${sourceFiles})

