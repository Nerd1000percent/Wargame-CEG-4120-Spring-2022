//Create a class Terrain
#ifndef TERRAIN-H
#define TERRAIN-H
#pragma once
#include<string>
#include<iostream>
using namespace std;
class Terrain {
//Attributes
private:
   string name;
   int movementCost;
//Member functions
public:
   //Constructor
   Terrain();
   Terrain(string name, int movementCost);
   //Getters
   string nameGetter();
   int movementCostGetter();

};
#endif