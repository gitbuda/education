#!/bin/bash

# TODO: CMake
# TODO: generate ycm based on CMake

# compile all c++ files and place executables into the build folder
for file_full_path in src/*.cpp; do
    file_full_name=$(basename $file_full_path)
    file_name="${file_full_name%.*}"
    # extension="${file_full_name##*.}"
    echo "TRY: ${file_name}"
    g++-7 -g -std=c++1z $file_full_path -o build/${file_name}.run
done
