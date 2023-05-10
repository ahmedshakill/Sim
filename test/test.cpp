#include <gtest/gtest.h>

int factorial (int n){
  if(n==0 or n==1) return 1;
  else return n * factorial(n-1);
}
namespace{

TEST(FactorialTest, HandlesZeroInput) {
  EXPECT_EQ(factorial(0), 1);
}

TEST(HelloTest, BasicAssertions) {
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);
}


TEST(FactorialTest, HandlesPositiveInput) {
  EXPECT_EQ(factorial(1), 1);
  EXPECT_EQ(factorial(2), 2);
  EXPECT_EQ(factorial(3), 6);
  EXPECT_EQ(factorial(8), 40320);
}

}