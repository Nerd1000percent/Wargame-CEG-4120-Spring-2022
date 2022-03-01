#include "Unit.h"


Unit::Unit(std::string id, int numMoves, int attackPower, int defensePower)
: m_ID{id}
, m_numMoves{numMoves}
, m_attackPower{attackPower}
, m_defensePower{defensePower}
{
   m_active = true;
   m_engagementList;
}

Unit::Unit(Unit& other)
{
    m_ID = other.getID();
    m_active = other.isActive();
    m_numMoves = other.getMovement();
    m_attackPower = other.getAttackPower();
    m_defensePower = other.getDefensePower();
    m_currentMoves = m_numMoves;
}

std::string Unit::getID()
{
   return m_ID;
}

bool Unit::isActive()
{
   return m_active;
}

int Unit::getMovement()
{
   return m_numMoves;
}

double Unit::getAttackPower ()
{
   return m_attackPower;
}

double Unit::getDefensePower()
{
   return m_defensePower;
}

// If this unit is attacking, damage is the ratio of enemy's defense power to this unit's attack power
// If this unit is defending, damage is the ratio of enemy's attack power to this unit's defense power
void Unit::dealDamage(double damage)
{
   m_attackPower -= damage;
   m_defensePower -= damage;
   if (attackPower <= 0 || defensePower <= 0)
      m_active = False; 
}

void Unit::engageUnit(std::unique_ptr<Unit> enemy)
{
   m_engagementList.push_back(enemy);
}

// Remove a specific unit from the engagement list
void Unit::disengageUnit(std::string unitID)
{
   for (auto it = m_engagementList.begin() ; it != m_engagementList.end(); ++it)
   {
       auto unit = *it;
       if (unit->getID() == unitID)
       {
           m_engagementList.erase(it);
           break;
       }
   }
}

void Unit::spendMovement(int cost){
   m_currentMoves -= cost;
}

void Unit::resetMovement(){
   m_currentMoves = m_numMoves;
}

void Unit::printUnit(){
   cout << "\nID: " << m_ID;
   cout << "\nBase Movement Range: " << m_numMoves;
   cout << "\nAvailable Movement Range: " << m_currentMoves;
   cout << "\nAttack Power: " << m_attackPower;
   cout << "\nDefense Power: " << m_defensePower << "\n";
}