#include "rpnCalculator.hpp"
#include <boost/range/adaptor/tokenized.hpp>
#include <list>
#include <sstream>

namespace rpn
{
namespace
{
template<typename T>
auto calculateResult(const T& tokens)
{
    std::list<ResultType> stack;

    for (const auto& token : tokens)
    {
        try
        {
            stack.push_front(std::stoi(token));
        }
        catch (const std::invalid_argument)
        {
            throw InvalidInputException("non numeric input");
        }
    }
    return stack;
}
}

ResultType calculate(const std::string& input)
{
    if (input.size() == 0)
    {
        return 0;
    }

    auto tokens = input | boost::adaptors::tokenized(boost::regex("\\w+"));
    auto stack = calculateResult(tokens);

    if (stack.size() != 1)
    {
        throw InvalidInputException("malformed operation");
    }
    return stack.front();
}
}