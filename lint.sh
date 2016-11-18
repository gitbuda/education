#!/bin/bash

# TODO: integrate with CMake

clang-tidy src/main.cpp -- -std=c++1y -Iinclude/
