#pragma once

#include <iostream>

namespace dsa::util {

// Helper function to print any number of arguments of any type with the
// possibility to define indentation.
template<int level = 1, int indent = 2, typename... T>
auto Print(T &&... t) {
  std::cout << std::string(indent * level, ' ');
  ((std::cout << t), ...);
}

auto Println() { std::cout << std::endl; }

template<int level = 1, int indent = 2, typename... T>
auto Println(T &&... t) {
  Print<level, indent>(t...);
  Println();
}

} // namespace dsa::util
