//Create a class Map
#ifndef MAP-H
#define MAP-H
#pragma once
#include "Unit.h"
#include "Tiles.h"
#include<list>
#include<string>
#include<iostream>
using namespace std;
class Map {
//Attributes
private:
   Tiles arrayOfTiles[][];
   int mapDimension;
   list<Unit*> engagedUnits;
//Member functions
public:
   //Constructor
   Map();
   Map(const Map clone);
   //Getters
   int arrayOfTilesGetter();
   void saveState(istream log);
   void moveUnit(string unitId, int locCoords[2], int destinationCoords[2]);
   //TODO void resolveCombat();
   void findEngagedUnits();
private:
	bool hostileCheck(int coords[2]);
	bool checkPath(Unit* unit, int locCoords[2], int destinationCoords[2]);
};
#endif