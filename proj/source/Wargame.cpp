#include <fstream>
#include <iostream>
#include <string>

#include "nlohmann/json.hpp"

#include "Map.h"

const std::string FILENAME = "inputMap.json";

Map loadMap()
{
    // Load the map
    std::ifstream inFile(FILENAME);
    //std::cout << "The file is open: " << inFile.is_open() << std::endl;
    nlohmann::json j;
    inFile >> j;
    //std::cout << j.dump() << endl;
    Map gameBoard({ 0, 0 });
    j.get_to(gameBoard);
    return gameBoard;
}

void processMoveCommand()
{

}

int main(int argc, char* argv[])
{
    
    Map gameBoard = loadMap();


    return 0;
}
