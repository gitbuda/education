#include <algorithm>
#include <iostream>
#include <random>
#include <string>

/**
 * FROM:
 * https://stackoverflow.com/questions/440133/how-do-i-create-a-random-alpha-numeric-string-in-c
 *
 * @param len length of returned random string
 */
std::string random_string(std::string::size_type len) {
  static const auto &chars = "abcd";
  thread_local static std::mt19937 rg{std::random_device{}()};
  thread_local static std::uniform_int_distribution<std::string::size_type> ridx(
      0, sizeof(chars) - 2);
  std::string s;
  s.reserve(len);
  while (len--) { s += chars[ridx(rg)]; }
  return s;
}

int main() {
  std::string str = "Test test Test!";
  std::string part = "test";
  auto it = std::search(str.begin(), str.end(), part.begin(), part.end());
  std::cout << str << " " << part << std::endl;
  std::cout << it - str.begin() << std::endl;

  auto str_random = random_string(1000); // NOLINT
  auto part_random = random_string(4);
  it = std::search(str_random.begin(), str_random.end(), part_random.begin(), part_random.end());
  std::cout << str_random << " " << part_random << std::endl;
  std::cout << it - str_random.begin() << std::endl;

  // TODO(gitbuda): do the benchmark with std::boyer_moore_searcher

  return 0;
}
