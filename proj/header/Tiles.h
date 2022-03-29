#ifndef TILES_H
#define TILES_H

#include "Terrain.h"
#include "nlohmann/json.hpp"

#include <string>
#include <memory>
#include <list>
#include <map>

class Unit;
class Terrain;

class Tiles {
  //Attributes
private:
  Terrain m_terrain;
  std::map<std::string, std::shared_ptr<Unit>> m_units;
  std::string m_team;
  bool m_victoryPoint;
  //Member functions
public:
  //Constructor
  Tiles();
  Tiles(std::string terrainName, int terrainCost);

  //Getters
  Terrain getTerrain() const;
  std::list<std::shared_ptr<Unit>> getUnits() const;

  void setTerrain(const Terrain& terrain);
  void setUnits(const std::list<std::shared_ptr<Unit>>& units);

  void setTeam(std::string team);
  std::string getTeam() const;

  void setVictoryPoint(bool victoryPoint);
  bool getVictoryPoint() const;

  //functions
  void addUnit(std::string id, std::string team, int numMoves, int attackPower, int defensePower);
  void addUnit(std::shared_ptr<Unit> unit);
  void removeUnit(std::shared_ptr<Unit> unit);
  std::shared_ptr<Unit> findUnit(std::string id); // return pointer of a given unitid
};

void to_json(nlohmann::json& j, const Tiles& t);
void from_json(const nlohmann::json& j, Tiles& t);

#endif
