// FROM: https://www.youtube.com/watch?v=p32owQE_5u0

// debian quick fix
// http://stackoverflow.com/questions/37096062/get-a-basic-c-program-to-compile-using-clang-on-ubuntu-16

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

    // std::clamp
    std::clamp(a.b, 2, 5);
    std::cout << a.b << std::endl;

    return 0;
}
