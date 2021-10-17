#include "gtest/gtest.h"

TEST(TestRpn,emptyInputReturnsZero)
{
    EXPECT_EQ(0, calculate(""));
}