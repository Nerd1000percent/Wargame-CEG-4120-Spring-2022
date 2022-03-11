#include "Unit.h"

#include <string>
#include <iostream>

Unit::Unit(std::string id, int numMoves, double attackPower, double defensePower)
: m_ID{id}
, m_active{true}
, m_numMoves{numMoves}
, m_currentMoves{numMoves}
, m_attackPower{1.0*attackPower}
, m_defensePower{1.0*defensePower}
{
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

std::string Unit::getID() const
{
   return m_ID;
}

bool Unit::isActive() const
{
   return m_active;
}

int Unit::getMovement() const
{
   return m_numMoves;
}

int Unit::getCurrentMovement() const
{
    return m_currentMoves;
}

double Unit::getAttackPower() const
{
   return m_attackPower;
}

double Unit::getDefensePower() const
{
   return m_defensePower;
}

// If this unit is attacking, damage is the ratio of enemy's defense power to this unit's attack power
// If this unit is defending, damage is the ratio of enemy's attack power to this unit's defense power
void Unit::dealDamage(double damage)
{
   m_attackPower -= damage;
   m_defensePower -= damage;
   if (m_attackPower <= 0 || m_defensePower <= 0)
      m_active = false; 
}

void Unit::spendMovement(int cost)
{
   m_currentMoves -= cost;
}

void Unit::resetMovement()
{
   m_currentMoves = m_numMoves;
}

void Unit::printUnit(){
   std::cout << "\nID: " << m_ID;
   std::cout << "\nBase Movement Range: " << m_numMoves;
   std::cout << "\nAvailable Movement Range: " << m_currentMoves;
   std::cout << "\nAttack Power: " << m_attackPower;
   std::cout << "\nDefense Power: " << m_defensePower << "\n";
}


// serializers
void to_json(nlohmann::json& j, const Unit& u)
{
  /*
  std::string m_ID;
   bool m_active;
   int m_numMoves;
   double m_attackPower;
   double m_defensePower;
  */
  j["id"] = u.getID();
  j["active"] = u.isActive();
  j["num_moves"] = u.getMovement();
  j["attack_power"] = u.getAttackPower();
  j["defense_power"] = u.getDefensePower();
}

void from_json(const nlohmann::json& j, Unit& u)
{
  // this is the id from the json.
  // how do we set it in u?
  // u.setID() doesn't seem to exist.
  j["id"].get<std::string>();
}
