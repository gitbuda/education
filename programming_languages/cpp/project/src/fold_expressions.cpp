#include <iostream>

using std::cout;
using std::endl;

template<typename... T>
auto sum_old(T... t) {
  typename std::common_type<T...>::type result{};
  (void)std::initializer_list<int>{(result += t, 0)...};
  return result;
}

template<typename... T>
auto sum(T... t) {
  return (t + ...);
}

template<typename... T>
auto div(T... t) {
  return (... / t);
}

template<typename... T>
auto avg(T... t) {
  return (t + ...) / sizeof...(t);
}

template<typename... T>
auto print(T &&... t) {
  (cout << ... << (std::string(t) + " ")) << endl;
}

template<typename... T>
auto all_true(T... t) {
  return ((t == true) && ...);
}

auto main() -> int {
  cout << "C++11/14 sum: " << sum_old(1.0, 2, 3, 4, 5.0) << endl; // NOLINT

  cout << "C++17 fold sum: " << sum(1.0, 2.0, 3, 4, 5) << endl; // NOLINT

  cout << "C++17 fold div: " << div(1.0, 2.0, 3.0) << endl; // NOLINT

  cout << "C++17 fold avg: " << avg(1.0, 2.0, 3.0) << endl; // NOLINT

  print("This", "is", "a", "test!"); // NOLINT

  bool is_true = 2 == 10; // NOLINT
  cout << "All true: " << all_true(true, true, is_true) << endl; // NOLINT

  return 0;
}
