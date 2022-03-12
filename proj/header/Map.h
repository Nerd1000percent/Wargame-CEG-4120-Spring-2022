//Create a class Map
#ifndef MAP_H
#define MAP_H

//#include "Unit.h"
#include "Tiles.h"
#include "Coordinates.h"
#include "HyperArray.hpp"
#include "nlohmann/json.hpp"

//#include <string>
#include <vector>

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
  Map(Coordinates dims);
  // don't need this constructor
  Map() = delete;

  // get the map sizes (row, col)
  Coordinates size();

  Tiles& getTile(Coordinates coords);

  bool moveUnit(std::string unitID, Coordinates source, Coordinates dest);
};

#endif
