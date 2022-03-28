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
}

void displayMap(std::shared_ptr<Map> p_map)
{
    std::ofstream mapOutput;
    mapOutput.open(HTML_FILE);
    mapOutput << p_map->mapToHtml();
}

void logGameState(std::string saveFile, std::shared_ptr<Map> p_map)
{
    ofstream jsonOutput;
    jsonOutput.open(saveFile);
    nlohmann::json j = *p_map;
    jsonOutput << std::setw(4) << j << std::endl;
}

void splitString(std::string s, std::vector<string>& v)
{
    string temp = "";
    for (int i = 0; i < s.length(); ++i)
    {

        if (s[i] == ' ')
        {
            v.push_back(temp);
            temp = "";
        }
        else
        {
            temp.push_back(s[i]);
        }
    }
    v.push_back(temp);
}

int main(int argc, char* argv[])
{
    std::cout << "Enter the name of the file to load the game board from: ";
    std::string inputFile;
    std::cin >> inputFile;
    auto p_gameBoard = std::make_shared<Map>(Coordinates{ 0, 0 });
    if (!loadMap(MAP_DIR + inputFile, p_gameBoard))
    {
        std::cout << std::endl << inputFile << " does not exist." << std::endl;
        std::cout << "Terminating." << std::endl;
        return 1;
    }
    displayMap(p_gameBoard);

    std::string team = "blue";
    std::string userInput = "";
    std::string command = "";
    size_t turn = 1;

    while (command != "exit")
    {
        p_gameBoard->resetUnitMovement();
        
        if (team == "blue") cout << "Blue";
        else cout << "Red";
        cout << " player, it is now your turn." << std::endl;
        
        command = "";
        while (command != "exit" && command != "done")
        {
            getline(std::cin, userInput);
            std::vector<std::string> args;
            splitString(userInput, args);
            command = args[0];

            // move commands should be of the form:
            // move unitID sourceX sourceY destX destY
            if (command == "move")
            {
                Coordinates source(stoi(args[2]), stoi(args[3]));
                Coordinates dest(stoi(args[4]), stoi(args[5]));
                
                auto& sourceTile = p_gameBoard->getTile(source);
                if (sourceTile.getTeam() != team)
                    std::cout << "You may not move the other team's units." << std::endl;

                if (!p_gameBoard->moveUnit(args[1], source, dest))
                    std::cout << "The unit did not successfully move." << std::endl;
                displayMap(p_gameBoard);
            }

            // this case is here so that the else statement doesn't print anything when these commands are entered
            else if (command == "exit" || command == "done" || command == "")
            {
            }

            else
                std::cout << "That is not a recognized command." << std::endl;
        }
        
        if (command == "done")
        {
            if (team == "blue") cout << "Blue";
            else cout << "Red";
            cout << " player's turn is over. " << std::endl << std::endl;
        }

        if (command == "exit")
        {
            std::cout << std::endl << "Terminating." << std::endl;
        }

        // log the game state and increment the turn counter
        // NOTE: this only logs the state of the game if both blue and red have gone this turn; if only blue takes a turn, progress will be lost
        if (team == "red") // the turn is only over once both red and blue have gone, so execute after red's turn
        {
            logGameState(MAP_DIR + "turn" + std::to_string(turn) + ".json", p_gameBoard);
            turn++;
        }
        
        team = (team == "blue") ? "red" : "blue";
    }

    return 0;
}
