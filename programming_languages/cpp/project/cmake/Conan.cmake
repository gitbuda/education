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
                 https://bincrafters.jfrog.io/artifactory/api/conan/public-conan)

# TODO: Enable revisions support on the client.
# `conan config _set general.revisions_enabled=1`

set(CONAN_PROFILE "default" CACHE STRING "Set conan profile")
conan_cmake_run(
  PROFILE
  ${CONAN_PROFILE}
  REQUIRES
  ${CONAN_EXTRA_REQUIRES}
  catch2/2.11.0
  docopt.cpp/0.6.2
  fmt/9.0.0
  spdlog/1.10.0
  OPTIONS
  ${CONAN_EXTRA_OPTIONS}
  BASIC_SETUP
  CMAKE_TARGETS # Individual targets to link to.
  BUILD
  missing)
endmacro()
