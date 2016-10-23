// SOURCE:
// https://www.youtube.com/watch?v=p32owQE_5u0

#include <iostream>
#include <algorithm>

int main()
{
    int x = 1;

    std::cout << std::clamp(x, 2, 5) << std::endl;

    return 0;
}
