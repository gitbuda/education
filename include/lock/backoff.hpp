#pragma once

#include <atomic>

#include "util/backoff.hpp"

namespace lock
{

// TODO: use std chrono litrals

template <int MIN_DELAY = 10, int MAX_DELAY = 1000>
class BackoffLock
{
private:
    std::atomic<bool> state {false};

public:
    void lock()
    {
        util::Backoff backoff{MIN_DELAY, MAX_DELAY};
        while (true) {
            while (state.load()) {}
            if (!state.exchange(true))
                return;
            else
                backoff.backoff();
        }
    }

    void unlock()
    {
        state.store(false);
    }
};

}
