///Implementation of Tiles
#include "Tiles.h"
#include "Unit.h"
#include "Map.h"
#include "UnitDatabase.h"
#include <algorithm> // what makes this needed?
#include <iostream>
#include <exception>

//Constructor
Tiles::Tiles() {
  this->m_terrain;
  this->m_units;
  this->m_victoryPoint;
}

Tiles::Tiles(string terrainName, int terrainCost) {
  m_terrain = Terrain(terrainName, terrainCost);
}

//Getters, data types are to be changed
Terrain Tiles::getTerrain() const {
  return m_terrain;
}

std::list<std::shared_ptr<Unit>> Tiles::getUnits() const {
  std::list<std::shared_ptr<Unit>> units;
  for (auto u : m_units)
    units.push_back(u.second);
  return units;
}

void Tiles::setTerrain(const Terrain& terrain)
{
  m_terrain = terrain;
}

void Tiles::setUnits(const std::list<std::shared_ptr<Unit>>& units)
{
  m_units.clear();
  for (auto u : units)
    m_units[u->getID()] = u;
}

//functions data types to be changed accordingly.
void Tiles::addUnit(std::string id, std::string team, int numMoves, int attackPower, int defensePower) {
  //place new unit on the map
  auto u = UnitDatabase::getUnitDatabase().getUnit(id);
  if (u)
    throw std::runtime_error("unit " + id + " already exists");
  u = std::make_shared<Unit>(id, team, numMoves, attackPower, defensePower);
  addUnit(u);
}

//Overloaded funtion for the pointer const in the Unit class. 
void Tiles::addUnit(std::shared_ptr<Unit> unit) {
  m_units[unit->getID()] = unit;
  m_team = unit->getTeam();
}

void Tiles::removeUnit(std::shared_ptr<Unit> unit) {
  if (m_units.count(unit->getID()))
  {
    m_units.erase(unit->getID());
  }
}

std::shared_ptr<Unit> Tiles::findUnit(string id) {
  if (m_units.count(id))
  {
    return m_units[id];
  }
  return nullptr;
}

void Tiles::setTeam(std::string team)
{
  m_team = team;
}

std::string Tiles::getTeam() const
{
  return m_team;
}

//Done by Ahmed, VictoryPont setter
void Tiles::setVictoryPoint(bool victoryPoint){
 m_victoryPoint=victoryPoint;
}
//Done by Ahmed, VictoryPont getter
bool Tiles::getVictoryPoint() const
{
  return m_victoryPoint; 
}

void to_json(nlohmann::json& j, const Tiles& t)
{
  j["terrain"] = t.getTerrain();
  j["team"] = t.getTeam();  
  j["units"] = std::vector<Unit>();
  //done by Ahmed
  j["victory_point"] = t.getVictoryPoint();
  for (auto& u : t.getUnits())
  {
    j["units"].push_back(*u);
  }
}

void from_json(const nlohmann::json& j, Tiles& t)
{
  Terrain terrain;
  j["terrain"].get_to(terrain);
  t.setTerrain(terrain);

  std::string team;
  j["team"].get_to(team);
  t.setTeam(team);

//done by Ahmed, reading victory Point from Json
  bool vicPoint;
  j["victory_point"].get_to(vicPoint);
  t.setVictoryPoint(vicPoint);

  // clear the units
  t.setUnits({});
  std::vector<Unit> units;
  j["units"].get_to(units);
  std::list<std::shared_ptr<Unit>> unitList;

  for (auto unit : units)
  {
    // check the global database to see if we already have this unit
    auto pUnit = UnitDatabase::getUnitDatabase().getUnit(unit.getID());
    if (!pUnit)
    {
      // make a new unit and put it in the database
      pUnit = std::make_shared<Unit>(unit);
      UnitDatabase::getUnitDatabase().addUnit(pUnit);
    }
    unitList.push_back(pUnit);
  }
  t.setUnits(unitList);
}

