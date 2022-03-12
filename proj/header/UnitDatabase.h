#ifndef UnitDatabase_h
#define UnitDatabase_h

#include <memory>
#include <string>
#include <map>

class Unit;

class UnitDatabase
{
public:
  static UnitDatabase& getUnitDatabase() {
    return theUnitDatabase;
  }
  std::shared_ptr<Unit> getUnit(std::string unitID);
  bool removeUnit(std::string unitID);
  bool addUnit(std::shared_ptr<Unit> unit);
  void clear();

private:
  UnitDatabase() {}
  static UnitDatabase theUnitDatabase;
  std::map<std::string, std::shared_ptr<Unit>> m_database;
};

#endif
