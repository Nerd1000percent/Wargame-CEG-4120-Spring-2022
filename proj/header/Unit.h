#ifndef UNIT_H
#define UNIT_H

#include <string>
#include <vector>
#include <memory>

/**
* @brief This class represents combat units in the game
* Unit objects have a string identifier, an active flag, a set number of allowed moves per turn, and attack and defense values for combat
*/
class Unit
{

private:

   // member variables

   /**
   * This is a unique string identifier.
   */
   std::string m_ID;

   /**
   * indicates whether unit is active (i.e. whether it's still in the game)
   */
   bool m_active;

   /**
   * number of moves the unit may make per turn
   */
   int m_numMoves;

   /**
   * number of moves the unit has left on the current turn
   */
   int m_currentMoves;

   /**
   * attack value
   */
   double m_attackPower;

   /**
   * defense value
   */
   double m_defensePower;

public:
   
   // Constructors

   /**
   * creates new Unit objects
   * @param id String identifier
   * @param numMoves Number of moves per turn
   * @param attackPower attack value for combat
   * @param defensePower defense value for combat
   */
   Unit(std::string id, int numMoves, double attackPower, double defensePower);

   /**
   * creates copies of Unit objects
   * @param other Reference to the Unit object to be copied
   */
   Unit(Unit& other);

   // Getter functions

   /**
   * gets m_id
   * @returns m_id
   */
   std::string getID();

   /**
   * gets m_active
   * @returns m_active
   */
   bool isActive();

   /**
   * gets m_numMoves
   * @returns m_numMoves
   */
   int getMovement();

   /**
   * gets m_currentMoves
   * @returns m_currentMoves
   */
   int getCurrentMovement();

   /**
   * gets m_attackPower
   * @returns m_attackPower
   */
   double getAttackPower();

   /**
   * gets m_defensePower
   * @returns m_defensePower
   */
   double getDefensePower();

   // Unit action functions

   /**
   * deducts damage from Unit's attack and defense then sets m_active to false if either reach 0
   * @param damage value to be deducted from the Unit's attack and defense values
   * @returns void
   */
   void dealDamage(double damage);

   /**
   * deducts cost from m_currentMoves
   * @param cost The number to be deducted from m_currentMoves
   */
   void spendMovement(int cost);

   /**
   * sets m_currentMoves to the value of m_numMoves
   */
   void resetMovement();

   // Debugging functions

   /**
   * prints out the member variables
   */
   void printUnit();
};
#endif