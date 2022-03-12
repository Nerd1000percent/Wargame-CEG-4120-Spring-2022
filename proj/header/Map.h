//Create a class Map
#ifndef MAP_H
#define MAP_H

#include "Unit.h"
#include "Tiles.h"
#include "Coordinates.h"
#include "HyperArray.hpp"
#include "nlohmann/json.hpp"

#include<list>
#include<string>
#include<iostream>
#include<vector>

using namespace std;
class Map {
  //Attributes
private:
  HyperArray<Tiles> m_arrayOfTiles;
  //Member functions
public:

  // serializers
  friend void to_json(nlohmann::json& j, const Map& m);
  friend void from_json(const nlohmann::json& j, Map& m);
    
  //Constructor
  Map(size_t dim);
  // don't need this constructor
  Map() = delete;

  //Getters
  HyperArray<Tiles>& arrayOfTilesGetter();
  void saveState(istream log);
  int moveUnit(string unitId, int locCoords[2], int destinationCoords[2]);
  void addTile(string terrainName, int terrainCost, size_t xCoord, size_t yCoord);
  void saveGameState();
  //TODO void resolveCombat();
  list<Coordinates> getEngagedUnits();
private:
  bool hostileCheck(int coords[2]);
  bool checkPath(Unit* unit, int locCoords[2], int destinationCoords[2]);
};

#endif
