///Implementation of Map
#include "Map.h"
#include "Unit.h"
#include "UnitDatabase.h"
#include "nlohmann/json.hpp"
#include "Coordinates.h"
#include <list>
#include <array>
#include <fstream>
#include <string>

Map::Map(Coordinates dims) : m_arrayOfTiles({ dims.getRow(), dims.getColumn() }) {

}

Coordinates Map::size()
{
	return { m_arrayOfTiles.getDimension(0), m_arrayOfTiles.getDimension(1) };
}

Tiles& Map::getTile(Coordinates coords)
{
	return m_arrayOfTiles.at({ coords.getRow(), coords.getColumn() });
}

void to_json(nlohmann::json& j, const Map& m)
{
	j["map"] = m.m_arrayOfTiles;
}

void from_json(const nlohmann::json& j, Map& m)
{
	j["map"].get_to(m.m_arrayOfTiles);
}

bool Map::moveUnit(std::string unitID, Coordinates source, Coordinates dest)
{
	// get the tiles
	auto sourceTile = getTile(source);
	auto destTile = getTile(dest);

	// make sure that the unit is actually on the source tile
	auto unit = sourceTile.findUnit(unitID);
	if (!unit)
		return false;

	// measure vertical distance
	size_t distance = 0;
	if (source.getRow() > dest.getRow())
		distance += source.getRow() - dest.getRow();
	else
		distance += dest.getRow() - source.getRow();

	// measure horizontal distance
	if (source.getColumn() > dest.getColumn())
		distance += source.getColumn() - dest.getColumn();
	else
		distance += dest.getColumn() - source.getColumn();

	// make sure that the unit is only moving one tile at a time
	if (distance != 1)
		return false;

	// check to see if the destination tile is empty or is friendly
	auto destUnits = destTile.getUnits();
	if (destUnits.size() == 0 || destTile.getTeam() == unit->getTeam())
	{
		auto movement = unit->getCurrentMovement();
		auto cost = destTile.getTerrain().getMovementCost();

		if (movement >= cost)
		{
			// just move the unit
			sourceTile.removeUnit(unit);
			destTile.addUnit(unit);
			unit->spendMovement(cost);

			// claim this land as our own
			destTile.setTeam(unit->getTeam());
			return true;
		}
		else
		{
			// spend the points without moving
			unit->spendMovement(unit->getCurrentMovement());
			return false;
		}
	}

	// if we get here, then we are trying to move to a tile with occupying forces.
	// fight all of them!
	std::list<std::shared_ptr<Unit>> dead;
	for (auto enemy : destUnits)
	{
		// fight the enemy
		unit->fight(enemy);
		
		// check to see if the enemy died
		if (!enemy->isActive())
			dead.push_back(enemy);

		// check to see if we died
		if (!unit->isActive())
			break;
	}

	// bury all of the dead
	for (auto enemy : dead)
	{
		// remove all of the smart pointers.  they will be gone when the dead list goes out of scope.
		destTile.removeUnit(enemy);
		UnitDatabase::getUnitDatabase().removeUnit(enemy->getID());
	}

	/*
	// check to see if we are still alive
	if (unit->isActive())
	{
		// move the unit ignoring the movement cost
		sourceTile.removeUnit(unit);
		destTile.addUnit(unit);
		unit->spendMovement(cost);

		// claim this land as our own
		destTile.setTeam(unit->getTeam());
		return true;
	}
	else
	{
		sourceTile.removeUnit(unit);
		UnitDatabase::getUnitDatabase().removeUnit(unit->getID());
		return false;
	}	
	*/
}
