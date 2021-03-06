#pragma once
#include <stdexcept>
#include <string>

namespace rpn
{
using ResultType = int;
class InvalidInputException : public std::invalid_argument
{
  public:
    InvalidInputException(const std::string& what)
        : std::invalid_argument(what)
    {
    }
};

ResultType calculate(const std::string&);
}