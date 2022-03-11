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
   double m_attackPower;
   double m_defensePower;
   int m_currentMoves; // To decrease as a unit moves around the map
   std::vector<std::shared_ptr<Unit>> m_engagementList;
public:
   
   Unit(std::string id, int numMoves, int attackPower, int defensePower);
   Unit(Unit& other);
   Unit(Unit& destroyedUnit, bool active);

   std::string getID();
   bool isActive();
   int getMovement();
   double getAttackPower();
   double getDefensePower();
   int getCurrentMovement();

   void dealDamage(double damage);
   void engageUnit(std::unique_ptr<Unit> enemy);
   void disengageUnit(std::string unitID);
   void spendMovement(int cost);
   void printUnit();
   void resetMovement();
};
#endif