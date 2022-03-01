//Create a class Tiles
#ifndef TILES-H
#define TILES-H
#pragma once
#include "Unit.h"
#include "Terrain.h"
#include<string>
#include<iostream>
using namespace std;
class Tiles {
//Attributes
private:
   Terrain terrainClass;
   std::list<Unit> allOfUnitClasses;
//Member functions
public:
   //Constructor
   Tiles();

   //Getters
   Terrain terrainClassGetter();
   list<Unit> allOfUnitClassesGetter();

   //functions
   void addUnit(std::string id, int numMoves, int attackPower, int defensePower);
   void addUnit(Unit &New);
   void removeUnit(Unit &Remove);
   Unit findUnit(int find); // return pointer of a given unitid
   void listUnit();
};
#endif
