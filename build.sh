#!/bin/bash

# compile all c++ files and place executables in the build folder
for file_full_path in src/*.cpp; do
    file_full_name=$(basename $file_full_path)
    file_name="${file_full_name%.*}"
    extension="${file_full_name##*.}"
    g++ -std=c++1y $file_full_path -o build/${file_name}.run
done
