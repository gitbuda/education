#include "include/using_iostream.hpp"

int main(int argc, char **argv) {
  uint32_t x = 80;
  cout << "x = " << x << endl;
  uint32_t exp_2_x = x & -x;
  cout << "Exponent of 2 in " << x << " = " << exp_2_x << endl;
  return 0;
}
