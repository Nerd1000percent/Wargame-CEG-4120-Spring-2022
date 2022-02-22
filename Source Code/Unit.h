#ifndef UNIT-H
#define UNIT-H
#pragma once

#include <string>
#include <vector>
#include <memory>

class Unit
{

private:

   std::string m_ID;
   bool m_active;
   int m_numMoves;
   double m_attackPower;
   double m_defensePower;
   std::vector<std::unique_ptr<Unit>> m_engagementList;

public:
   
   Unit(std::string id, int numMoves, int attackPower, int defensePower);
   Unit(Unit& other);

   std::string getID():
   bool isActive();
   int getMovement();
   double getAttackPower();
   double getDefensePower();

   void dealDamage(double damage);
   void engageUnit(std::unique_ptr<Unit> enemy);
   void disengageUnit(std::string unitID);

};
#endif