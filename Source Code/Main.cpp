
#include <iostream>
#include <array>
#include <fstream>
using namespace std;


// demo saving to file
void saveGameState(){
    std::ofstream gameStateFile("gameStateFile.txt");
    // we would want to get copy of the map after all the plays have been made.
    gameStateFile<<"Copy of the new map after the player quits the game";
    gameStateFile.close();

}

// demo reading from a file
void readGameState(){

    // create empty copy of the map for now im just creating a string for demo purposes
    std::string myfile;
    ifstream MyReadFile ("gameStateFile.txt");
    while (std::getline (MyReadFile, myfile)) {
  // Output the text from the file
    cout << ;
    MyReadFile.close();
}



}
int main() {

//if the player choses to load saved game, call radGameState()

//if the player choses to save the game before qutting, call saveGameStat()

// the save file will be overrittewn everytime saveGameStat() is called, which gives the oppurtinty to save the game state one time. 


//main code goes here


return 0;
}
