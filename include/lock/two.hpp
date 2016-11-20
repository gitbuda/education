#pragma once

#include <cassert>
#include <atomic>

#include "util/thread_id.hpp"

namespace lock
{

// deadlocks if one thread runs completely before the other
class TwoLock
{
public:
    void lock()
    {
        auto thread_id = util::ThreadId<>::instance().get_id();
        assert(thread_id <= 1); 

        victim.store(thread_id); // let the other go first
        while (victim.load() == thread_id) {} // wait
    }

    void unlock() {}

private:
    std::atomic<int> victim;
};

}
