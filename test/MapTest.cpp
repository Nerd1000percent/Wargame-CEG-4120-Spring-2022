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
  //pMap->saveGameState();
}