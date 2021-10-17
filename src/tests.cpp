#include "gtest/gtest.h"
#include "rpnCalculator.hpp"

TEST(TestRpn, emptyInputReturnsZero)
{
    EXPECT_EQ(0, rpn::calculate(""));
}