#pragma once

#include <cassert>
#include <atomic>

#include "util/thread_id.hpp"

namespace lock
{

// deadlocks if thread executions are interleaved
class OneLock
{
public:
    void lock()
    {
        auto i = util::ThreadId::instance().get_id();
        assert(i <= 1);

        auto j = 1 - i;

        flags[i].store(true);    // I'm interested
        while (flags[j].load()) {} // wait
    }

    void unlock()
    {
        auto i = util::ThreadId::instance().get_id();
        assert(i <= 1);

        flags[i].store(false); // unlock
    }

private:
    std::array<std::atomic<bool>, 2> flags;
};

}
