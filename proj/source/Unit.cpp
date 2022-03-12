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

void Unit::setID(const std::string id)
{
    m_ID = id;
}

void Unit::setActive(const bool active)
{
    m_active = active;
}

void Unit::setMovement(const int movement)
{
    m_numMoves = movement;
}

void Unit::setAttackPower(const double attackPower)
{
    m_attackPower = attackPower;
}

void Unit::setDefensePower(const double defensePower)
{
    m_defensePower = defensePower;
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

void to_json(nlohmann::json& j, const Unit& u)
{
  j["id"] = u.getID();
  j["active"] = u.isActive();
  j["num_moves"] = u.getMovement();
  j["attack_power"] = u.getAttackPower();
  j["defense_power"] = u.getDefensePower();
}

void from_json(const nlohmann::json& j, Unit& u)
{
  // j["id"].get<std::string>();

  std::string id;
  j["id"].get_to(id);
  u.setID(id);

  bool active = true;
  j["active"].get_to(active);
  u.setActive(active);

  int numMoves = 0;
  j["num_moves"].get_to(numMoves);
  u.setMovement(numMoves);

  double attackPower = 0;
  j["attack_power"].get_to(attackPower);
  u.setAttackPower(attackPower);

  double defensePower = 0;
  j["defense_power"].get_to(attackPower);
  u.setDefensePower(defensePower);
}
