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