# Cpp Type Deduction Experiments

## Function Template and Parameter Deduction

Generated by using Clang `10.0.0` and `-std=gnu++2a`.

|    Type     |  <T>f(T param)   |  <T>f(const T param)   |        <T>f(T& param)         |  <T>f(const T& param)   |        <T>f(T&& param)         | <T>f(const T&& param) |
|-------------|------------------|------------------------|-------------------------------|-------------------------|--------------------------------|-----------------------|
| int         | T=int; param=int | T=int; param=int const | T=int; param=int&             | T=int; param=int const& | T=int&; param=int&             | no known conversion   |
| const int   | T=int; param=int | T=int; param=int const | T=int const; param=int const& | T=int; param=int const& | T=int const&; param=int const& | no known conversion   |
| int&        | T=int; param=int | T=int; param=int const | T=int; param=int&             | T=int; param=int const& | T=int&; param=int&             | no known conversion   |
| const int&  | T=int; param=int | T=int; param=int const | T=int const; param=int const& | T=int; param=int const& | T=int const&; param=int const& | no known conversion   |
| int&&       | T=int; param=int | T=int; param=int const | T=int; param=int&             | T=int; param=int const& | T=int&; param=int&             | no known conversion   |
| const int&& | T=int; param=int | T=int; param=int const | T=int; param=int&             | T=int; param=int const& | T=int&; param=int&             | no known conversion   |