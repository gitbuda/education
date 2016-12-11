#pragma once

#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <chrono>

namespace util
{

// TODO: use std chrono litrals

class Backoff
{
private:
    const int min_delay;
    const int max_delay;
    int limit;

public:
    Backoff(int min, int max) :
        min_delay(min), max_delay(max), limit(min_delay)
    {
        std::srand(std::time(0));
    }

    void backoff()
    {
        int delay = std::rand() % limit;
        limit = std::min(max_delay, 2 * limit);
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    }
};

}
