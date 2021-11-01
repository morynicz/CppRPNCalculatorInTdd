#include "rpnCalculator.hpp"
#include <algorithm>
#include <functional>
#include <list>
#include <map>
#include <ranges>

namespace rpn
{
namespace
{
using Stack = std::list<ResultType>;
using Operator = std::function<ResultType(ResultType, ResultType)>;

const std::map<char, Operator> operators{
    { '+', [](ResultType lhs, ResultType rhs) { return lhs + rhs; } },
    { '-', [](ResultType lhs, ResultType rhs) { return lhs - rhs; } }
};

class WorkStack
{
  public:
    void applyOperation(const Operator& op)
    {
        const auto [arg1, arg2] = pop2();
        stack.push_front(op(arg2, arg1));
    }

    void storeNumber(const std::string& number)
    try
    {
        stack.push_front(std::stoi(number));
    }
    catch (const std::invalid_argument)
    {
        throw InvalidInputException("non numeric input");
    }

    Stack getStack() const { return stack; }

  private:
    std::list<ResultType> stack;
    std::tuple<ResultType, ResultType> pop2()
    {
        auto arg1 = stack.front();
        stack.pop_front();
        auto arg2 = stack.front();
        stack.pop_front();
        return { arg1, arg2 };
    }
};

auto calculateResult(auto tokens)
{
    WorkStack stack;
    auto operate = [&stack](const std::string& token) -> void
    {
        if (const auto operation = operators.find(token.back());
            operation != operators.end())
        {
            stack.applyOperation(operation->second);
            return;
        }
        stack.storeNumber(std::string{ token });
    };

    std::ranges::for_each(tokens, operate);
    return stack.getStack();
}
}

ResultType calculate(const std::string& input)
{
    if (input.size() == 0)
    {
        return 0;
    }

    auto tokens = input | std::views::split(' ') |
                  std::views::transform(
                      [](auto&& rng) { // TODO: find a better way to convert
                                       // damned split_view element to a string
                          std::string result;
                          std::ranges::copy(rng.begin(),
                                            rng.end(),
                                            std::back_inserter(result));
                          return result;
                      });
    auto stack = calculateResult(tokens);

    if (stack.size() != 1)
    {
        throw InvalidInputException("malformed operation");
    }
    return stack.front();
}
}