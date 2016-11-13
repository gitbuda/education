#pragma once

#include <vector>

#include "util/thread_id.hpp"

namespace lock
{

// TODO: std::atomic for level and victim
// TODO: implementation isn't correct (DEADLOCK + ABORT) -> FIX IT

class Filter
{
private:
    size_t N;
    std::vector<size_t> level;
    std::vector<size_t> victim;

    bool spin(size_t i, size_t me)
    {
        // TODO: check this (should i start from 0?)
        for (uint64_t k = 0; k < N; ++k)
        {
            if (k == me) continue;

            auto filter = (level[k] >= i) && (victim[i] == me);
            if (filter) return true;
        }

        return false;
    }

public:
    Filter(size_t N) : N(N), level(N, 0), victim(N, 0) {}

    void lock()
    {
        auto me = util::ThreadId::instance().get_id();

        for (uint64_t i = 1; i < N; i++) { //attempt level 1
            level[me] = i;
            victim[i] = me;
            while (spin(i, me)) {}
        }
    }

    void unlock()
    {
        auto me = util::ThreadId::instance().get_id();
        level[me] = 0;
    }

};

}
