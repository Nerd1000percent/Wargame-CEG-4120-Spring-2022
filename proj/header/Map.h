//Create a class Map
#ifndef MAP_H
#define MAP_H

//#include "Unit.h"
#include "Tiles.h"
#include "Coordinates.h"
#include "HyperArray.hpp"
#include "nlohmann/json.hpp"

#include <string>
#include <vector>
#include <map>

using namespace std;

class Map {
  //Attributes
private:
  HyperArray<Tiles> m_arrayOfTiles;
  //Member functions
  static const std::string HTML_TEMPLATE;
  static const size_t ROW_HEIGHT = 175;

  typedef std::string(Map::*ReplaceHtmlTags)() const;
  std::string getRowHeightHtml() const;
  std::string getMapJsonHtml() const;
  std::string getTilesHtml() const;
  std::string getColumnsHtml() const;

  const std::map<std::string, ReplaceHtmlTags> HTML_TAGS =
  {
    {"ROW_HEIGHT", &Map::getRowHeightHtml},
    {"MAP_JSON", &Map::getMapJsonHtml},
    {"TILES", &Map::getTilesHtml},
    {"COLUMNS", &Map::getColumnsHtml}
  };

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

  // tries to move the unit one tile.  fights if necessary.  returns
  // true if the end result is the unit on the new tile.
  bool moveUnit(std::string unitID, Coordinates source, Coordinates dest);

  std::string mapToHtml();
};

#endif
