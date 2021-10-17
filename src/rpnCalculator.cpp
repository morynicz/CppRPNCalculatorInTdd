#include "rpnCalculator.hpp"
#include <list>
#include <sstream>

namespace rpn
{
ResultType calculate(const std::string& input)
{
    std::list<ResultType> stack;
    if (input.size() == 0)
    {
        return 0;
    }
    auto start = 0;
    do
    {
        auto end = input.find(' ', start);
        try
        {
            stack.push_front(std::stoi(input.substr(start, end)));
            start = end + 1;
            if (end == std::string::npos)
            {
                break;
            }
        }
        catch (const std::invalid_argument)
        {
            throw InvalidInputException("non numeric input");
        }
    } while (true);
    if (stack.size() != 1)
    {
        throw InvalidInputException("malformed operation");
    }
    return stack.front();
}
}