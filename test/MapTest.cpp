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

// test the size function of the map class
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

// test that the contents of a Map object can be written and read from JSON
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

// test that the moveUnit does nothing and returns false when given incorrect source coordinates
TEST_F(BattleMapTestSuite, badSourceCoords)
{
    nlohmann::json j = *pMap;
    std::cout << j.dump() << std::endl;

    // check the tile where the "weak" unit is really located before the move attempt
    Tiles& realSource = pMap->getTile({ 1, 1 });
    auto realSourceUnits = realSource.getUnits();
    EXPECT_EQ(realSourceUnits.size(), 1);

    // check the fake source tile to make sure it's empty
    Tiles& fakeSource = pMap->getTile({ 2, 0 });
    auto fakeSourceUnits = fakeSource.getUnits();
    EXPECT_EQ(fakeSourceUnits.size(), 0);

    // check the destination tile before the move to make sure it is empty
    Tiles& destTile = pMap->getTile({ 1, 0 });
    auto destTileUnits = destTile.getUnits();
    EXPECT_EQ(destTileUnits.size(), 0);

    // check whether the "weak" unit was successfully moved
    bool success = pMap->moveUnit("weak", { 2, 0 }, { 1, 0 });
    EXPECT_EQ(success, false);

    // check whether the unit is still on the original tile
    realSourceUnits = realSource.getUnits();
    EXPECT_EQ(realSourceUnits.size(), 1);

    // check that the fake source tile is still empty
    fakeSourceUnits = fakeSource.getUnits();
    EXPECT_EQ(fakeSourceUnits.size(), 0);

    // check that the destination tile is still empty
    destTileUnits = destTile.getUnits();
    EXPECT_EQ(destTileUnits.size(), 0);
}

// test that the moveUnit function moves a unit and returns true when moving to an adjacent, neutral tile
TEST_F(BattleMapTestSuite, moveAway)
{
    nlohmann::json j = *pMap;
    //std::cout << j.dump() << std::endl;

    // check the source tile where the "weak" unit is located before the move to make sure it's there
    Tiles& sourceTile = pMap->getTile({ 1, 1 });
    auto sourceTileUnits = sourceTile.getUnits();
    EXPECT_EQ(sourceTileUnits.size(), 1);

    // check the destination tile before the move to make sure it is empty
    Tiles& destTile = pMap->getTile({ 1, 0 });
    auto destTileUnits = destTile.getUnits();
    EXPECT_EQ(destTileUnits.size(), 0);

    // check whether the "weak" unit was successfully moved
    bool success = pMap->moveUnit("weak", { 1, 1 }, { 1, 0 });
    EXPECT_EQ(success, true);

    // check the source tile after the move to make sure the "weak" unit is gone
    sourceTileUnits = sourceTile.getUnits();
    EXPECT_EQ(sourceTileUnits.size(), 0);

    // check the destination tile after the move to make sure the "weak" unit is there
    destTileUnits = destTile.getUnits();
    EXPECT_EQ(destTileUnits.size(), 1);
}

// test that the moveUnit function does nothing and returns false when a unit tries to move more than it has movement points for
TEST_F(BattleMapTestSuite, moveTwice)
{
    nlohmann::json j = *pMap;
    //std::cout << j.dump() << std::endl;

    // check aTile where the "weak" unit is located before the move to make sure it's there
    Tiles& aTile = pMap->getTile({ 1, 1 });
    auto aTileUnits = aTile.getUnits();
    EXPECT_EQ(aTileUnits.size(), 1);

    // check bTile before the move to make sure it is empty
    Tiles& bTile = pMap->getTile({ 1, 0 });
    auto bTileUnits = bTile.getUnits();
    EXPECT_EQ(bTileUnits.size(), 0);

    // check whether the "weak" unit was successfully moved from aTile to bTile
    bool success = pMap->moveUnit("weak", { 1, 1 }, { 1, 0 });
    EXPECT_EQ(success, true);

    // check aTile after the move to make sure the "weak" unit is gone
    aTileUnits = aTile.getUnits();
    EXPECT_EQ(aTileUnits.size(), 0);

    // check bTile after the move to make sure the "weak" unit is there
    bTileUnits = bTile.getUnits();
    EXPECT_EQ(bTileUnits.size(), 1);

    // attempt to move from bTile to aTile with no moves left
    success = pMap->moveUnit("weak", { 1, 0 }, { 1, 1 });
    EXPECT_EQ(success, false);
    
    // check aTile after the move attempt to make sure the "weak" unit did not move to it
    aTileUnits = aTile.getUnits();
    EXPECT_EQ(aTileUnits.size(), 0);

    // check bTile after the move attempt to make sure the "weak" unit is still there
    bTileUnits = bTile.getUnits();
    EXPECT_EQ(bTileUnits.size(), 1);
}

