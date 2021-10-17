#include "gtest/gtest.h"

int calculate(std::string)
{
    return 0;
}

TEST(TestRpn,emptyInputReturnsZero)
{
    EXPECT_EQ(0, calculate(""));
}