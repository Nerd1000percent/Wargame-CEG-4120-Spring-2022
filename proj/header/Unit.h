#ifndef UNIT_H
#define UNIT_H

#include <string>
#include <vector>
#include <memory>

/*
* Unit class
* This class represents combat units in the game
* Unit objects have a string identifier, an active flag, a set number of allowed moves per turn, and attack and defense values for combat
*/
class Unit
{

private:

   // member variables
   std::string m_ID; // string identifier
   bool m_active; // indicates whether unit is active (i.e. whether it's still in the game)
   int m_numMoves; // number of moves the unit may make per turn
   int m_currentMoves; // number of moves the unit has left on the current turn
   double m_attackPower;
   double m_defensePower;

public:
   
   // Constructors
   
   // Function: Unit constructor
   // Parameters:
   //             std::string id - string identifier
   //             int numMoves - number of moves per turn
   //             double attackPower - attack value for combat
   //             double defensePower - defense value for combat
   // Returns: N/A
   Unit(std::string id, int numMoves, double attackPower, double defensePower);

   // Function: Unit copy constructor
   // Parameters: Unit& other - reference to the Unit object to be copied
   // Returns: N/A
   Unit(Unit& other);

   // Getter functions

   // Function: getID
   // Parameters: N/A
   // Returns: std::string - m_id
   std::string getID();

   // Function: isactive
   // Parameters: N/A
   // Returns: bool - m_active
   bool isActive();

   // Function: getMovement
   // Parameters: N/A
   // Returns: int - m_numMoves
   int getMovement();

   // Function: getCurrentMovement
   // Parameters: N/A
   // Returns: int - m_currentMoves
   int getCurrentMovement();

   // Function: getAttackPower
   // Parameters: N/A
   // Returns: double - m_attackPower
   double getAttackPower();

   // Function: getDefensePower
   // Parameters: N/A
   // Returns: double - m_defensePower
   double getDefensePower();

   // Unit action functions

   // Function: dealDamage
   // Parameters: double damage - damage value to be deducted from the Unit's attack and defense values
   // Returns: N/A
   // Side Effects: if either m_attackValue or m_defenseValue hits 0, m_active will be set to false
   void dealDamage(double damage);

   // Function: spendMovement
   // Parameters: int cost - number of movement points to be used
   // Returns: N/A
   // Side Effects: cost is deducted from m_currentMovement
   void spendMovement(int cost);

   // Function: resetMovement
   // Parameters: N/A
   // Returns: N/A
   // Side Effects: m_currentMoves is set to the value of m_numMoves
   void resetMovement();

   // Debugging function

   // Function: printUnit
   // Parameters: N/A
   // Returns: N/A
   // Side Effects: prints out the member variables of the Unit object
   void printUnit();
};
#endif