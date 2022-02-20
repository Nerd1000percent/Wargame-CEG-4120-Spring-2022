///Implementation of Map
#include "MAP.h"
#include "UNIT.h"
#include <list>
//Constructor
Map::Map() {
	this->arrayOfTiles[][] = 0;
	this->mapDimension = 0;
	this->engagedList = 0;
}

Map::Map(Map clone) {
   
}
//Getter
int Map::arrayOfTilesGetter () {
   return arrayOfTiles;
}

void Map::saveState(istream log) {
	//TODO
}

// Move unit tile to tile
// pre:: given unit id, location, and destination.  post:: unit is removed from location and added to destination, if the unit has the movement points and does not pass through any enemy adjacent tiles
int Map::moveUnit(string unitId, int locCoords[2], int destinationCoords[2]) {
	//TODO logging
	Unit* unit = arrayOfTiles[locCoords[0]][locCoords[1]]->getUnit(unitId); //not sure if this is how it needs to be called
	if (unit = 0) return 0;

	std::array<int, 4> locCoordsCopy = locCoords; //copy array A into array B

	if (checkPath(unit, locCoords, destinationCoords)) {
		arrayOfTiles[locCoordsCopy[0], [locCoordsCopy[1]]->removeUnit(unitId); // not sure if this is how it needs to be called
	}
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


