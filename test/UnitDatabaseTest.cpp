#include "gtest/gtest.h"
#include "UnitDatabase.h"
#include <iostream>
#include <string>
#include <memory>

#include "Unit.h"
#include "nlohmann/json.hpp"

using namespace std;

class UnitDatabaseTestSuite : public testing::Test
{
public:
  // Override this to define how to set up the environment.
  void SetUp() override {
    UnitDatabase::getUnitDatabase().clear();
  }

  // Override this to define how to tear down the environment.
  void TearDown() override {
    UnitDatabase::getUnitDatabase().clear();
  }
};

TEST_F(UnitDatabaseTestSuite, TODO)
{

}
