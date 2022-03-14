#include <fstream>
#include <iostream>
#include <memory>
#include <string>

#include "nlohmann/json.hpp"

#include "Map.h"

const std::string INPUT_FILE = "inputMap.json";
const std::string OUTPUT_FILE = "outputMap.html";
const std::string GAME_FILE = "gameState.json";

Map loadMap()
{
    // Load the map
    std::ifstream inFile(INPUT_FILE);
    //std::cout << "The file is open: " << inFile.is_open() << std::endl;
    nlohmann::json j;
    inFile >> j;
    //std::cout << j.dump() << endl;
    Map gameBoard({ 0, 0 });
    j.get_to(gameBoard);
    return gameBoard;
}

void displayMap(std::unique_ptr<Map> gameBoard)
{
    std::ofstream mapOutput;
    mapOutput.open(OUTPUT_FILE);
    mapOutput << gameBoard->mapToHtml();
}

void saveGame(std::unique_ptr<Map> gameBoard)
{
    ofstream jsonOputput;
    jsonOputput.open(GAME_FILE);
    nlohmann::json j = *gameBoard;
    jsonOputput << std::setw(4) << j << std::endl;
}

int main(int argc, char* argv[])
{
    
    Map gameBoard = loadMap();
    displayMap(std::make_unique<Map>(gameBoard));

    return 0;
}
