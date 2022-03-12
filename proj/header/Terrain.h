#ifndef TERRAIN_H
#define TERRAIN_H

#include "nlohmann/json.hpp"
#include <string>

class Terrain {

private:
   std::string m_name = "";
   int m_movementCost = 1;

public:
   Terrain();
   Terrain(std::string name, int movementCost);

   std::string getName() const;
   int getMovementCost() const;

   void setName(std::string name);
   void setMovementCost(int movementCost);

   void printTerrain();

};

void to_json(nlohmann::json& j, const Terrain& t);
void from_json(const nlohmann::json& j, Terrain& t);

#endif
