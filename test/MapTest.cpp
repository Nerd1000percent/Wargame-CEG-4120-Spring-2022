#include "gtest/gtest.h"
#include <iostream>
#include <string>
#include <memory>

#include "Map.h"
#include "UnitDatabase.h"
#include "nlohmann/json.hpp"

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

  std::shared_ptr<Map> p_map;
};

TEST_F(MapTestSuite, testSaveGameState)
{
  p_map->saveGameState();
}

TEST_F(MapTestSuite, testSerialization)
{
  // serialize the map
  nlohmann::json j = *p_map;

  // change to _DEBUG to make this work again
#ifdef DEBUG
  cout << __FUNCTION__ << ":" << __LINE__ << " unit=" << j.dump() << endl;
#endif

  // deserialize the map
  Map map(5);
  j.get_to(map);

  // verify all the fields
}