#pragma once

#include <vector>

#include "util/thread_id.hpp"

namespace lock
{

class Filter
{
private:
    // aliases
    using id_t = int;
    using id_atomic_t = std::atomic<id_t>;
    using id_uptr_t = std::unique_ptr<id_atomic_t>;
    using id_collection_t = std::vector<id_uptr_t>;

    int N; // number of threads

    // NOTE: here has to be atomic otherwise compiler will make a mess
    // with reordering
    id_collection_t level;
    id_collection_t victim;

    bool is_spinning(int i, int me)
    {
        for (int k = 0; k < N; ++k)
        {
            if (k == me) continue;

            auto filter = (level[k]->load() >= i) && (victim[i]->load() == me);
            if (filter) return true;
        }

        return false;
    }

public:
    Filter(int N) : N(N)
    {
        for (int i = 0; i < N; ++i)
        {
            level.emplace_back(std::make_unique<id_atomic_t>(0));
            victim.emplace_back(std::make_unique<id_atomic_t>(0));
        }
    }

    void lock()
    {
        auto me = util::ThreadId::instance().get_id();

        for (int i = 1; i < N; i++) {
            level[me]->store(i);
            victim[i]->store(me);
            while (is_spinning(i, me)) {}
        }
    }

    void unlock()
    {
        auto me = util::ThreadId::instance().get_id();
        level[me]->store(0);
    }

};

}
