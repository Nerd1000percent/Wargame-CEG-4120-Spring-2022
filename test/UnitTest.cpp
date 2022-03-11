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
    pUnit = std::make_shared<Unit>(id, numMoves, attackPower, defensePower);
  }

  // Override this to define how to tear down the environment.
  void TearDown() override {
    pUnit.reset();
  }

  std::shared_ptr<Unit> pUnit;
};

TEST_F(UnitTestSuite, firstTest)
{
  EXPECT_EQ(pUnit->getID(), "test_unit");
}

TEST_F(UnitTestSuite, serializationTest)
{
  // serialize the unit
  nlohmann::json j = *pUnit;

#ifdef _DEBUG
  cout << __FUNCTION__ << ":" << __LINE__ << " unit=" << j.dump() << endl;
#endif

  // deserialize the unit
  Unit unit;
  j.get_to(unit);

  // verify all the fields
  EXPECT_EQ(pUnit->getID(), unit.getID());
}