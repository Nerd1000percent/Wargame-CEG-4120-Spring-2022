///Implementation of Tiles
#include "Tiles.h"
#include "Unit.h"
#include "Map.h"
#include "Terrain.h"
#include <algorithm> // what makes this needed?
#include <iostream>
//Constructor
Tiles::Tiles() {
   this->terrainClass;
   this->allOfUnitClasses;
}

Tiles::Tiles(string terrainName, int terrainCost) {
   this->terrainClass = std::make_shared<Terrain>(terrainName, terrainCost);
}

//Getters, data types are to be changed
 std::shared_ptr<Terrain> Tiles::terrainClassGetter () {
   return terrainClass;
}

 std::list<std::shared_ptr<Unit>> Tiles::allOfUnitClassesGetter () {
   return allOfUnitClasses;
}
//test
//functions data types to be changed accordingly.
 void Tiles::addUnit(std::string id, int numMoves, int attackPower, int defensePower) { 
   //place new unit on the map
   allOfUnitClasses.push_front(std::make_shared<Unit>(id,numMoves,attackPower,defensePower));
   
}
//Overloaded funtion for the pointer const in the Unit class. 
 void Tiles::addUnit(std::shared_ptr<Unit> New) { 
   allOfUnitClasses.push_front(New);
}

void Tiles::removeUnit(std::shared_ptr<Unit> Remove){

   //TODO

}
void Tiles::listUnit(){
    for (auto const &i: allOfUnitClasses) {
        std::cout <<i<< std::endl; //I don't know why this is erroring
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

std::shared_ptr<Unit> Tiles::findUnit(string find){
   for (auto it : allOfUnitClasses)
      if (it->getID().compare(find)) return it;
   return nullptr; //returning NULL if not found so that Map can know
}