#include "Terrain.h"

using namespace std;

Terrain::Terrain() {
   this->name = "";
   this->movementCost = 0;
}

Terrain::Terrain(string name, int cost) {
   this->name = name;
   this->movementCost = cost;
}
//Getter
string Terrain::nameGetter () {
   return name;
}
int Terrain::movementCostGetter() {
   return movementCost;
}

void Terrain::printTerrain() {
   cout << "\nName: " << name;
   cout << "\nMovement Cost: " << movementCost; 
}