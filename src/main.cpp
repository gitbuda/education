#include <iostream>

#include "counter.hpp"
#include "lock/lock_one.hpp"
#include "lock/lock_two.hpp"
#include "lock/peterson.hpp"
#include "lock/filter.hpp"

size_t THREAD_NO = 100;

// TODO: rewrite LockOne and LockTwo (because ThreadId is implemented)
// TODO: write deadlock usecases for the LockOne and LockTwo classes
// TODO: write long running test for Peterson lock
// Counter<lock::LockOne> counter_lock;
// Counter<lock::LockTwo> counter_lock;
// Counter<lock::Peterson> counter_lock;
Counter<lock::Filter> counter_lock {lock::Filter(THREAD_NO)};

void get_and_increment()
{
    std::cout << counter_lock.get_and_increment() << std::endl;
}

int main()
{
    std::thread threads[THREAD_NO];

    for (size_t i = 0; i < THREAD_NO; ++i)
    {
        threads[i] = std::thread(get_and_increment);
    }
   
    for (size_t i = 0; i < THREAD_NO; ++i)
    {
        threads[i].join();
    } 

    std::cout << counter_lock.get_and_increment() << std::endl;

    return 0;
}
