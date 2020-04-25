#include <iomanip>
#include <iostream>

// custom struct
struct S {
  std::string first_name;
  std::string last_name;
  uint64_t age;
};

// std::hash<S> implementation
namespace std {
template<>
struct hash<S> {
  typedef S argument_type;
  using result_type = std::size_t;
  result_type operator()(argument_type const &s) const {
    result_type const h1(std::hash<std::string>()(s.first_name));
    result_type const h2(std::hash<std::string>()(s.last_name));
    result_type const h3(std::hash<uint64_t>()(s.age));
    return h1 ^ (h2 << 1) ^ (h3 << 2);
  }
};
} // namespace std

auto main() -> int {
  // string hash
  std::string str = "Hello hash!";
  std::size_t str_hash = std::hash<std::string>{}(str);
  std::cout << "hash(" << std::quoted(str) << ") = " << str_hash << std::endl;

  // custom object hash
  S o = {"Name", "Surname", 20}; // NOLINT
  std::size_t o_hash = std::hash<S>{}(o);
  std::cout << "hash(object) = " << o_hash << std::endl;

  return 0;
}
