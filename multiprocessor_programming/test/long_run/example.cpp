#include <cassert>

int main()
{
    for (int i = 0; i < 1000000000; ++i)
    {
        assert(0 == 0);
    }

    return 0;
}
