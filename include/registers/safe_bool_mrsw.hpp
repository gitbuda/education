#pragma once

#include "util/thread_id.hpp"
#include "registers/register.hpp"

namespace registers
{

class SafeBoolMRSW : public Register<bool>
{
public:
    SafeBoolMRSW(int capacity) :
        capacity_(capacity), s_table_(new bool[capacity_])
    {
    }

    bool Read() override
    {
        auto thread_id = util::ThreadId<>::instance().get_id();
        return s_table_[thread_id];
    }

    void Write(bool value) override
    {
        for (int i = 0; i < capacity_; ++i)
        {
            s_table_[i] = value;
        }
    }

    ~SafeBoolMRSW()
    {
        delete [] s_table_;
    }

private:
    int capacity_;
    bool* s_table_;
};

}
