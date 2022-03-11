#ifndef TERRAIN_H
#define TERRAIN_H

#include <string>
#include <iostream>

class Terrain {

private:
   std::string name;
   int movementCost;

public:
   Terrain();
   Terrain(std::string name, int movementCost);

   std::string nameGetter();
   int movementCostGetter();

   void printTerrain();

};

#endif