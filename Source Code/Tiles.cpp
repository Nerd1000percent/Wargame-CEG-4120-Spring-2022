///Implementation of Tiles
#include "Tiles.h"
#include "Unit.h"
//Constructor
Tiles::Tiles() {
   this->terrainClass  = 0;
   this->allOfUnitClasses= 0;
}
//Getters, data types are to be changed
int Tiles::terrainClassGetter () {
   return terrainClass;
}

int Tiles::allOfUnitClassesGetter () {
   return allOfUnitClasses;
}
//test
//functions data types to be changed accordingly.
 void Tiles::addUnit() { 
  Unit();
  Unit( " ", 0, 0, 0);
}

void Tiles::removeUnit(){



}