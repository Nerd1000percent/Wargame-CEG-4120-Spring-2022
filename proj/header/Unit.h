#ifndef UNIT_H
#define UNIT_H

#include <string>
#include <vector>
#include <memory>

#include "nlohmann/json.hpp"

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
   * This indicates whether Unit is active (i.e. whether it's still in the game).
   */
   bool m_active;

   /**
   * This is the number of moves the Unit may make per turn.
   */
   int m_numMoves;

   /**
   * This is the number of moves the Unit has left on the current turn.
   */
   int m_currentMoves;

   /**
   * This is the Unit's attack value.
   */
   double m_attackPower;

   /**
   * This is the Unit's defense value.
   */
   double m_defensePower;

public:
   
   // Constructors

// need a default constructor for serialization

   /**
   * Creates new Unit objects.
   */
   Unit() = default;

   /**
   * Creates new Unit objects.
   * @param id String identifier.
   * @param numMoves Number of moves per turn.
   * @param attackPower Attack value for combat.
   * @param defensePower Defense value for combat.
   */
   Unit(std::string id, int numMoves, double attackPower, double defensePower);

   /**
   * Creates copies of Unit objects.
   * @param other Reference to the Unit object to be copied.
   */
   Unit(Unit& other);

   // Attribute accessor functions

   /**
   * Gets the Unit's m_id attribute.
   * @returns m_id
   */
   std::string getID() const;

   /**
   * Gets the Unit's m_active attribute.
   * @returns m_active
   */
   bool isActive() const;

   /**
   * Gets the Unit's m_numMoves attribute.
   * @returns m_numMoves
   */
   int getMovement() const;

   /**
   * Gets the Unit's m_currentMoves attribute.
   * @returns m_currentMoves
   */
   int getCurrentMovement() const;

   /**
   * Gets the Unit's m_attackPower attribute.
   * @returns m_attackPower
   */
   double getAttackPower() const;

   /**
   * Gets the Unit's m_defensePower attribute.
   * @returns m_defensePower
   */
   double getDefensePower() const;

   // Attribute mutator functions

   void setID(const std::string id);

   void setActive(const bool active);

   void setMovement(const int movement);

   void setAttackPower(const double attackPower);

   void setDefensePower(const double defensePower);

   // Unit action functions

   /**
   * Deducts damage from Unit's attack and defense then sets m_active to false if either reach 0.
   * @param damage Value to be deducted from the Unit's attack and defense values.
   * @returns void
   */
   void dealDamage(double damage);

   /**
   * Deducts cost from m_currentMoves.
   * @param cost The number to be deducted from m_currentMoves
   */
   void spendMovement(int cost);

   /**
   * Sets m_currentMoves to the value of m_numMoves.
   */
   void resetMovement();

   // Debugging functions

   /**
   * Prints out the member variables.
   */
   void printUnit();
};

// Serializer functions for game state reading/writing

/**
* TODO
*/
void to_json(nlohmann::json& j, const Unit& u);

/**
* TODO
*/
void from_json(const nlohmann::json& j, Unit& u);

#endif