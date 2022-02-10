//Create a class Map
#ifndef MAP-H
#define MAP-H
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