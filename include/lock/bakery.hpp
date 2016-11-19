#pragma once

#include <algorithm>
#include <vector>

#include "util/thread_id.hpp"

namespace lock
{

class BakeryLock
{
public:
    BakeryLock(int N) : N(N)
    {
        flag.reserve(N);
        label.reserve(N);

        for (int i = 0; i < N; i++)
        {
            flag[i] = false;
            label[i] = 0;
        }
    }

    void lock()
    {
        auto me = util::ThreadId::instance().get_id();
        flag[me] = true;
        label[me] = *std::max_element(label.begin(), label.end()) + 1;
        while (is_spinning(me)) {}
    }

    void unlock()
    {
        auto me = util::ThreadId::instance().get_id();
        flag[me] = false;
    }

private:
    int N;
    std::vector<bool> flag;
    std::vector<int> label;

    bool is_spinning(int me)
    {
        for (int k = 0; k < N; ++k)
        {
            if (k == me) continue;

            auto stop = (flag[k] && ((label[k] <= label[me]) && (k < me)));
            if (stop) return true;
        }

        return false;
    }
};

}
