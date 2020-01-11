#include <unistd.h>
#include <iostream>

int main() {
  auto pageSize = getpagesize();
  std::cout << pageSize << std::endl;
  return 0;
}
