/*
** Created by Christian Howard on 10/9/22.
*/

#include "gtest/gtest.h"

class SomeTest : public ::testing::Test {
 public:
  SomeTest() = default;
  ~SomeTest() = default;
};

TEST_F(SomeTest, Test1) {

  EXPECT_EQ(1, 1);
  GTEST_LOG_(INFO) << "Just some info";
  
}

TEST_F(SomeTest, Test2) {
  EXPECT_GE(3, 1);
}
