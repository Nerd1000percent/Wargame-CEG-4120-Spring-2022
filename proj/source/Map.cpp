///Implementation of Map
#include "Map.h"
#include "Unit.h"
#include "nlohmann/json.hpp"
#include "Coordinates.h"
#include <list>
#include <array>
#include <fstream>
#include <string>

Map::Map(size_t dim) : m_arrayOfTiles({ dim, dim }) {
	
}

//Getter
HyperArray<Tiles>& Map::arrayOfTilesGetter () {
   return m_arrayOfTiles;
}

void Map::saveState(istream log) {
	//TODO
}
void Map::saveGameState(){
	nlohmann::json state;
	state["mapDimension"] = "todo";
	cout << __FUNCTION__ << ":" << __LINE__ << " state=" << state.dump() << endl;
	/*
    Json::Value actualJson; //creates the main JSON object 
    Json::StyledStreamWriter writer; // write to JSON
    ofstream newFile;  //open new file
    std::ifstream gameStateFile("GameState.json"); //Create the file
    actualJson["Map deminsions"]= mapDimension;//save the map dimension to JSON file
	for (auto i=0; i !=arrayOfTiles.size;i++){
		Json::Value temp(Json::arrayValue);
		
		for(auto j=0; j !=arrayOfTiles[i].size;j++){ //not sure why .size ie erroring out. 
			Json::Value obj(Json::objectValue);
			obj[<String>Unit::getAttackPower]=arrayOfTiles[i][j]; // somehow we need cast the getters to String. 
			obj[<String>Unit::getDefensePower]=arrayOfTiles[i][j];
			obj[<String>Unit::getMovement]=arrayOfTiles[i][j];
			temp.append(obj);
		}
	
		actualJson.append(temp);
	}
    
    newFile.open("GameState.json");
    writer.write(newFile, actualJson);
    newFile.close();
		*/
}


// Move unit tile to tile
// pre:: given unit id, location, and destination.  post:: unit is removed from location and added to destination, if the unit has the movement points and does not pass through any enemy adjacent tiles
int Map::moveUnit(string unitId, int locCoords[2], int destinationCoords[2])
{
	//TODO 
	return 0;

	/*
	Unit* unit = arrayOfTiles[locCoords[0]][locCoords[1]].findUnit(unitId); //not sure if this is how it needs to be called
	if (unit == 0) return 0;

	//std::array<int, 2> locCoordsCopy = locCoords; //copy array A into array B
	std::array<int, 2> locCoordsCopy = {locCoords[0], locCoords[1]};

	//if (checkPath(unit, locCoords, destinationCoords)) {
	//	arrayOfTiles[destinationCoords[0]][destinationCoords[1]].addUnit(unit);
	//	arrayOfTiles[locCoords[0]][locCoords[1]]->removeUnit(unit); // not sure if this is how it needs to be called
	//}
	*/

	/*
	if (checkPath(unit, locCoords, destinationCoords)) {
		arrayOfTiles[destinationCoords[0]][destinationCoords[1]].addUnit(*unit); // TODO overload this to call copy constructor
		arrayOfTiles[locCoords[0]][locCoords[1]].removeUnit(*unit); // not sure if this is how it needs to be called
	}
	*/
}

/** Interates through all tiles to see who is engaged. Will return a list of coordinates of hostiles within range of attack
 */
