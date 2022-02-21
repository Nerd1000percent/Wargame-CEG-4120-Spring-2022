#include "Unit.h"

Unit::Unit(std::string id, int numMoves, int attackPower, int defensePower)
: m_ID{id}
, m_numMoves{numMoves}
, m_attackPower{attackPower}
, m_defensePower{defensePower}
{
   m_active = true;
}

std::string Unit::getID()
{
   return m_ID;
}

int Unit::isActive()
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