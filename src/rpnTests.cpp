#include "rpnCalculator.hpp"
#include "gtest/gtest.h"

TEST(TestRpn, emptyInputReturnsZero)
{
    EXPECT_EQ(0, rpn::calculate(""));
}

TEST(TestRpn, nonNumericInputCausesInvalidInputException)
{
    EXPECT_THROW(rpn::calculate("ple"), rpn::InvalidInputException);
}

TEST(TestRpn, singleNumberInputReturnsThisNumber)
{
    EXPECT_EQ(2048, rpn::calculate("2048"));
}

TEST(TestRpn, twoNumbersWithoutOperatorCauseInvalidInputException)
{
    EXPECT_THROW(rpn::calculate("2 2"), rpn::InvalidInputException);
}

struct OperationAndResult
{
    const std::string operation;
    const rpn::ResultType expectedResult;
};

std::ostream& operator<<(std::ostream& str, const OperationAndResult& op)
{
    return str << "Operation: " << op.operation
               << ", expectedResult: " << op.expectedResult;
}

struct TestRpnNonExceptionCases
    : public testing::TestWithParam<OperationAndResult>
{
};

TEST_P(TestRpnNonExceptionCases, calculatedOperationReturnsExpectedResult)
{
    auto params = GetParam();
    EXPECT_EQ(rpn::calculate(params.operation), params.expectedResult);
}

INSTANTIATE_TEST_SUITE_P(RpnTests,
                         TestRpnNonExceptionCases,
                         testing::Values(OperationAndResult{ "2 2 +", 4 },
                                         OperationAndResult{ "3 2 -", 1 }));
