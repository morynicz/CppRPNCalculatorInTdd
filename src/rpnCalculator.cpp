#include "rpnCalculator.hpp"
#include <sstream>

namespace rpn
{
ResultType calculate(const std::string& input)
{
    if (input.size() == 0)
    {
        return 0;
    }
    auto space = input.find_first_of(' ');
    try
    {
        return std::stoi(input.substr(0, space));
    }
    catch (const std::invalid_argument)
    {
        throw InvalidInputException("non numeric input");
    }
    return 0;
}
}