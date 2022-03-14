#include <fstream>
#include <iostream>
#include <memory>
#include <string>

#include "nlohmann/json.hpp"

#include "Map.h"

const std::string MAP_DIR = "MapFiles\\";
const std::string HTML_FILE = MAP_DIR + "currentState.html";

bool loadMap(std::string inputFile, std::shared_ptr<Map> p_map)
{
    std::ifstream inFile(inputFile);
    if (!inFile.is_open()) return false;
    nlohmann::json j;
    inFile >> j;
    j.get_to(*p_map);
    return true;

    //// load
    //std::ifstream inFile(INPUT_FILE);
    //std::cout << "The file is open: " << inFile.is_open() << std::endl;
    //nlohmann::json j;
    //inFile >> j;
    //std::cout << j.dump() << endl;
    //Map gameBoard({ 0, 0 });
    //j.get_to(gameBoard);
    //return gameBoard;
}

void displayMap(std::shared_ptr<Map> p_map)
{
    std::ofstream mapOutput;
    mapOutput.open(HTML_FILE);
    mapOutput << p_map->mapToHtml();
}

//void saveGame(std::string saveFile, Map& map)
//{
//    ofstream jsonOutput;
//    jsonOutput.open(saveFile);
//    nlohmann::json j = map;
//    jsonOutput << std::setw(4) << j << std::endl;
//
//    //// L
//    //ofstream jsonOutput;
//    //jsonOutput.open(GAME_FILE);
//    //nlohmann::json j = *gameBoard;
//    //jsonOutput << std::setw(4) << j << std::endl;
//}

int main(int argc, char* argv[])
{
    std::cout << "Enter the name of the file to load the game board from: " << std::endl;
    std::string inputFile;
    std::cin >> inputFile;
    inputFile = MAP_DIR + inputFile;
    auto p_gameBoard = std::make_shared<Map>(Coordinates{ 0, 0 });
    loadMap(inputFile, p_gameBoard);
    displayMap(p_gameBoard);

    //Map gameBoard = loadMap();
    //displayMap(std::make_unique<Map>(gameBoard));

    return 0;
}
