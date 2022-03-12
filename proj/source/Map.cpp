///Implementation of Map
#include "Map.h"
#include "Unit.h"
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
	j.get_to(m.m_arrayOfTiles);
}

