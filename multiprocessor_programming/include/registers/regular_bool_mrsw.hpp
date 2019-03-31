#pragma once

#include "util/thread_id.hpp"
#include "registers/register.hpp"

namespace registers
{

class RegularBoolMRSW : public Register<bool>
{
public:
    RegularBoolMRSW()
    {
        last_ = false;
    }

    bool Read() override
    {
        return s_value_;
    }

    void Write(bool value) override
    {
        if (value != last_) {
            last_ = value;
            s_value_ = value;
        }
    }

    ~RegularBoolMRSW()
    {
    }

private:
    thread_local static bool last_;
    bool s_value_;
};

}
