#include <iostream>
#include <cstdlib>

#include "counter.hpp"
#include "lock/lock_one.hpp"
#include "lock/lock_two.hpp"
#include "lock/peterson.hpp"
#include "lock/filter.hpp"

int THREAD_NO = 100;

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

int main(int argc, char **argv)
{
    // second argument is thread number
    if (argc >= 2)
    {
        THREAD_NO = std::atoi(argv[1]) ?: THREAD_NO;
    }

    std::thread threads[THREAD_NO];

    for (int i = 0; i < THREAD_NO; ++i)
    {
        threads[i] = std::thread(get_and_increment);
    }
   
    for (int i = 0; i < THREAD_NO; ++i)
    {
        threads[i].join();
    } 

    std::cout << "COUNT: "<< counter_lock.get() << std::endl;

    return 0;
}
