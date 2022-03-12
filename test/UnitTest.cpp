#include "gtest/gtest.h"
#include <iostream>
#include <string>
#include <memory>

#include "Unit.h"
#include "nlohmann/json.hpp"

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
  EXPECT_EQ(p_unit->isActive(), true);
  EXPECT_EQ(p_unit->getMovement(), 3);
  EXPECT_EQ(p_unit->getAttackPower(), 7);
  EXPECT_EQ(p_unit->getDefensePower(), 9);
}

// Verify that the copy constructor creates copies correctly
TEST_F(UnitTestSuite, testCopyConstructor)
{
    EXPECT_EQ(p_unitCopy->getID(), "test_unit");
    EXPECT_EQ(p_unitCopy->isActive(), true);
    EXPECT_EQ(p_unitCopy->getMovement(), 3);
    EXPECT_EQ(p_unitCopy->getAttackPower(), 7);
    EXPECT_EQ(p_unitCopy->getDefensePower(), 9);
}

// Verify that the dealDamage function changes the attack and defense values of units correctly
TEST_F(UnitTestSuite, testDealDamage)
{
    // this unit is dealt 6 damage, attack power goes down to 1 but it is still active
    p_unit->dealDamage(6);
    EXPECT_EQ(p_unit->getAttackPower(), 1);
    EXPECT_EQ(p_unit->isActive(), true);

    // this unit is dealt 7 damage, attack power goes down to 1 so it is inactive
    p_unitCopy->dealDamage(7);
    EXPECT_EQ(p_unitCopy->getAttackPower(), 0);
    EXPECT_EQ(p_unitCopy->isActive(), false);
}

// Verify that spendMovement and resetMovement functions work correctly
TEST_F(UnitTestSuite, testMovement)
{
    // m_currentMoves should be 0 after 3 of the 3 total movements points are spent
    p_unit->spendMovement(3);
    EXPECT_EQ(p_unit->getCurrentMovement(), 0);
    
    // m_currentMoves should be 3 after it is reset to m_numMoves
    p_unit->resetMovement();
    EXPECT_EQ(p_unit->getCurrentMovement(), 3);
}

TEST_F(UnitTestSuite, serializationTest)
{
  // serialize the unit
  nlohmann::json j = *p_unit;

#ifdef _DEBUG
  cout << __FUNCTION__ << ":" << __LINE__ << " unit=" << j.dump() << endl;
#endif

  // deserialize the unit
  Unit unit;
  j.get_to(unit);

  // verify all the fields
  EXPECT_EQ(p_unit->getID(), unit.getID());
  EXPECT_EQ(p_unit->isActive(), unit.isActive());
  EXPECT_EQ(p_unit->getMovement(), unit.getMovement());
  EXPECT_EQ(p_unit->getAttackPower(), unit.getAttackPower());
  EXPECT_EQ(p_unit->getDefensePower(), unit.getDefensePower());
}