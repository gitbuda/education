#include <iostream>

#include "counter.hpp"
#include "lock/lock_one.hpp"

Counter<lock::LockOne> lock_one;

void get_and_increment()
{
    std::cout << lock_one.get_and_increment() << std::endl;
}

int main()
{
    std::thread t1(get_and_increment);
    std::thread t2(get_and_increment);
    
    t1.join();
    t2.join();

    std::cout << lock_one.get_and_increment() << std::endl;

    return 0;
}
