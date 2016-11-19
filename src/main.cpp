#include <iostream>
#include <cstdlib>

#include "counter.hpp"

#include "lock/one.hpp"
#include "lock/two.hpp"
#include "lock/peterson.hpp"
#include "lock/bakery.hpp"
#include "lock/filter.hpp"
#include "lock/tas.hpp"
#include "lock/ttas.hpp"

const int THREAD_NO = 64;

// Counter<lock::OneLock> counter_lock;
// Counter<lock::TwoLock> counter_lock;
// Counter<lock::PetersonLock> counter_lock;
// Counter<lock::FilterLock> counter_lock {lock::FilterLock(THREAD_NO)};
// Counter<lock::BakeryLock> counter_lock {lock::BakeryLock(THREAD_NO)};
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
