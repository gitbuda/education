# Data Structures and Algorithms

A dumping ground for various data structures and algorithms. The goal here is
to play and learn.

Thank you [@lefticus](https://twitter.com/lefticus) for the project scaffold.

How to build and test?
```bash
mkdir -p build
cd build
cmake -DCMAKE_CXX_COMPILER={cxx_compiler_path} \
      -DENABLE_CLANG_TIDY=ON \
      -DENABLE_CPPCHECK=ON \
      -DCONAN_PROFILE={conan_profile_name} \
      ..
make -j
ctest
```
