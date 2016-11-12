#include <iostream>

#include "counter.hpp"
#include "lock/lock_one.hpp"
#include "lock/lock_two.hpp"
#include "lock/peterson.hpp"
#include "lock/filter.hpp"

// TODO: rewrite LockOne and LockTwo (because ThreadId is implemented)
// TODO: write deadlock usecases for the LockOne and LockTwo classes
// TODO: write long running test for Peterson lock
// Counter<lock::LockOne> counter_lock;
// Counter<lock::LockTwo> counter_lock;
// Counter<lock::Peterson> counter_lock;
Counter<lock::Filter<2>> counter_lock;

void get_and_increment()
{
    std::cout << counter_lock.get_and_increment() << std::endl;
}

int main()
{
    std::thread t1(get_and_increment);
    std::thread t2(get_and_increment);
    
    t1.join();
    t2.join();

    std::cout << counter_lock.get_and_increment() << std::endl;

    return 0;
}
