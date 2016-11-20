#pragma once

#include <atomic>
#include <cassert>

#include "util/thread_id.hpp"

namespace lock
{

class PetersonLock
{
public:
    void lock()
    {
        auto i = util::ThreadId<>::instance().get_id();
        assert(i <= 1);

        auto j = 1 - i;

        flag[i].store(true); // I'm interested
        victim.store(i); // you go first
        while(flag[j].load() && victim.load() == i) {} // wait
    }

    void unlock()
    {
        auto i = util::ThreadId<>::instance().get_id();
        assert(i <= 1);

        flag[i].store(false); // I'm not interested
    }

private:
    std::array<std::atomic<bool>, 2> flag;
    std::atomic<int> victim;
};

}
