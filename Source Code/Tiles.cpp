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
 void Tiles::addUnit(std::string id, int numMoves, int attackPower, int defensePower) { 
   //place new unit on the map
    Unit(id,numMoves,attackPower,defensePower);

   
}
//Overloaded funtion for the pointer const in the Unit class. 
 void Tiles::addUnit(Unit &New) { 
    

   Unit(&New); // I think this is how you call the pointer constrctor in the Unit class.

}

void Tiles::removeUnit(){



}