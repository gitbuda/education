#pragma once

#include <vector>

#include "util/thread_id.hpp"

namespace lock
{

// TODO: ints
// TODO: std::atomic for level and victim
// TODO: implementation isn't correct (DEADLOCK + ABORT) -> FIX IT
// TODO: the same problem with atomics

template <typename T>
using atomic_uptr = std::unique_ptr<std::atomic<T>>;

class Filter
{
private:
    size_t N;
    std::vector<atomic_uptr<size_t>> level;
    std::vector<atomic_uptr<size_t>> victim;

    bool spin(size_t i, size_t me)
    {
        // TODO: check this (should i start from 0?)
        for (uint64_t k = 0; k < N; ++k)
        {
            if (k == me) continue;

            auto filter = (level[k]->load() >= i) && (victim[i]->load() == me);
            if (filter) return true;
        }

        return false;
    }

public:
    Filter(size_t N) : N(N)
    {
        for (size_t i = 0; i < N; ++i)
        {
            level.emplace_back(std::make_unique<std::atomic<size_t>>(0));
            victim.emplace_back(std::make_unique<std::atomic<size_t>>(0));
        }
    }

    void lock()
    {
        auto me = util::ThreadId::instance().get_id();

        for (uint64_t i = 1; i < N; i++) { //attempt level 1
            // level[me] = i;
            // victim[i] = me;
            level[me]->store(i);
            victim[i]->store(me);
            while (spin(i, me)) {}
        }
    }

    void unlock()
    {
        auto me = util::ThreadId::instance().get_id();
        // level[me] = 0;
        level[me]->store(0);
    }

};

}
