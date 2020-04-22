// C++ Reference std::variant
//
// https://en.cppreference.com/w/cpp/utility/variant
#include <iomanip>
#include <iostream>
#include <memory>
#include <string>
#include <variant>
#include <vector>

// Helper function to print any number of arguments of any type with the
// possibility to define indentation.
template<int level = 1, int indent = 2, typename... T>
auto print(T &&... t) {
  std::cout << std::string(indent * level, ' ');
  ((std::cout << t), ...);
}
auto println() { std::cout << std::endl; }
template<int level = 1, int indent = 2, typename... T>
auto println(T &&... t) {
  print<level, indent>(t...);
  println();
}

struct Struct {
  Struct() { println("Struct default constructor called."); }
  Struct([[maybe_unused]] const Struct &other) { println("Struct copy constructor called."); }
  Struct([[maybe_unused]] Struct &&other) noexcept { println("Struct move constructor called."); }
  Struct &operator=([[maybe_unused]] const Struct &other) {
    println("Struct copy assignment called.");
    return *this;
  }
  Struct &operator=([[maybe_unused]] Struct &&other) noexcept {
    println("Struct move assignment called.");
    return *this;
  }
  ~Struct() {}
  operator int() { return 2000; }
};
// Required to test variadic initialization with an error.
struct ErrorStruct {
  operator int() { throw 1; }
};

// Helper visitor construct explained in depth here
// https://dev.to/tmr232/that-overloaded-trick-overloading-lambdas-in-c17.
template<class... Ts>
struct overloaded : Ts... {
  using Ts::operator()...;
};
template<class... Ts>
overloaded(Ts...) -> overloaded<Ts...>;

int main() {
  // Basic usage example.
  println<0>("Basic std::variant example.");

  std::variant<int, float> basic{10};
  println("Get by int type: ", std::get<int>(basic));
  println("Get by 0 index: ", std::get<0>(basic));
  println("Index: ", basic.index());

  basic = 10.5F;
  println("Get by float type: ", std::get<float>(basic));
  println("Get by 1 index: ", std::get<1>(basic));
  println("Index: ", basic.index());

  try {
    std::get<0>(basic);
  } catch (std::bad_variant_access &) { println("Bad variant access"); }
  println();

  // Visit example.
  println<0>("Visit example");
  std::variant<int, float, std::string> visitable{1.2f};
  std::visit([](auto &&arg) { println(arg); }, visitable);
  println();

  // Get pointer example.
  println<0>("Get pointer example");
  std::variant<int, float> ptr_example;
  ptr_example = 1.F;
  if (auto *ptr = std::get_if<float>(&ptr_example)) {
    println("Variant value based on pointer: ", *ptr);
  } else {
    println("Failed to get value");
  }
  println();

  // Valueless example.
  println<0>("Valueless example");
  std::variant<float, int> valueless{0.F};
  try {
    valueless.emplace<int>(Struct());
    valueless.emplace<1>(ErrorStruct());
  } catch (int e) { println("Error during variant emplace operation"); }
  println(std::boolalpha, "Valueless: ", valueless.valueless_by_exception());
  println();

  // Overloaded pattern.
  println<0>("Overloaded example pattern");
  std::vector<std::variant<int, long, double, std::string>> vec = {10, 15l, 1.5, "hello"};
  print(""); // Just indentation.
  for (auto &v : vec) {
    std::visit(
        overloaded{
            [](int arg) { print<0>("int: ", arg, ", "); },
            [](long arg) { print<0>("long: ", arg, ", "); },
            [](double arg) { print<0>("double: ", std::fixed, arg, ", "); },
            [](const std::string &arg) { print<0>("std::string: ", std::quoted(arg)); },
        },
        v);
  }
  println();

  return 0;
}
