/**
 * @file Armor.cpp
 * @brief this file writes the functionality for the armor
 * functions that are needed to create the armor object.
 * @ref Armor.h
 * @author Mate Barabas and Steven Gingras
 */
#include "../include/Components/Armor.h"

/**
 * @brief method that gets the armor type for the armor
 * @return armor type
 */
std::string Armor::getArmorType()
{
  return armorType;
}

/**
 * @brief method that returns the base armor class of the armor
 * @return baseArmorAC
 */
int Armor::getBaseArmorAC() {
  return baseArmorAC;
}

std::string Armor::toString() const {
  return Item::toString() + " " + armorType + " " + std::to_string(baseArmorAC);
}