#ifndef UNIT-H
#define UNIT-H
#pragma once

#include <string>

class Unit
{

private:

   std::string m_ID;
   bool m_active;
   int m_numMoves;
   double m_attackPower;
   double m_defensePower;

public:
   
   Unit(std::string id, int numMoves, int attackPower, int defensePower);

   std::string getID():
   bool isActive();
   int getMovement();
   double getAttackPower();
   double getDefensePower();

   void dealDamage(double damage);

};
#endif