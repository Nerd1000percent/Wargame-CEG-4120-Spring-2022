#ifndef UNIT_H
#define UNIT_H

#include <string>
#include <vector>
#include <memory>

class Unit
{
private:

   std::string m_ID;
   bool m_active;
   int m_numMoves;
   int m_currentMoves; // To decrease as a unit moves around the map
   double m_attackPower;
   double m_defensePower;
public:
   
   Unit(std::string id, int numMoves, int attackPower, int defensePower);
   Unit(Unit& other);

   std::string getID();
   bool isActive();
   int getMovement();
   int getCurrentMovement();
   double getAttackPower();
   double getDefensePower();

   void dealDamage(double damage);
   void spendMovement(int cost);
   void printUnit();
   void resetMovement();
};
#endif