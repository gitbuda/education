#pragma once

#include <stdexcept>

namespace exception
{

class EmptyException : public std::runtime_error
{
};

}
