macro(run_conan)
# Download automatically, you can also just copy the conan.cmake file.
if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
  message(
    STATUS
      "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
  file(DOWNLOAD "https://github.com/conan-io/cmake-conan/raw/v0.15/conan.cmake"
       "${CMAKE_BINARY_DIR}/conan.cmake")
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)

conan_add_remote(NAME bincrafters URL
                 https://api.bintray.com/conan/bincrafters/public-conan)

set(CONAN_PROFILE "" CACHE STRING "Set Conan profile")
conan_cmake_run(
  PROFILE
  ${CONAN_PROFILE}
  REQUIRES
  ${CONAN_EXTRA_REQUIRES}
  catch2/2.11.0
  OPTIONS
  ${CONAN_EXTRA_OPTIONS}
  BASIC_SETUP
  CMAKE_TARGETS # Individual targets to link to.
  BUILD
  missing)
endmacro()
