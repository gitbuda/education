# An RPG in C++20

Based on [An RPG in C++20](https://www.youtube.com/playlist?list=PLs3KjaCtOwSZ-74ryhrQQkqr8kZW50_mZ).

How to compile?
```
cmake \
    -DENABLE_SANITIZER_ADDRESS:BOOL=True \
    -DENABLE_SANITIZER_UNDEFINED_BEHAVIOR:BOOL=True \
    -DENABLE_CPPCHECK:BOOL=True \
    -DENABLE_CLANG_TIDY:BOOL=False \
    -DCONAN_PROFILE={profile_name} \
    ..
```
