#include <any>
#include <iostream>
#include <optional>
#include <string>
#include <variant>

struct Test {
  int test_int;

  Test(int test_int) : test_int(test_int) {
    std::cout << "Test Constructor" << std::endl;
  }
  Test(const Test& other) {
    std::cout << "Test Copy Constructor" << std::endl;
    this->test_int = other.test_int;
  }
  Test(Test&& other) {
    std::cout << "Test Move Constructor" << std::endl;
    this->test_int = std::move(other.test_int);
  }
};

int main() {
  std::cout << "Constructing optional without in_place" << std::endl;
  std::optional<Test> test1 = Test(10);
  std::cout << std::endl;

  std::cout << "Constructing optional with in_place" << std::endl;
  std::optional<Test> test2(std::in_place, 10);
  std::cout << std::endl;

  std::cout << "in_place_type" << std::endl;
  std::any any(std::in_place_type<int>, 10);
  std::cout << std::any_cast<int>(any) << std::endl;
  std::cout << std::endl;

  std::cout << "in_place_index" << std::endl;
  std::variant<int, std::string> v(std::in_place_index<1>, "test");
  std::cout << "Index: " << v.index() << std::endl;
  std::cout << std::endl;

  return 0;
}
