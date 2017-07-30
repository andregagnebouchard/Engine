// Step 1. Include necessary header files such that the stuff your
// test logic needs is declared.
//
// Don't forget gtest.h, which declares the testing framework.

#include <limits.h>
#include "gtest/gtest.h"
TEST(FactorialTest, Negative) 
{
	EXPECT_EQ(1, 1);
}
TEST(FactorialTest, Zero) 
{
	EXPECT_EQ(1, 0);
}

// Tests factorial of positive numbers.
TEST(FactorialTest, Positive) 
{
	EXPECT_EQ(1, 1);
}

TEST(A, B) 
{
}