#include "include/using_iostream.hpp"

int main(int argc, char **argv)
{
    uint32_t x = 10, y = 20;
    cout << "Init values:" << endl;
    cout << "x = " << x << "; y = " << y << endl;
    cout << "XOR swap" << endl;
    x = x ^ y;
    y = y ^ x;
    x = x ^ y;
    cout << "x = " << x << "; y = " << y << endl;
    return 0;
}
