//Create a class Tiles
#ifndef TILES_H
#define TILES_H

#include <string>
#include <iostream>
#include <list>

#include "Unit.h"
#include "Terrain.h"

class Tiles {
//Attributes
private:
   Terrain terrainClass;
   std::list<Unit> allOfUnitClasses;
//Member functions
public:
   //Constructor
   Tiles();
   Tiles(std::string terrainName, int terrainCost);

   //Getters
   Terrain terrainClassGetter();
   std::list<Unit> allOfUnitClassesGetter();

   //functions
   void addUnit(std::string id, int numMoves, int attackPower, int defensePower);
   void addUnit(Unit &New);
   void removeUnit(Unit &Remove);
   Unit* findUnit(std::string find); // return pointer of a given unitid
   void listUnit();
};
#endif
