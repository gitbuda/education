// SOURCE:
// https://www.youtube.com/watch?v=p32owQE_5u0

#include <iostream>

// nested namespace
namespace io::network::test
{
    struct IOStruct {
        int b;
    };
}

int main()
{
    // nested namespace
    io::network::test::IOStruct a;
    a.b = 10;
    std::cout << a.b << std::endl;

    return 0;
}
