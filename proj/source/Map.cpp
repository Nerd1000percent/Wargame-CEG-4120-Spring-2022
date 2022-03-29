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
#include <sstream>
#include <iostream>

Map::Map(Coordinates dims) : m_arrayOfTiles({ dims.getRow(), dims.getColumn() }) {
	blueScore = 0;
	redScore = 0;
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
	auto& sourceTile = getTile(source);
	auto& destTile = getTile(dest);

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

	// get the destination units
	auto destUnits = destTile.getUnits();

	// check to see if we are trying to move to a tile with occupying forces
	if (destUnits.size() > 0 && destTile.getTeam() != unit->getTeam())
	{
		// fight all of them!
		std::list<std::shared_ptr<Unit>> dead;
		for (auto enemy : destUnits)
		{
			// fight the enemy
			unit->fightEnemy(enemy);

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

		// check to see if we died
		if (!unit->isActive())
		{
			// bury the dead
			sourceTile.removeUnit(unit);
			UnitDatabase::getUnitDatabase().removeUnit(unit->getID());
			return false;
		}
	}

	// refresh the destination units
	destUnits = destTile.getUnits();

	// check to see if the destination tile is clear or at least friendly
	if (destUnits.size() == 0 || destTile.getTeam() == unit->getTeam())
	{
		// if we get here, then we are able to move
		auto movement = unit->getCurrentMovement();
		auto cost = destTile.getTerrain().getMovementCost();

		if (movement >= cost)
		{
			// just move the unit
			sourceTile.removeUnit(unit);
			destTile.addUnit(unit);
			unit->spendMovement(cost);

			// increment the score if the unit is claiming a victory point that is not currently owned by their team
			auto unitTeam = unit->getTeam();
			if (destTile.getVictoryPoint())
			{
				if (destTile.getTeam() != unitTeam)
				{
					if (unitTeam == "blue")
					{
						blueScore++;
						if (redScore != 0) redScore--;
					}

					else
					{
						if (blueScore != 0) blueScore--;
						redScore++;
					}
				}

				else if (destTile.getTeam() == "")
				{
					if (unitTeam == "blue") blueScore++;
					else redScore++;
				}
			}
			
			// claim the tile regardless of victory point presence
			destTile.setTeam(unitTeam);
			
			return true;
		}
		else
		{
			// uncomment this to make units spend movement points without moving if they don't have enough to move to the destination
			//unit->spendMovement(unit->getCurrentMovement());
			return false;
		}
	}

	// still have some enemy on the tile
	else
	{
		// spend the points without moving
		unit->spendMovement(unit->getCurrentMovement());
		return false;
	}
}

void Map::resetUnitMovement()
{
	for (size_t row = 0; row < this->size().getRow(); row++)
	{
		for (size_t col = 0; col < this->size().getRow(); col++)
		{
			auto& tile = this->getTile({ row, col });
			auto units = tile.getUnits();
			if (units.size() > 0)
			{
				for (auto unit : units)
				{
					if (unit->isActive()) unit->resetMovement();
				}
			}
		}
	}
}

std::vector<Coordinates> Map::getVictoryPoints()
{
	std::vector<Coordinates> victoryPoints = {};
	for (size_t row = 0; row < this->size().getRow(); row++)
	{
		for (size_t col = 0; col < this->size().getRow(); col++)
		{
			auto& tile = this->getTile({ row, col });
			if (tile.getVictoryPoint())
			{
				auto coords = Coordinates(row, col);
				victoryPoints.push_back(coords);
			}
		}
	}
	return victoryPoints;
}

// What happens when out of bounds coordinates get passed in?
void Map::setVictoryPoint(Coordinates coords, bool victoryPoint)
{
	auto& tile = this->getTile(coords);
	tile.setVictoryPoint(victoryPoint);
}

void Map::clearVictoryPoints()
{
	for (size_t row = 0; row < this->size().getRow(); row++)
	{
		for (size_t col = 0; col < this->size().getRow(); col++)
		{
			auto& tile = this->getTile(Coordinates(row, col));
			tile.setVictoryPoint(false);
		}
	}
}
