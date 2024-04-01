/**
 * @file Weapon.h
 * @brief this file is used for creating the functions for
 * the weapon item type which will be used for doing the combat damage
 * to enemies.
 * @ref Item.h
 * @author Mate Barabas and Steven Gingras
 */
#ifndef INC_345PROJECT_INCLUDE_COMPONENTS_WEAPON_H_
#define INC_345PROJECT_INCLUDE_COMPONENTS_WEAPON_H_
#include "Item.h"

/**
 * @class Weapon
 * @brief this class is used for creating the character weapon object
 * that inherits from the item object.
 */
class Weapon : public Item {
public:
  Weapon(std::string itemNameParam, std::string itemTypeParam, std::string enchantTypeParam, int enchantLevelParam, std::string weaponTypeParam, int rangeParam, std::string diceTypeParam) : Item(itemNameParam, itemTypeParam, enchantTypeParam, enchantLevelParam), weaponType(Functions::convertToUpper(weaponTypeParam)), range(rangeParam), diceType(diceTypeParam){};
  Weapon() : Item(), weaponType("-"), range(0), diceType("-") {};

  std::string getWeaponType();
  int getRange();
  std::string getDiceType();

  std::string toString() const;

private:
  std::string weaponType;
  int range;
  std::string diceType;
};
#endif //INC_345PROJECT_INCLUDE_COMPONENTS_WEAPON_H_
