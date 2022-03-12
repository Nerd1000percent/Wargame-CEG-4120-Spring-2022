#include "gtest/gtest.h"
#include "UnitDatabase.h"
#include <iostream>
#include <string>
#include <memory>

#include "Unit.h"
#include "Tiles.h"
#include "nlohmann/json.hpp"

using namespace std;

class TilesTestSuite : public testing::Test
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

TEST_F(TilesTestSuite, serialization)
{
  // build a tile
  Tiles original("terrainName", 1);
  UnitDatabase::getUnitDatabase().addUnit(std::make_shared<Unit>("unit1", 1, 2, 3));
  UnitDatabase::getUnitDatabase().addUnit(std::make_shared<Unit>("unit2", 4, 5, 6));
  original.addUnit(UnitDatabase::getUnitDatabase().getUnit("unit1"));
  original.addUnit(UnitDatabase::getUnitDatabase().getUnit("unit2"));

  // serialize it to json
  nlohmann::json json = original;
  //cout << __FUNCTION__ << ":" << __LINE__ << " original=" << json.dump() << endl;

  // deserialize from json
  Tiles copy;
  json.get_to(copy);

  // verify that the copy matches the original
  EXPECT_EQ(original.getTerrain().getName(), copy.getTerrain().getName());
  EXPECT_EQ(original.getUnits().size(), copy.getUnits().size());

  auto origUnits = original.getUnits();
  auto copyUnits = copy.getUnits();

  auto i = origUnits.begin();
  auto j = copyUnits.begin();
  while (i != origUnits.end() && j != copyUnits.end())
  {
    // the shared pointers should be pointing to the same units in the global database
    EXPECT_EQ((*i).get(), (*j).get());

    // advance to the next units
    ++i; 
    ++j;
  }
}

TEST_F(TilesTestSuite, serialization2)
{
    // build a tile
    Tiles original("terrainName", 1);
    UnitDatabase::getUnitDatabase().addUnit(std::make_shared<Unit>("unit1", 1, 2, 3));
    UnitDatabase::getUnitDatabase().addUnit(std::make_shared<Unit>("unit2", 4, 5, 6));
    original.addUnit(UnitDatabase::getUnitDatabase().getUnit("unit1"));
    original.addUnit(UnitDatabase::getUnitDatabase().getUnit("unit2"));

    // serialize it to json
    nlohmann::json json = original;
    //cout << __FUNCTION__ << ":" << __LINE__ << " original=" << json.dump() << endl;

    // clear the global datbase to see if the units get restored
    UnitDatabase::getUnitDatabase().clear();
    // verify that there is nothing in the database
    EXPECT_EQ(UnitDatabase::getUnitDatabase().getUnit("unit1"), nullptr);

    // deserialize from json
    Tiles copy;
    json.get_to(copy);

    // verify that there is something in the database
    EXPECT_NE(UnitDatabase::getUnitDatabase().getUnit("unit1"), nullptr);
    EXPECT_NE(UnitDatabase::getUnitDatabase().getUnit("unit2"), nullptr);

    // verify that the copy matches the original
    EXPECT_EQ(original.getTerrain().getName(), copy.getTerrain().getName());
    EXPECT_EQ(original.getUnits().size(), copy.getUnits().size());

    auto origUnits = original.getUnits();
    auto copyUnits = copy.getUnits();

    auto i = origUnits.begin();
    auto j = copyUnits.begin();
    while (i != origUnits.end() && j != copyUnits.end())
    {        
        // grab temporary pointers to both i and j
        Unit* tempI = (*i).get();
        Unit* tempJ = (*j).get();

        // compare the pointers' contents one by one instead of the pointers themselves
        EXPECT_EQ(tempI->getID(), tempJ->getID());
        EXPECT_EQ(tempI->isActive(), tempJ->isActive());
        EXPECT_EQ(tempI->getMovement(), tempJ->getMovement());
        EXPECT_EQ(tempI->getAttackPower(), tempJ->getAttackPower());
        EXPECT_EQ(tempI->getDefensePower(), tempJ->getDefensePower());

        // advance to the next units
        ++i;
        ++j;
    }
}