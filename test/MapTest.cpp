#include "gtest/gtest.h"
#include <iostream>
#include <string>
#include <memory>

#include "Coordinates.h"
#include "Map.h"
#include "Unit.h"
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
  }

  // Override this to define how to tear down the environment.
  void TearDown() override {
    UnitDatabase::getUnitDatabase().clear();
  }
};

class BattleMapTestSuite : public testing::Test
{
public:
  // Override this to define how to set up the environment.
  void SetUp() override {

    // clear database
    UnitDatabase::getUnitDatabase().clear();
    UnitDatabase::getUnitDatabase().addUnit(make_shared<Unit>("weak", "losers", 1, 1.0, 1.0));
    UnitDatabase::getUnitDatabase().addUnit(make_shared<Unit>("strong", "winners", 1, 10, 10));

    /*
       1 1 1 1
       1 w s 1
       1 1 1 1
    */
    Terrain desert{"desert", 1};
    pMap = std::make_shared<Map>(Coordinates{ 3, 4 });
    for(size_t r = 0; r<pMap->size().getRow(); r++)
      for (size_t c = 0; c < pMap->size().getColumn(); c++)
      {
        auto& tile = pMap->getTile({r, c});
        tile.setTerrain(desert);
      }
    pMap->getTile({ 1, 1 }).addUnit(UnitDatabase::getUnitDatabase().getUnit("weak"));
    pMap->getTile({ 1, 2 }).addUnit(UnitDatabase::getUnitDatabase().getUnit("strong"));
  }

  // Override this to define how to tear down the environment.
  void TearDown() override {
    pMap.reset();
    UnitDatabase::getUnitDatabase().clear();
  }

  std::shared_ptr<Map> pMap;
};

TEST_F(MapTestSuite, testSize)
{
    // make a map
    Coordinates dimensions{ 2, 4 };
    Map map(dimensions);

    // populate the map
    for (size_t row = 0; row < dimensions.getRow(); row++)
    {
        for (size_t col = 0; col < dimensions.getColumn(); col++)
        {
            auto& tile = map.getTile({ row, col });
            std::string name = "(" + std::to_string(row) + ", " + std::to_string(col) + ")";
            int cost = dimensions.getColumn() * row + col;
            tile.setTerrain({ name, cost });
        }
    }

    // check that the map dimensions are correct
    EXPECT_EQ(map.size().getColumn(), dimensions.getColumn());
    EXPECT_EQ(map.size().getRow(), dimensions.getRow());
}

TEST_F(MapTestSuite, testMovement)
{
    // make a map
    Coordinates dimensions{ 3, 5 };
    Map map(dimensions);

    // populate the map with tiles
    for (size_t row = 0; row < dimensions.getRow(); row++)
    {
        for (size_t col = 0; col < dimensions.getColumn(); col++)
        {
            auto& tile = map.getTile({ row, col });
            std::string name = "(" + std::to_string(row) + ", " + std::to_string(col) + ")";
            int cost = dimensions.getColumn() * row + col;
            tile.setTerrain({ name, cost });
        }
    }

    //// put a unit on the start tile
    Tiles& startTile = map.getTile({ 0, 0 });
    //UnitDatabase::getUnitDatabase().addUnit(std::make_shared<Unit>("test_unit", "team", 1, 2, 3));
    //startTile.addUnit(UnitDatabase::getUnitDatabase().getUnit("test_unit"));
    
    //// make sure the start tile has the unit and the destination tile is empty before moving the unit
    //auto startTileUnits = startTile.getUnits();
    //auto i = startTileUnits.begin();

    //// make sure that the start tile is empty and the destination tile has the unit after movement
    //map.moveUnit("test_unit", { 0, 0 }, { 0, 1 });
    //Tiles& destTile = map.getTile({ 0, 1 });
}

TEST_F(MapTestSuite, serializationTest)
{
  // make a map
  Coordinates dimensions{ 3, 5 };
  Map orig(dimensions);
  
  // populate the map
  for (size_t row = 0; row < dimensions.getRow(); row++)
  {
    for (size_t col = 0; col < dimensions.getColumn(); col++)
    {
      auto& tile = orig.getTile({ row, col });
      std::string name = "(" + std::to_string(row) + ", " + std::to_string(col) + ")";
      int cost = dimensions.getColumn() * row + col;
      tile.setTerrain({ name, cost });
    }
  }  

  // serialize the map
  nlohmann::json j = orig;

  //cout << j.dump() << endl;

  // deserialze the map
  Map copy({ 0, 0 });
  j.get_to(copy);

  // check results
  for (size_t row = 0; row < dimensions.getRow(); row++)
  {
    for (size_t col = 0; col < dimensions.getColumn(); col++)
    {
      auto& origTile = orig.getTile({ row, col });
      auto& copyTile = copy.getTile({ row, col });

      auto origTerrain = origTile.getTerrain();
      auto copyTerrain = copyTile.getTerrain();

      EXPECT_EQ(origTerrain.getMovementCost(), copyTerrain.getMovementCost());
      EXPECT_EQ(origTerrain.getName(), copyTerrain.getName());
    }
  }
}

TEST_F(BattleMapTestSuite, moveAway)
{
  nlohmann::json j = *pMap;
  std::cout << j.dump() << std::endl;

  Tiles& sourceTile = pMap->getTile({ 1, 1 });
  Tiles& destTile = pMap->getTile({ 1, 0 });

  auto sourceTileUnits = sourceTile.getUnits();
  EXPECT_EQ(sourceTileUnits.size(), 1);

  auto destTileUnits = destTile.getUnits();
  EXPECT_EQ(destTileUnits.size(), 0);

  bool success = pMap->moveUnit("weak", { 1, 1 }, { 1, 0 });
  EXPECT_EQ(success, true);

  sourceTileUnits = sourceTile.getUnits();
  destTileUnits = destTile.getUnits();

  EXPECT_EQ(sourceTileUnits.size(), 0);
  //EXPECT_EQ(destTileUnits.size(), 1);
}
