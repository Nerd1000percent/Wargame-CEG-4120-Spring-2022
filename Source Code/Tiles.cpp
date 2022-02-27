///Implementation of Tiles
#include "Tiles.h"
#include "Unit.h"
#include "Map.h"
//Constructor
Tiles::Tiles() {
   this->terrainClass;
   this->allOfUnitClasses;
}
//Getters, data types are to be changed
 Terrain Tiles::terrainClassGetter () {
   return terrainClass;
}

list<Unit> Tiles::allOfUnitClassesGetter () {
   return allOfUnitClasses;
}
//test
//functions data types to be changed accordingly.
 void Tiles::addUnit(std::string id, int numMoves, int attackPower, int defensePower) { 
   //place new unit on the map
   allOfUnitClasses.push_front(Unit(id,numMoves,attackPower,defensePower));
   
}
//Overloaded funtion for the pointer const in the Unit class. 
 void Tiles::addUnit(Unit &New) { 
    

   Unit(&New); // I think this is how you call the pointer constrctor in the Unit class,.

}

void Tiles::removeUnit(Unit &Remove){

   allOfUnitClasses.remove(Remove);


}