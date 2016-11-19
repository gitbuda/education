#pragma once

#include <atomic>

namespace lock
{

class TASLock
{
public:
    void lock()
    {
        while (state.test_and_set()) {}
    }

    void unlock()
    {
        state.clear();
    }

private:
    std::atomic_flag state = ATOMIC_FLAG_INIT;
};

}
