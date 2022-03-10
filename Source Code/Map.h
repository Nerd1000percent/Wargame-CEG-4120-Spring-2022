//Create a class Map
#ifndef MAP-H
#define MAP-H
#pragma once
#include "Unit.h"
#include "Tiles.h"
#include"Coordinates.h"
#include<list>
#include<string>
#include<iostream>
class Map {
//Attributes
private:
   Tiles arrayOfTiles[][];
   auto mapDimension;
   list<Coordinates> engagedUnits;
//Member functions
public:
   //Constructor
   Map();
   Map(const Map clone);
   //Getters
   int arrayOfTilesGetter();
   void saveState(istream log);
   void moveUnit(string unitId, auto locCoords[2], auto destinationCoords[2]);
   //TODO void resolveCombat();
   list<Coordinates> getEngagedUnits();
private:
	bool hostileCheck(int coords[2]);
	bool checkPath(Unit* unit, int locCoords[2], int destinationCoords[2]);
};
#endif