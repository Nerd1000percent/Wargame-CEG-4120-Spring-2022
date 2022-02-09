//Create a class Map
#ifndef Map.h
#define Map.h
#pragma once
#include<string>
#include<iostream>
using namespace std;
class Map {
//Attributes
private:
   int arrayOfTiles[][];
   int mapDimension;
//Member functions
public:
   //Constructor
   Map();
   //Getters
   int arrayOfTilesGetter();

};
#endif