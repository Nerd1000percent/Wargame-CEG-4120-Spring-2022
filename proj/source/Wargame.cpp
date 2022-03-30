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

//TODO: make this return the line number of the file that had an issue
bool playFromFile(std::string commandFile)
{
    std::ifstream inFile(MAP_DIR + commandFile);
    if (!inFile.is_open())
    {
        return false;
    }

    // Load game board from file
    std::string mapFile;
    getline(inFile, mapFile);
    auto p_gameBoard = std::make_shared<Map>(Coordinates{ 0, 0 });
    if (!loadMap(MAP_DIR + mapFile, p_gameBoard))
    {
        return false;
    }
    displayMap(p_gameBoard);

    // Process victory point editing commands
    std::string line = "";
    std::string command = "";
    //std::cout << "Would you like to edit the victory points on the game board? (y/n)" << std::endl;
    getline(inFile, line);
    if (line == "y" || line == "Y")
    {
        //std::cout << "You may enter coordinates for tiles to become victory points until you enter the \"exit\" command." << std::endl;
        //std::cout << "Type \"help\" for more options." << std::endl << std::endl;
        line = "";
        while (command != "exit")
        {
            getline(inFile, line);
            std::vector<std::string> args;
            splitString(line, args);
            command = args[0];

            if (command == "add")
            {
                Coordinates tile(stoi(args[1]), stoi(args[2]));
                size_t maxRow = p_gameBoard->size().getRow() - 1;
                size_t maxCol = p_gameBoard->size().getColumn() - 1;

                //std::cout << std::endl;
                bool ok = true;
                if (tile.getRow() > maxRow || tile.getRow() < 0)
                {
                    ok = false;
                    //std::cout << "ERROR: row index must be between 0 and " << maxRow << " (inclusive)." << std::endl;
                }
                if (tile.getColumn() > maxCol || tile.getColumn() < 0)
                {
                    ok = false;
                    //std::cout << "ERROR: column index must be between 0 and " << maxCol << " (inclusive)." << std::endl;
                }

                if (ok)
                    p_gameBoard->setVictoryPoint(tile, true);
                
                /*
                else
                    std::cout << std::endl;
                */
            }

            /*
            else if (command == "display")
            {
                auto victoryPoints = p_gameBoard->getVictoryPoints();
                if (victoryPoints.size() == 0)
                {
                    std::cout << std::endl << "There are currently no victory points on the game board." << std::endl;
                    std::cout << "You can add victory points to the board with the \"add\" command." << std::endl;
                    std::cout << "Type \"help\" for more info." << std::endl << std::endl;
                }

                else
                {
                    std::cout << std::endl << "The following victory points are currently on the game board:" << std::endl;
                    for (auto i = victoryPoints.begin(); i != victoryPoints.end(); i++)
                        std::cout << "Row: " << (*i).getRow() << ", Column: " << (*i).getColumn() << std::endl;
                    std::cout << std::endl;
                }
            }
            */

            else if (command == "remove")
            {
                Coordinates tile(stoi(args[1]), stoi(args[2]));
                p_gameBoard->setVictoryPoint(tile, false);
            }

            else if (command == "clear")
            {
                p_gameBoard->clearVictoryPoints();
            }

            /*
            else if (command == "help")
            {
                std::cout << std::endl << "The following commands are available:" << std::endl << std::endl;

                std::cout << "add {row index} {column index}" << std::endl;
                std::cout << "\tturns the tile at the specified index into a victory point" << std::endl;

                std::cout << std::endl << "remove {row index} {column index}" << std::endl;
                std::cout << "\tturns the victory point at the specified index into a regular tile" << std::endl;

                std::cout << std::endl << "clear" << std::endl;
                std::cout << "\tturns all victory points currently on the game board into regular tiles" << std::endl;

                std::cout << std::endl << "display" << std::endl;
                std::cout << "\tprints all the victory points currently on the game board to the console" << std::endl;

                std::cout << std::endl << "exit" << std::endl;
                std::cout << "\texits the edit mode and begins the game" << std::endl;

                std::cout << std::endl;
            }
            */

            // don't print anything in these cases
            else if (command == "exit" || command == "")
            {
            }

            else
            {
                /*
                std::cout << std::endl << "That command is not recognized." << std::endl;
                std::cout << "Type \"help\" for the list of available commands." << std::endl << std::endl;
                */
            }

        } // while (command != "exit")

        logGameState(MAP_DIR + "configuration.json", p_gameBoard);
        //std::cout << std::endl << "Your changes have been saved to configuration.json." << std::endl << std::endl;

    } // if (line == "y")

    // Play the actual game
    std::string team = "blue";
    line = "";
    command = "";
    size_t turn = 1;

    // TODO: CALL THE setStartScores FUNCTION HERE
    //std::cout << "The game is now starting." << std::endl;
    while (command != "exit")
    {
        p_gameBoard->resetUnitMovement();

        /*
        if (team == "blue") cout << "Blue";
        else cout << "Red";
        cout << " player, it is now your turn." << std::endl;
        */

        command = "";
        while (command != "exit" && command != "done")
        {
            getline(inFile, line);
            std::vector<std::string> args;
            splitString(line, args);
            command = args[0];

            // maybe eventually make it so that the user doesn't need to enter the source tile, just find it for them
            if (command == "move")
            {
                Coordinates source(stoi(args[2]), stoi(args[3]));
                Coordinates dest(stoi(args[4]), stoi(args[5]));

                auto& sourceTile = p_gameBoard->getTile(source);
                if (sourceTile.getTeam() != team)
                {
                    //std::cout << "You may not move the other team's units." << std::endl;
                }

                if (!p_gameBoard->moveUnit(args[1], source, dest))
                {
                    //std::cout << "The unit did not successfully move." << std::endl;
                }
                displayMap(p_gameBoard);
            }

            /*
            else if (command == "display")
            {
                auto victoryPoints = p_gameBoard->getVictoryPoints();
                if (victoryPoints.size() == 0)
                {
                    std::cout << std::endl << "There are currently no victory points on the game board." << std::endl;
                    std::cout << "You can add victory points to the board with the \"add\" command." << std::endl;
                    std::cout << "Type \"help\" for more info." << std::endl << std::endl;
                }

                else
                {
                    std::cout << std::endl << "The following victory points are currently on the game board:" << std::endl;
                    for (auto i = victoryPoints.begin(); i != victoryPoints.end(); i++)
                        std::cout << "Row: " << (*i).getRow() << ", Column: " << (*i).getColumn() << std::endl;
                    std::cout << std::endl;
                }
            }
            */

            /*
            else if (command == "help")
            {
                std::cout << std::endl << "The following commands are available:" << std::endl << std::endl;

                std::cout << std::endl << "move {source row index} {source col index} {destination row index} {destination col index}" << std::endl;
                std::cout << "\tmoves the specified unit to the desired destination if it is only one tile away" << std::endl;

                std::cout << std::endl << "display" << std::endl;
                std::cout << "\tprints all the victory points currently on the game board to the console" << std::endl;

                std::cout << std::endl << "done" << std::endl;
                std::cout << "\tends the current team's turn and begins the other team's turn" << std::endl;

                std::cout << std::endl << "exit" << std::endl;
                std::cout << "\tends the game and saves its state one last time if it's currently the red team's turn" << std::endl;

                std::cout << std::endl;
            }
            */

            // this case is here so that the else statement doesn't print anything when these commands are entered
            else if (command == "exit" || command == "done" || command == "")
            {
            }

            /*
            else
                std::cout << "That is not a recognized command." << std::endl;
            */
        }
        

        if (command == "done")
        {
            /*
            if (team == "blue") cout << "Blue";
            else cout << "Red";
            cout << " player's turn is over. " << std::endl << std::endl;
            */
        }

        if (command == "exit")
        {
            //std::cout << std::endl << "Terminating." << std::endl;
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

    return true;
}

int main(int argc, char* argv[])
{
    std::cout << "Do you want to read commands in from a text file? (y/n)" << std::endl;
    std::string userInput = "";
    std::cin >> userInput;
    if (userInput == "y" || userInput == "Y")
    {
        std::cout << "Enter the name of the file to read commands from: ";
        std::cin >> userInput;
        if (!playFromFile(userInput))
        {
            std::cout << "ERROR: issue with file" << std::endl;
            return 1;
        }
        return 0;
    }

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

    userInput = "";
    std::string command = "";
    std::cout << "Would you like to edit the victory points on the game board? (y/n)" << std::endl;
    std::cin >> userInput;

    // What if they enter a tile that is already a victory point?
    // What if they enter a tile that is not on the board?
    std::cout << std::endl;
    if (userInput == "y" || userInput == "Y")
    {
        std::cout << "You may enter coordinates for tiles to become victory points until you enter the \"exit\" command." << std::endl;
        std::cout << "Type \"help\" for more options." << std::endl << std::endl;
        while (command != "exit")
        {
            getline(std::cin, userInput);
            std::vector<std::string> args;
            splitString(userInput, args);
            command = args[0];

            if (command == "add")
            {
                Coordinates tile(stoi(args[1]), stoi(args[2]));
                size_t maxRow = p_gameBoard->size().getRow() - 1;
                size_t maxCol = p_gameBoard->size().getColumn() - 1;

                //std::cout << std::endl;
                bool ok = true;
                if (tile.getRow() > maxRow || tile.getRow() < 0)
                {
                    ok = false;
                    std::cout << "ERROR: row index must be between 0 and " << maxRow << " (inclusive)." << std::endl;
                }
                if (tile.getColumn() > maxCol || tile.getColumn() < 0)
                {
                    ok = false;
                    std::cout << "ERROR: column index must be between 0 and " << maxCol << " (inclusive)." << std::endl;
                }

                if (ok)
                    p_gameBoard->setVictoryPoint(tile, true);
                else
                    std::cout << std::endl;
            }

            else if (command == "display")
            {
                auto victoryPoints = p_gameBoard->getVictoryPoints();
                if (victoryPoints.size() == 0)
                {
                    std::cout << std::endl << "There are currently no victory points on the game board." << std::endl;
                    std::cout << "You can add victory points to the board with the \"add\" command." << std::endl;
                    std::cout << "Type \"help\" for more info." << std::endl << std::endl;
                }

                else
                {
                    std::cout << std::endl << "The following victory points are currently on the game board:" << std::endl;
                    for (auto i = victoryPoints.begin(); i != victoryPoints.end(); i++)
                        std::cout << "Row: " << (*i).getRow() << ", Column: " << (*i).getColumn() << std::endl;
                    std::cout << std::endl;
                }
            }

            else if (command == "remove")
            {
                Coordinates tile(stoi(args[1]), stoi(args[2]));
                p_gameBoard->setVictoryPoint(tile, false);
            }

            else if (command == "clear")
            {
                p_gameBoard->clearVictoryPoints();
            }

            else if (command == "help")
            {
                std::cout << std::endl << "The following commands are available:" << std::endl << std::endl;

                std::cout << "add {row index} {column index}" << std::endl;
                std::cout << "\tturns the tile at the specified index into a victory point" << std::endl;

                std::cout << std::endl << "remove {row index} {column index}" << std::endl;
                std::cout << "\tturns the victory point at the specified index into a regular tile" << std::endl;

                std::cout << std::endl << "clear" << std::endl;
                std::cout << "\tturns all victory points currently on the game board into regular tiles" << std::endl;

                std::cout << std::endl <<  "display" << std::endl;
                std::cout << "\tprints all the victory points currently on the game board to the console" << std::endl;

                std::cout << std::endl << "exit" << std::endl;
                std::cout << "\texits the edit mode and begins the game" << std::endl;

                std::cout << std::endl;
            }

            // don't print anything in these cases
            else if (command == "exit" || command == "")
            {
            }

            else
            {
                std::cout << std::endl << "That command is not recognized." << std::endl;
                std::cout << "Type \"help\" for the list of available commands." << std::endl << std::endl;
            }

        } // while (command != "exit")

        logGameState(MAP_DIR + "configuration.json", p_gameBoard);
        std::cout << std::endl << "Your changes have been saved to configuration.json." << std::endl << std::endl;

    } // if (userInput == "y")

    std::string team = "blue";
    userInput = "";
    command = "";
    size_t turn = 1;

    // TODO: CALL THE setStartScores FUNCTION HERE
    std::cout << "The game is now starting." << std::endl;
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

            // maybe eventually make it so that the user doesn't need to enter the source tile, just find it for them
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

            else if (command == "display")
            {
                auto victoryPoints = p_gameBoard->getVictoryPoints();
                if (victoryPoints.size() == 0)
                {
                    std::cout << std::endl << "There are currently no victory points on the game board." << std::endl;
                    std::cout << "You can add victory points to the board with the \"add\" command." << std::endl;
                    std::cout << "Type \"help\" for more info." << std::endl << std::endl;
                }

                else
                {
                    std::cout << std::endl << "The following victory points are currently on the game board:" << std::endl;
                    for (auto i = victoryPoints.begin(); i != victoryPoints.end(); i++)
                        std::cout << "Row: " << (*i).getRow() << ", Column: " << (*i).getColumn() << std::endl;
                    std::cout << std::endl;
                }
            }
            
            else if (command == "help")
            {
                std::cout << std::endl << "The following commands are available:" << std::endl << std::endl;

                std::cout << std::endl << "move {source row index} {source col index} {destination row index} {destination col index}" << std::endl;
                std::cout << "\tmoves the specified unit to the desired destination if it is only one tile away" << std::endl;
                
                std::cout << std::endl << "display" << std::endl;
                std::cout << "\tprints all the victory points currently on the game board to the console" << std::endl;

                std::cout << std::endl << "done" << std::endl;
                std::cout << "\tends the current team's turn and begins the other team's turn" << std::endl;
                
                std::cout << std::endl << "exit" << std::endl;
                std::cout << "\tends the game and saves its state one last time if it's currently the red team's turn" << std::endl;

                std::cout << std::endl;
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
