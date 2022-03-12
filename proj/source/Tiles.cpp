///Implementation of Tiles
#include "Tiles.h"
#include "Unit.h"
#include "Map.h"
#include "UnitDatabase.h"
#include <algorithm> // what makes this needed?
#include <iostream>
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
  return m_units;
}

void Tiles::setTerrain(const Terrain& terrain)
{
  m_terrain = terrain;
}

void Tiles::setUnits(const std::list<std::shared_ptr<Unit>>& units)
{
  m_units = units;
}

//test
//functions data types to be changed accordingly.
void Tiles::addUnit(std::string id, int numMoves, int attackPower, int defensePower) {
  //place new unit on the map
  m_units.push_front(std::make_shared<Unit>(id, numMoves, attackPower, defensePower));
}

//Overloaded funtion for the pointer const in the Unit class. 
void Tiles::addUnit(std::shared_ptr<Unit> New) {
  m_units.push_front(New);
}

void Tiles::removeUnit(std::shared_ptr<Unit> Remove) {

  //TODO

}
void Tiles::listUnit() {
  for (auto const& i : m_units) {
    std::cout << i << std::endl; //I don't know why this is erroring
  }// this all views the list in linear form, changes to come later.
}
//searchs the list of Units loking for element
// Unit Tiles::findUnit(Unit find){ //Im not sue how to get the ID at this point, might need defualt const in Unit.cpp so we can access geId
//    std::list<Unit>::iterator it;
//   it = std::find (allOfUnitClasses.begin(), allOfUnitClasses.end(), find);
//     if (it != allOfUnitClasses.end()){
//        return find;
//     }else{
//         return NULL;
//     }
// }

std::shared_ptr<Unit> Tiles::findUnit(string find) {
  for (auto it : m_units)
    if (it->getID().compare(find)) return it;
  return nullptr; //returning NULL if not found so that Map can know
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
  // for debugging
  //std::cout << __FUNCTION__ << ":" << __LINE__ << " " << j.dump() << std::endl;

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
      unitList.push_back(pUnit);
    }
  }
  t.setUnits(unitList);
}

