//Create a class Map
#ifndef MAP_H
#define MAP_H
#pragma once
#include "Unit.h"
#include "Tiles.h"
#include"Coordinates.h"
#include<list>
#include<string>
#include<iostream>
#include<vector>
using namespace std;
class Map {
//Attributes
private:
   int mapDimension;
   vector<vector<Tiles>> arrayOfTiles;
   list<Unit*> engagedUnits;
//Member functions
public:
   //Constructor
   Map();
   Map(const Map* clone);
   Map(int dim);
   //Getters
   vector<vector<Tiles>> arrayOfTilesGetter();
   void saveState(istream log);
   int moveUnit(string unitId, int locCoords[2], int destinationCoords[2]);
   void addTile(string terrainName, int terrainCost, int xCoord, int yCoord);
   void saveGameState();
   //TODO void resolveCombat();
   list<Coordinates> getEngagedUnits();
private:
	bool hostileCheck(int coords[2]);
	bool checkPath(Unit* unit, int locCoords[2], int destinationCoords[2]);
};
#endif