list<Coordinates> Map::getEngagedUnits() {

	//TODO
	return {};

	/*
	auto enemies = false;
//	if (enemies == unit->getFlag()) {
//		enemies = true;
//	}

	// TODO: find a way to distinquish between both roles if a player switches colors
	list<Coordinates> listOfHostiles;

	// Find all engaged units first
	for(auto r = 0; r < mapDimension; r++) {
		for(auto c = 0; c < mapDimension; c++) {


			// player's pieces
			if(arrayofTiles[r][c]->getFlag() != enemies){
				engagedUnits->insert(arrayOfTiles[r][c]->getUnit());

				// now looking for hostiles
				auto leftValid = false, rightValid = false;

				if(c - 1 >= 0) {
					leftValid = true;
					if(arrayofTiles[r][c - 1]->getFlag() == enemies) {
						listOfHostiles.insert(new Coordinates (r, c - 1));
					}
				}

				if(c + 1 < mapDimension) {
					rightValid = true; 
					if(arrayofTiles[r][c + 1]->getFlag() == enemies) {
					 	listOfHostiles.insert(new Coordinates (r, c + 1));
					}
				}
				if(r - 1 >= 0) {
					if(arrayOfTiles[r - 1][c]->getFlag() == enemies) {
						listOfHostiles.insert(new Coordinates (r - 1, c));
					}
					if(leftValid) {
						if(arrayofTiles[r - 1][c - 1]->getFlag() == enemies) {
							listOfHostiles.insert(new Coordinates (r - 1, c - 1));
						}
					}
					if(rightValid) {
						if(arrayofTiles[r - 1][c + 1]->getFlag() == enemies) {
							listOfHostiles.insert(new Coordinates (r - 1, c + 1));
						}
					}
				}
				if(r + 1 < mapDimension) {
						if(arrayofTiles[r + 1][c]->getFlag() == enemies) {
							listOfHostiles.insert(new Coordinates(r + 1, c));
						}
					if(leftValid) {
						if(arrayofTiles[r + 1][c - 1]->getFlag() == enemies) {
							listOfHostiles.insert(new Coordinates (r + 1, c - 1));
						}
					}
					if(rightValid) {
						if(arrayofTiles[r + 1][c + 1]->getFlag() == enemies) {
							listOfHostiles.insert(new Coordinates (r + 1, c + 1));
						}
					}
				}
			}
		}
	}
	*/
	
}

// pre:: given unit pointer and location/destination coords post:: check for sufficient movement and that will not enter hostile adjacent tile then will move unit to new tile
// Limitation: currently there could be a move that is possible that it does not like because of how it paths.  In these instances you may need to make smaller movements yourself.  Will come back to it if I can.
// TODO change for current and base move
bool Map::checkPath(Unit* unit, int locCoords[2], int destinationCoords[2]) {
	int availMove = unit->getMovement();
	int diffX = locCoords[0] - destinationCoords[0];
	int diffY = locCoords[1] - destinationCoords[1];

	//to keep track of negative x and Y to move left instead of right? not needed I don't think
	//bool negX = 0, negY = 0;

	//if (negX < 0) negX = 1;
	//if (negY < 0) negY = 1;


	// Checking for valid movement. With 8 directional movement the difference between new and old x or y is what matters. A full diagnol move for a 3 movement would mean x and y change by 3
	if (availMove < abs(diffX) || availMove < abs(diffY)) {
		std::cout << "error not enough movement";
		return 0;
	}

	int c = 0;

	// iterating through tiles, should go diagnally if it should. In each tile it will run a hostile check
	while (locCoords[0] != destinationCoords[0] && locCoords[1] != destinationCoords[1]) {
		if (diffX < 0) {
			locCoords[0] -= 1;
			diffX += 1;
		}
		else if (diffX > 0) {
			locCoords[0] += 1;
			diffX -= 1;
		}

		if (diffY < 0) {
			locCoords[1] -= 1;
			diffY += 1;
		}
		else if (diffY > 0) {
			locCoords[1] += 1;
			diffY -= 1;
		}

		// TODO solution for a "retreating move" technically the first tile moved can be away from an enemy but if it is into another enemy adjacent tile the move stops there
		if (hostileCheck(locCoords)) {
			std::cout << "Error: Can't move past hostile unit.  \n** This could be because of the pathing algorithm!  **\n** If you believe the move to be possible try entering it in one tile at a time to force the specific path required **\n\n";
			return 0;
		}
		c++;
	}

	return 1;
}



//pre:: coords are given.  post;: iterate through all surrounding tiles checking for enemies, return true if enemies are found
bool Map::hostileCheck(int coords[2]) {
	// TODO
	// hardcoding to false for now.
	return false;
}

void Map::addTile(string terrainName, int terrainCost, size_t xCoord, size_t yCoord) {
	m_arrayOfTiles.at({ yCoord, xCoord }) = Tiles(terrainName, terrainCost);
}

void to_json(nlohmann::json& j, const Map& m)
{
	j["map"] = m.m_arrayOfTiles;
}

void from_json(const nlohmann::json& j, Map& m)
{
	j.get_to(m.m_arrayOfTiles);
}

