#pragma once

#include <atomic>

namespace lock
{

class TTASLock
{
public:
    void lock()
    {
        while (true)
        {
            while (state.load()) {}
            if (!state.exchange(true))
                return;
        }
    }

    void unlock()
    {
        state.store(false);
    }

private:
    std::atomic<bool> state{false};
};

}
