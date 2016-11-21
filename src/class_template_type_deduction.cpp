#include <iostream>
#include <tuple>

template <class X, class Y>
struct A
{
    A(X x, Y y) : x(x), y(y) {}

    X x;
    Y y;
};

int main()
{
    auto a = A(0, 1);

    std::tuple b(2, 3);

    std::cout << a.x << " " << a.y << " " << std::endl;

    std::cout << std::get<0>(b) << " " << std::get<1>(b) << " " << std::endl;
    
    return 0;
}
