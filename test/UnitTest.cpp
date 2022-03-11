#include "gtest/gtest.h"
#include <iostream>
#include <string>
#include <memory>

//temporary for debugging
#include <typeinfo>

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
    p_unit = make_shared<Unit>(id, numMoves, attackPower, defensePower);
    
    // auto temp = *p_unit.get();
    // cout << "Type of temp : " << typeid(temp).name() << endl;

    p_unitCopy = make_shared<Unit>(*p_unit.get());
  }

  // Override this to define how to tear down the environment.
  void TearDown() override {
      p_unit.reset();
  }

  shared_ptr<Unit> p_unit;
  shared_ptr<Unit> p_unitCopy;
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

// Verify that the copy constructor creates copies correctly
TEST_F(UnitTestSuite, testCopyConstructor)
{
    EXPECT_EQ(p_unitCopy->getID(), "test_unit");
    EXPECT_EQ(p_unitCopy->getMovement(), 3);
    EXPECT_EQ(p_unitCopy->getAttackPower(), 7);
    EXPECT_EQ(p_unitCopy->getDefensePower(), 9);
}

// Verify that the dealDamage function
TEST_F(UnitTestSuite, testDealDamage)
{

}