/**
 * @file Weapon.cpp
 * @brief this cpp file writes the functions for each method needed
 * for the weapon class.
 * @ref Weapon.h
 * @author Mate Barabas and Steven Gingras
 */
#include "../include/Components/Weapon.h"

/**
 * @brief method that gets the weapon type
 * @return weapon type
 */
std::string Weapon::getWeaponType()
{
  return weaponType;
}
/**
 * @brief method that gets the range
 * @return range
 */
int Weapon::getRange()
{
  return range;
}
/**
 * @brief method that gets the dice type for the weapon
 * @return dice type
 */
std::string Weapon::getDiceType()
{
  return diceType;
}

std::string Weapon::toString() const
{
  return Item::toString() + " " + weaponType + " " + std::to_string(range) + " " + diceType;
}