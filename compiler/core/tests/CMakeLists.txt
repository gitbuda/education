cmake_minimum_required(VERSION 3.1)

project(compiler_tests)

# find tests
file(GLOB_RECURSE test_files ${CMAKE_HOME_DIRECTORY}/tests/*.cpp)
set(tests "")
foreach(test_file ${test_files})
    get_filename_component(test_name ${test_file} NAME_WE)
    list(APPEND tests ${test_name})
endforeach()

message(STATUS "Available tests are: ${tests}")

# build tests
foreach(test ${tests})
    add_executable(${test} ${test}.cpp)
    add_test(NAME ${test} COMMAND ${test})
    set_property(TARGET ${test} PROPERTY CXX_STANDARD 14)
endforeach()
