#include "gtest/gtest.h"
#include <iostream>
#include <string>
#include <memory>

#include "Unit.h"

using namespace std;

class UnitTestSuite : public testing::Test
{
public:
  // Override this to define how to set up the environment.
  void SetUp() override {
    std::string id = "test_unit";
    int numMoves = 3;
    int attackPower = 7;
    int defensePower = 9;
    p_unit = std::make_shared<Unit>(id, numMoves, attackPower, defensePower);
  }

  // Override this to define how to tear down the environment.
  void TearDown() override {
      p_unit.reset();
  }

  std::shared_ptr<Unit> p_unit;
};

// Verify that the constructor has initialized member variables correctly
// Also verify that the getter functions work correctly
TEST_F(UnitTestSuite, testConstructor)
{
  EXPECT_EQ(p_unit->getID(), "test_unit");
  EXPECT_EQ(p_unit->getMovement(), 3);
  EXPECT_EQ(p_unit->getAttackPower(), 7);
  EXPECT_EQ(p_unit->getDefensePower(), 9);
}

TEST_F(UnitTestSuite, testCopyConstructor)
{

}