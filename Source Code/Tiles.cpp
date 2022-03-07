///Implementation of Tiles
#include "Tiles.h"
#include "Unit.h"
#include "Map.h"
#include <algorithm> // what makes this needed?
#include <iostream>
//Constructor
Tiles::Tiles() {
   this->terrainClass;
   this->allOfUnitClasses;
}

Tiles::Tiles(string terrainName, int terrainCost) {
   this->terrainClass = Terrain(terrainName, terrainCost);
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
   Unit(*New); // I think this is how you call the pointer constrctor in the Unit class,
               //I will look into this and further change it. 
}

void Tiles::removeUnit(Unit &Remove){

   allOfUnitClasses.remove(Remove); //this is just an Idea, we will have to have over loaded 
                                    //functions to remove the unit just like how we added it.


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

Unit* Tiles::findUnit(string find){
   for (auto it : allOfUnitClasses)
      if (it.getID().compare(find)) return &it;
   return NULL; //returning NULL if not found so that Map can know
}
