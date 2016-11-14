#pragma once

#include <thread>
#include <unordered_map>

#include "util/thread_id.hpp"

namespace lock
{

// deadlocks if thread executions are interleaved
class LockOne
{
public:
    void lock()
    {
        auto i = util::ThreadId::instance().get_id();
        auto j = 1 - i;
        flags[i] = true;    // I'm interested
        while (flags[j]) {} // wait
    }

    void unlock()
    {
        auto i = util::ThreadId::instance().get_id();
        flags[i] = false; // unlock
    }

private:
    std::unordered_map<int, bool> flags;
    std::hash<std::thread::id> hasher;
};

}
