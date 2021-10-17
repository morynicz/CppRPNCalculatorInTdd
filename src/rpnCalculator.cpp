#include "rpnCalculator.hpp"
#include <boost/range/adaptor/tokenized.hpp>
#include <list>

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
        if ("+" == token)
        {
            auto arg1 = stack.front();
            stack.pop_front();
            auto arg2 = stack.front();
            stack.pop_front();
            stack.push_front(arg1 + arg2);
            continue;
        }
        if ("-" == token)
        {
            auto arg1 = stack.front();
            stack.pop_front();
            auto arg2 = stack.front();
            stack.pop_front();
            stack.push_front(arg2 - arg1);
            continue;
        }
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

    auto tokens = input | boost::adaptors::tokenized(boost::regex("[+-\\w]+"));
    auto stack = calculateResult(tokens);

    if (stack.size() != 1)
    {
        throw InvalidInputException("malformed operation");
    }
    return stack.front();
}
}