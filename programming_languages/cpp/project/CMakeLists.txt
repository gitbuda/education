cmake_minimum_required(VERSION 3.15)

project(cpp_type_deduction CXX)
include(cmake/StandardProjectSettings.cmake)

# Link this 'library' to set the c++ standard / compile-time options requested.
add_library(project_options INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_20)

# Link this 'library' to use the warnings specified in CompilerWarnings.cmake.
add_library(project_warnings INTERFACE)

# Standard compiler warnings.
include(cmake/CompilerWarnings.cmake)
set_project_warnings(project_warnings)

# Sanitizer options if supported by compiler.
include(cmake/Sanitizers.cmake)
enable_sanitizers(project_options)

# Enable doxygen.
include(cmake/Doxygen.cmake)
enable_doxygen()

# Allow for static analysis options.
include(cmake/StaticAnalyzers.cmake)

option(BUILD_SHARED_LIBS "Enable compilation of shared libraries" OFF)
option(ENABLE_TESTING "Enable Test Builds" ON)

# Very basic PCH example.
option(ENABLE_PCH "Enable Precompiled Headers" OFF)
if (ENABLE_PCH)
  # This sets a global PCH parameter, each project will build its own PCH, which
  # is a good idea if any #define's change.
  target_precompile_headers(project_options INTERFACE <vector> <string> <map> <utility>)
endif()

# Set up some extra Conan dependencies based on our needs before loading Conan.
set(CONAN_EXTRA_REQUIRES "")
set(CONAN_EXTRA_OPTIONS "")
set(CONAN_EXTRA_REQUIRES ${CONAN_EXTRA_REQUIRES}
                         boost_type_index/1.69.0@bincrafters/stable)
include(cmake/Conan.cmake)
run_conan()

find_package(Threads REQUIRED)

if(ENABLE_TESTING)
  enable_testing()
  message(
    "Building Tests. Be sure to check out test/constexpr_tests for constexpr testing"
  )
  add_subdirectory(test)
endif()

if(ENABLE_FUZZING)
  message(
    "Building Fuzz Tests, using fuzzing sanitizer https://www.llvm.org/docs/LibFuzzer.html"
  )
  add_subdirectory(fuzz_test)
endif()

add_subdirectory(src)
