#include "fib.h"
#include "gtest/gtest.h"

TEST(FibTest, Nominal) {
	Fibonacci f;
	EXPECT_EQ(f.get(5), 5);
	EXPECT_EQ(f.get(7), 13);
}
