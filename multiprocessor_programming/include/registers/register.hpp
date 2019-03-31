#pragma once

namespace registers
{

template <typename T>
class Register
{
public:
    virtual T Read() = 0;
    virtual void Write(T value) = 0;
    virtual ~Register() {}
};

}
