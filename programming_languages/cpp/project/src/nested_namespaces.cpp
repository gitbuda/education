// SOURCE:
// https://www.youtube.com/watch?v=p32owQE_5u0

#include <iostream>

// nested namespace
namespace io::network::test {
struct IOStruct {
  int b; // NOLINT
};
} // namespace io::network::test

int main() {
  // nested namespace
  io::network::test::IOStruct a{0};
  a.b = 1;
  std::cout << a.b << std::endl;

  return 0;
}
