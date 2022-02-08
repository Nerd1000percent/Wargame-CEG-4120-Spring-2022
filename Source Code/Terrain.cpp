///Implementation of Terrain
#include "Terrain.h"
//Constructor
Terrain::Terrain() {
   this->name = "";
   this-> movementCost= 0;
}
//Getter
string Terrain::nameGetter () {
   return name;
}
int Terrain::movementCostGetter() {
   return movementCost;
}


