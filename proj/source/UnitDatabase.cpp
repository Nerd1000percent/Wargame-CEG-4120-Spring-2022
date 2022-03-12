#include "UnitDatabase.h"
#include "Unit.h"

UnitDatabase UnitDatabase::theUnitDatabase;

void UnitDatabase::clear()
{
  m_database.clear();
}

std::shared_ptr<Unit> UnitDatabase::getUnit(std::string unitID)
{
  if (!m_database.count(unitID))
    return nullptr;
  return m_database.at(unitID);
}

bool UnitDatabase::removeUnit(std::string unitID)
{
  if (!m_database.count(unitID))
    return false;
  m_database.erase(unitID);
  return true;
}

bool UnitDatabase::addUnit(std::shared_ptr<Unit> unit)
{
  // don't add it if we already have it
  if (m_database.count(unit->getID()))
    return false;

  // add the unit to the database
  m_database[unit->getID()] = unit;
  return true;
}
