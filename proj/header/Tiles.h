//Create a class Tiles
#ifndef TILES_H
#define TILES_H

#include <string>
#include <memory>
#include <iostream>
#include <list>

class Unit;
class Terrain;

class Tiles {
  //Attributes
private:
  std::shared_ptr<Terrain> terrainClass;
  std::list<std::shared_ptr<Unit>> allOfUnitClasses;
  //Member functions
public:
  //Constructor
  Tiles();
  Tiles(std::string terrainName, int terrainCost);

  //Getters
  std::shared_ptr<Terrain> terrainClassGetter();
  std::list<std::shared_ptr<Unit>> allOfUnitClassesGetter();

  //functions
  void addUnit(std::string id, int numMoves, int attackPower, int defensePower);
  void addUnit(std::shared_ptr<Unit> New);
  void removeUnit(std::shared_ptr<Unit> Remove);
  std::shared_ptr<Unit> findUnit(std::string find); // return pointer of a given unitid
  void listUnit();
};
#endif
