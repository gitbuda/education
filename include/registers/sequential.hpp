#pragma once

#include "registers/register.hpp"

namespace registers
{

template <typename T>
class Sequential : public Register<T>
{
public:
    T Read() override
    {
        return value_;
    }

    void Write(T value) override
    {
        value_ = value;
    }

private:
    T value_;
};

}
