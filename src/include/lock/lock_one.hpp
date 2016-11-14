#pragma once

#include <thread>
#include <unordered_map>

namespace lock
{

// deadlocks if thread executions are interleaved
class LockOne
{
private:
    auto this_thread_id()
    {
        return hasher(std::this_thread::get_id());
    }

    bool wait(int thread_id)
    {
        for (auto & flag : flags)
        {
            if (flag.first == thread_id) continue;

            if (flag.second == true) return true;
        }

        return false;
    }

public:
    void lock()
    {
        auto thread_id = this_thread_id();
        flags[thread_id] = true;
        while (wait(thread_id)) {} // wait
    }

    void unlock()
    {
        auto thread_id = this_thread_id();
        flags[thread_id] = false; // unlock
    }

private:
    std::unordered_map<int, bool> flags;
    std::hash<std::thread::id> hasher;
};

}
