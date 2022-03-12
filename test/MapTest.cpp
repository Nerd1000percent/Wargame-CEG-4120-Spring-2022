#include "gtest/gtest.h"
#include <iostream>
#include <string>
#include <memory>

#include "Coordinates.h"
#include "Map.h"
#include "UnitDatabase.h"
#include "nlohmann/json.hpp"

using namespace std;

class MapTestSuite : public testing::Test
{
public:
  // Override this to define how to set up the environment.
  void SetUp() override {
    
    // clear database
    UnitDatabase::getUnitDatabase().clear();

    // build a tile
    Tiles tile("terrainName", 1);
    UnitDatabase::getUnitDatabase().addUnit(std::make_shared<Unit>("unit1", 1, 2, 3));
    UnitDatabase::getUnitDatabase().addUnit(std::make_shared<Unit>("unit2", 4, 5, 6));
    tile.addUnit(UnitDatabase::getUnitDatabase().getUnit("unit1"));
    tile.addUnit(UnitDatabase::getUnitDatabase().getUnit("unit2"));

    // create a map with the tile
    Coordinates dimensions(1, 1);
    p_map = std::make_shared<Map>(dimensions);
    //p_map->
  }

  // Override this to define how to tear down the environment.
  void TearDown() override {
    UnitDatabase::getUnitDatabase().clear();
    p_map.reset();
  }

  shared_ptr<Map> p_map;
};

TEST_F(MapTestSuite, testSize)
{
    EXPECT_EQ(p_map->size().getColumn(), 1);
    EXPECT_EQ(p_map->size().getRow(), 1);
}

TEST_F(MapTestSuite, testSerialization)
{
  // serialize the map
  

  // change to _DEBUG to make this work again
#ifdef DEBUG
  cout << __FUNCTION__ << ":" << __LINE__ << " unit=" << j.dump() << endl;
#endif

  // deserialize the map
  

  // verify all the fields
}