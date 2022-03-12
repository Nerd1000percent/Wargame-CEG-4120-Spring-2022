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

//test
//functions data types to be changed accordingly.
void Tiles::addUnit(std::string id, int numMoves, int attackPower, int defensePower) {
  //place new unit on the map
  auto u = UnitDatabase::getUnitDatabase().getUnit(id);
  if (u)
    throw std::runtime_error("unit " + id + " already exists");
  u = std::make_shared<Unit>(id, numMoves, attackPower, defensePower);
  m_units[id] = u;
}

//Overloaded funtion for the pointer const in the Unit class. 
void Tiles::addUnit(std::shared_ptr<Unit> unit) {
  m_units[unit->getID()] = unit;
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

void to_json(nlohmann::json& j, const Tiles& t)
{
  j["terrain"] = t.getTerrain();
  j["units"] = std::vector<Unit>();
  
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

