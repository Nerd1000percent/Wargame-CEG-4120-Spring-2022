#ifndef UNIT_H
#define UNIT_H

#include "nlohmann/json.hpp"
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
   
   // need a default constructor for serialization
   Unit() = default;
   Unit(std::string id, int numMoves, int attackPower, int defensePower);
   Unit(Unit& other);
   Unit(Unit& destroyedUnit, bool active);

   std::string getID() const;
   bool isActive() const;
   int getMovement() const;
   double getAttackPower() const;
   double getDefensePower() const;
   int getCurrentMovement();

   void dealDamage(double damage);
   void engageUnit(std::shared_ptr<Unit> enemy);
   void disengageUnit(std::string unitID);
   void spendMovement(int cost);
   void printUnit();
   void resetMovement();
};

// serializers
void to_json(nlohmann::json& j, const Unit& u);
void from_json(const nlohmann::json& j, Unit& u);

#endif