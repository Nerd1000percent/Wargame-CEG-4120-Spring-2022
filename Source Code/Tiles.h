//Create a class Tiles
#ifndef Tiles.h
#define Tiles.h
#pragma once
#include<string>
#include<iostream>
using namespace std;
class Terrain {
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

};
#endif
