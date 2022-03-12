#include "gtest/gtest.h"
#include <iostream>
#include <string>
#include <memory>

#include "Map.h"
#include "UnitDatabase.h"

#include <memory>
using namespace std;

class MapTestSuite : public testing::Test
{
public:
  // Override this to define how to set up the environment.
  void SetUp() override {
    //pMap = std::make_shared<Map>(5);
    UnitDatabase::getUnitDatabase().clear();
  }

  // Override this to define how to tear down the environment.
  void TearDown() override {
    //pMap.reset();
    UnitDatabase::getUnitDatabase().clear();
  }

  std::shared_ptr<Map> pMap;
};

TEST_F(MapTestSuite, firstTest)
{
  pMap->saveGameState();
}