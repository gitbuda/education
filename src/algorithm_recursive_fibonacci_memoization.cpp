#include <cassert>
#include <vector>

#include "include/using_iostream.hpp"

auto fibonacci(int x, std::vector<int> &results)
{
    if (x == 1) return 0;
    if (x == 2) return 1;
    if (results[x] != -1) return results[x];

    results[x] = fibonacci(x - 1, results) + fibonacci(x - 2, results);

    return results[x];
}

int main(int argc, char **argv)
{
    assert(argc == 2);

    int index = std::atoi(argv[1]);
    assert(index > 0);

    std::vector<int> results(index + 1, -1);
    auto result = fibonacci(index, results);
    cout << result << endl;

    return 0;
}
