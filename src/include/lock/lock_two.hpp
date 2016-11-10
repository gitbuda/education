#pragma once

#include <atomic>
#include <thread>

namespace lock
{

// deadlocks if one thread runs completely before the other
class LockTwo
{
public:
    void lock()
    {
        auto thread_id = hasher(std::this_thread::get_id());
        victim.store(thread_id); // let the other go first
        while (victim.load() == thread_id) {} // wait
    }

    void unlock() {}

private:
    std::atomic<size_t> victim;
    std::hash<std::thread::id> hasher;
};

}
