#include "rpnCalculator.hpp"

namespace rpn
{
ResultType calculate(const std::string& input)
{
    if(input.size())
    {
        throw InvalidInputException("non numeric input");
    }
    return 0;
}
}