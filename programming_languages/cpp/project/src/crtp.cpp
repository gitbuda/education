#include <iostream>
#include <memory>

template<typename T>
struct Base {
  void call() { static_cast<T *>(this)->impl(); }
};

struct Derived : public Base<Derived> {
  void impl() { std::cout << "Derived Impl" << std::endl; }
};

// TODO(gitbuda): Polymorphic chaining.
// TODO(gitbuda): Polymorphic copy construction.

int main() {
  auto derived = std::make_unique<Derived>();
  derived->call();
  return 0;
}
