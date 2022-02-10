//Create a class Unit
#ifndef UNIT-H
#define UNIT-H
#pragma once
#include<string>
#include<iostream>
using namespace std;
class Unit {
//Attributes
private:
   int attackPower;
   int defensePower;
   int movement;
   int id;
   int activeFlag;

//Member functions
public:
   //Constructor
   Unit();

   //Getters
   int attackPowerGetter();
   int defensePowerGetter();
   int movementGetter();
   int idGetter():
   int activeFlagGetter();

   //functions
   int decreaseDefensePower();
   int decreaseAttackPower();

};
#endif