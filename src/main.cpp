#include <iostream>
#include <cstdlib>

#include "counter.hpp"
#include "lock/lock_one.hpp"
#include "lock/lock_two.hpp"
#include "lock/peterson.hpp"
#include "lock/filter.hpp"
#include "lock/tas_lock.hpp"
#include "lock/ttas_lock.hpp"

const int THREAD_NO = 64;

// TODO: write deadlock usecases for the LockOne and LockTwo classes
// TODO: write test binaries for all relevant implementations
// TODO: write long running tests
// Counter<lock::LockOne> counter_lock;
// Counter<lock::LockTwo> counter_lock;
// Counter<lock::Peterson> counter_lock;
// Counter<lock::Filter> counter_lock {lock::Filter(THREAD_NO)};
// Counter<lock::TASLock> counter_lock;
Counter<lock::TTASLock> counter_lock;

void get_and_increment()
{
    std::cout << counter_lock.get_and_increment() << std::endl;
}

int main(int argc, char **argv)
{
    std::array<std::thread, THREAD_NO> threads;

    for (int i = 0; i < THREAD_NO; ++i)
    {
        threads[i] = std::thread(get_and_increment);
    }
   
    for (int i = 0; i < THREAD_NO; ++i)
    {
        threads[i].join();
    } 

    std::cout << "COUNT: " << counter_lock.get() << std::endl;

    return 0;
}
