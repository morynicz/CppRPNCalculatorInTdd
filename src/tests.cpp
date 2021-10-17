#include "gtest/gtest.h"
#include "rpnCalculator.hpp"

TEST(TestRpn, emptyInputReturnsZero)
{
    EXPECT_EQ(0, rpn::calculate(""));
}

TEST(TestRpn, nonNumericInputCausesInvalidInputException)
{
    EXPECT_THROW(rpn::calculate("ple"), rpn::InvalidInputException);
}
