#include "rpnCalculator.hpp"
#include <boost/range/adaptor/tokenized.hpp>
#include <functional>
#include <list>
#include <map>

namespace rpn
{
namespace
{
using Stack = std::list<ResultType>;
using Operator = std::function<ResultType(ResultType, ResultType)>;

std::map<char, Operator> operators{
    { '+', [](ResultType lhs, ResultType rhs) { return lhs + rhs; } },
    { '-', [](ResultType lhs, ResultType rhs) { return lhs - rhs; } }
};

std::tuple<ResultType, ResultType> pop2(Stack& stack)
{
    auto arg1 = stack.front();
    stack.pop_front();
    auto arg2 = stack.front();
    stack.pop_front();
    return { arg1, arg2 };
}

void applyOperation(Stack& stack, const Operator& op)
{
    const auto [arg1, arg2] = pop2(stack);
    stack.push_front(op(arg2, arg1));
}

void storeNumber(Stack& stack, const std::string number)
try
{
    stack.push_front(std::stoi(number));
}
catch (const std::invalid_argument)
{
    throw InvalidInputException("non numeric input");
}

template<typename T>
auto calculateResult(const T& tokens)
{
    Stack stack;

    for (const std::string& token : tokens)
    {
        if (const auto operation = operators.find(token.back());
            operation != operators.end())
        {
            applyOperation(stack, operation->second);
            continue;
        }
        storeNumber(stack, token);
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