#include "Unit.h"

#include <string>
#include <iostream>

Unit::Unit(std::string id, std::string team, int numMoves, double attackPower, double defensePower)
  : m_ID{ id }
  , m_team{ team }
  , m_active{ true }
  , m_numMoves{ numMoves }
  , m_currentMoves{ numMoves }
  , m_attackPower{ 1.0 * attackPower }
  , m_defensePower{ 1.0 * defensePower }
{
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

void Unit::setTeam(std::string team)
{
  m_team = team;
}

std::string Unit::getTeam() const
{
  return m_team;
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

void Unit::fightEnemy(std::shared_ptr<Unit> enemy)
{

}

void Unit::spendMovement(int cost)
{
  m_currentMoves -= cost;
}

void Unit::resetMovement()
{
  m_currentMoves = m_numMoves;
}

void Unit::printUnit() {
  std::cout << "\nID: " << m_ID;
  std::cout << "\nBase Movement Range: " << m_numMoves;
  std::cout << "\nAvailable Movement Range: " << m_currentMoves;
  std::cout << "\nAttack Power: " << m_attackPower;
  std::cout << "\nDefense Power: " << m_defensePower << "\n";
}

void to_json(nlohmann::json& j, const Unit& u)
{
  j["id"] = u.getID();
  j["team"] = u.getTeam();
  j["active"] = u.isActive();
  j["num_moves"] = u.getMovement();
  j["attack_power"] = u.getAttackPower();
  j["defense_power"] = u.getDefensePower();
}

void from_json(const nlohmann::json& j, Unit& u)
{
  std::string id;
  j["id"].get_to(id);
  u.setID(id);

  std::string team;
  j["team"].get_to(team);
  u.setTeam(team);

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
  j["defense_power"].get_to(defensePower);
  u.setDefensePower(defensePower);
}
