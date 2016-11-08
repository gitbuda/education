#pragma once

#include <mutex>

template <typename Lock = std::mutex>
class Counter
{
public:
    auto get_and_increment()
    {
        // std::unique_lock is more powerful but is not needed here
        std::lock_guard<Lock> guard(lock); // enter critical section (RAII)
        
        // increase and return value
        return ++value;
    } // leave criticl section (quard object is destroyed)

private:
    long value {0};
    Lock lock;
};
