#pragma once

#include <mutex>

#include "exception/empty.hpp"
#include "exception/full.hpp"

namespace data_structure
{

template <class Item, class Lock = std::mutex>
class LockQueue
{
private:
    int head, tail;
    Lock lock;
    std::vector<Item> items;

public:
    LockQueue(int capacity) : head(0), tail(0)
    {
        items.reserve(capacity);
    }

    void push(Item x)
    {
        std::lock_guard<Lock> hold(lock);

        if (tail - head == items.size() && (tail != 0 || head != 0))
            throw exception::FullException();

        items[tail % items.capacity()] = x;
        ++tail;
    }

    Item pop()
    {
        std::lock_guard<Lock> hold(lock);

        if (tail == head)
            throw exception::EmptyException();

        // Item has to be movable type!
        auto x = std::move(items[head % items.capacity()]);
        head++;

        return x;
    }
};

}
