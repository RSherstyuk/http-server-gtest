#include "Fact.h"
#include <gtest/gtest.h>

TEST(FactorialTest, HandlesPositiveInput) {
  EXPECT_EQ(Fact::fact(1),1);
  EXPECT_EQ(Fact::fact(2),2);
  EXPECT_EQ(Fact::fact(3),6);
  EXPECT_EQ(Fact::fact(5),120);
}

TEST(FactorialTest, HandlesZeroInput) {
    EXPECT_EQ(Fact::fact(0), 1);
}

TEST(FactorialTest, HandlesNegativeInput) {
    EXPECT_EQ(Fact::fact(-1), 1);  
}