// test that the moveUnit function does nothing and returns false if a unit tries to move more than one tile at a time
TEST_F(BattleMapTestSuite, moveMultipleTiles)
{
    nlohmann::json j = *pMap;
    //std::cout << j.dump() << std::endl;

    // check the source tile where the "weak" unit is located before the move to make sure it's there
    Tiles& sourceTile = pMap->getTile({ 1, 1 });
    auto sourceTileUnits = sourceTile.getUnits();
    EXPECT_EQ(sourceTileUnits.size(), 1);

    // check the destination tile before the move to make sure it is empty
    Tiles& destTile = pMap->getTile({ 2, 2 });
    auto destTileUnits = destTile.getUnits();
    EXPECT_EQ(destTileUnits.size(), 0);

    // check whether the "weak" unit was successfully moved
    bool success = pMap->moveUnit("weak", { 1, 1 }, { 2, 2 });
    EXPECT_EQ(success, false);

    // check the source tile after the move to make sure the "weak" unit is still there
    sourceTileUnits = sourceTile.getUnits();
    EXPECT_EQ(sourceTileUnits.size(), 1);

    // check the destination tile after the move to make sure it's still empty
    destTileUnits = destTile.getUnits();
    EXPECT_EQ(destTileUnits.size(), 0);
}

// test that the moveUnit function removes a unit from the Map if it dies while attacking an enemy-occupied tile
TEST_F(BattleMapTestSuite, dieFighting)
{
    nlohmann::json j = *pMap;
    //std::cout << j.dump() << std::endl;

    // check the source tile where the "weak" unit is located before the move to make sure it's there
    Tiles& sourceTile = pMap->getTile({ 1, 1 });
    auto sourceTileUnits = sourceTile.getUnits();
    EXPECT_EQ(sourceTileUnits.size(), 1);

    // check the destination tile where the "strong" unit is located before the move to make sure it's there
    Tiles& destTile = pMap->getTile({ 1, 2 });
    auto destTileUnits = destTile.getUnits();
    EXPECT_EQ(destTileUnits.size(), 1);

    // check whether the "weak" unit was successfully moved
    bool success = pMap->moveUnit("weak", { 1, 1 }, { 1, 2 });
    EXPECT_EQ(success, false);

    // check the source tile after the move to make sure the "weak" unit is now dead
    sourceTileUnits = sourceTile.getUnits();
    EXPECT_EQ(sourceTileUnits.size(), 0);

    // check the destination tile after the move to make sure the "strong" unit is still there
    destTileUnits = destTile.getUnits();
    EXPECT_EQ(destTileUnits.size(), 1);
}

// test that the moveUnit function moves a unit if it defeats an enemy unit occupying its destination
TEST_F(BattleMapTestSuite, killAndReplace)
{
    nlohmann::json j = *pMap;
    //std::cout << j.dump() << std::endl;

    // check the source tile where the "strong" unit is located before the move to make sure it's there
    Tiles& sourceTile = pMap->getTile({ 1, 2 });
    auto sourceTileUnits = sourceTile.getUnits();
    EXPECT_EQ(sourceTileUnits.size(), 1);

    // check the destination tile where the "weak" unit is located before the move to make sure it's there
    Tiles& destinationTile = pMap->getTile({ 1, 1 });
    auto destinationTileUnits = sourceTile.getUnits();
    EXPECT_EQ(destinationTileUnits.size(), 1);

    // check whether the "strong" unit was successfully moved
    bool success = pMap->moveUnit("strong", { 1, 2 }, { 1, 1 });
    EXPECT_EQ(success, true);

    // check the source tile where the "strong" unit started and confirm that it is no longer there
    sourceTileUnits = sourceTile.getUnits();
    EXPECT_EQ(sourceTileUnits.size(), 0);

    // check the destination tile where the "weak" unit started and confirm that only one unit is there
    destinationTileUnits = destinationTile.getUnits();
    EXPECT_EQ(destinationTileUnits.size(), 1);
}

