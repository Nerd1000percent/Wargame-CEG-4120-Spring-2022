#include "gtest/gtest.h"
#include <iostream>
#include <string>
#include <memory>

#include "Map.h"

#include <memory>
using namespace std;

class MapTestSuite : public testing::Test
{
public:
  // Override this to define how to set up the environment.
  void SetUp() override {
    
  }

  // Override this to define how to tear down the environment.
  void TearDown() override {
    
  }
};

TEST_F(MapTestSuite, firstTest)
{

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

  cout << j.dump() << endl;

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