#include "Terrain.h"

#include <iostream>
using namespace std;

Terrain::Terrain() {

}

Terrain::Terrain(string name, int cost) {
   m_name = name;
   m_movementCost = cost;
}
//Getter
string Terrain::getName() const {
   return m_name;
}
int Terrain::getMovementCost() const {
   return m_movementCost;
}

void Terrain::setName(std::string name)
{
  m_name = name;
}

void Terrain::setMovementCost(int movementCost)
{
  m_movementCost = movementCost;
}

void Terrain::printTerrain() {
   cout << "\nName: " << m_name;
   cout << "\nMovement Cost: " << m_movementCost;
}

void to_json(nlohmann::json& j, const Terrain& t)
{
  /*
  std::string name;
  int movementCost;
  */
  j["name"] = t.getName();
  j["movement"] = t.getMovementCost();
}

void from_json(const nlohmann::json& j, Terrain& t)
{
    std::string name;
    j["name"].get_to(name);
    t.setName(name);

    int movementCost = 0;
    j["movement"].get_to(movementCost);
    t.setMovementCost(movementCost);
    
}
