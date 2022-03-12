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
    
    UnitDatabase::getUnitDatabase().clear();

    Coordinates dimensions(3, 3);
    p_map = std::make_shared<Map>(dimensions);
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
    EXPECT_EQ(p_map->size().getColumn(), 3);
    EXPECT_EQ(p_map->size().getRow(), 3);
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