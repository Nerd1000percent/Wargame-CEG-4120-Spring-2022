#include "gtest/gtest.h"
#include <iostream>
#include <string>

using namespace std;

class UnitTestSuite : public testing::Test
{
public:
  // Override this to define how to set up the environment.
  void SetUp() override {
    example = "hello";
  }

  // Override this to define how to tear down the environment.
  void TearDown() override {
  }

  string example;
};

TEST_F(UnitTestSuite, firstTest)
{
  EXPECT_EQ(example, "hello");
}