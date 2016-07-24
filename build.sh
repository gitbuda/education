#!/bin/bash

# compile all c++ files and place executables in the build folder
for file_full_path in src/*.cpp; do
    file_full_name=$(basename $file_full_path)
    file_name="${file_full_name%.*}"
    extension="${file_full_name##*.}"
    clang++-3.8 -std=c++1z $file_full_path -o build/${file_name}.run
done
