#include <cassert>
#include <vector>

#include "include/using_iostream.hpp"

using index_type = int;
using value_type = long long;

template <typename index_type, typename value_type>
value_type fibonacci(index_type x, std::vector<value_type> &results) {
  if (x == 1) return 0;
  if (x == 2) return 1;
  if (results[x] != -1) return results[x];

  results[x] = fibonacci(x - 1, results) + fibonacci(x - 2, results);

  return results[x];
}

int main(int argc, char **argv) {
  assert(argc == 2);

  index_type index = std::atoi(argv[1]);

  // index geater or equal 93 produces values which cann't fit
  // in the long long range
  assert(index > 0 && index < 94);

  std::vector<value_type> results(index + 1, -1);
  auto result = fibonacci<index_type, value_type>(index, results);
  cout << result << endl;

  return 0;
}
