#include <iostream>
#include <vector>

#include <cxxabi.h>

int main() {
  std::vector<int64_t> vector;

  int status;
  auto type_name = typeid(vector).name();
  auto real_name = abi::__cxa_demangle(type_name, 0, 0, &status);
  if (status == 0) {
    std::cout << "TYPE ID: " << type_name << std::endl
              << "REAL NAME: " << real_name << '\n';
  } else {
    std::cout << "abi::__cxa_demangle failed!" << std::endl;
  }
  free(real_name);

  return 0;
}
