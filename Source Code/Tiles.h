//Create a class Tiles
#ifndef TILES-H
#define TILES-H
#pragma once
#include "Unit.h"
#include<string>
#include<iostream>
using namespace std;
class Tiles {
//Attributes
private:
   int terrainClass;
   int allOfUnitClasses;
//Member functions
public:
   //Constructor
   Tiles();

   //Getters
   int terrainClassGetter();
   int allOfUnitClassesGetter();

   //functions
   void addUnit();
   void removeUnit();
   Unit* findUnit(); // return pointer of a given unitid


};
#endif
