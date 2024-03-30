/**
 * @file Equipment.cpp
 * @brief This cpp file writes the functionality for the equipmen methods
 * which helps know what a character has equipped or in his inventory.
 * @ref Equipment.h
 * @author Mate Barabas and Steven Gingras
 */
#include "../../include/Components/Equipment.h"

Armor Equipment::getArmor() const{
  return armor;
}

Weapon Equipment::getWeapon() const{
  return weapon;
}

/**
 * @brief method which allows a character to equip a new item
 * @param itemParam item to be equipped
 */
void Equipment::equipItem(Item itemToEquip) {
  if (otherEquipped.hasItemType(itemToEquip.getItemType())) {
   inventory.put(otherEquipped.removeByType(itemToEquip.getItemType()));
  }
  otherEquipped.put(itemToEquip);
}

/**
 * @brief method to equip new armor
 * @param armorParam armor to be equipped
 */
void Equipment::equipArmor(Armor& armorParam){
  if (armor.getItemName() != "INVALID_ITEM") {
    inventory.put(armor);
  }
  armor = armorParam;
}

/**
 * @brief method to equip new weapon
 * @param weaponParam weapon to be equipped
 */
void Equipment::equipWeapon(Weapon& weaponParam) {
  if (weapon.getItemName() != "INVALID_ITEM") {
    inventory.put(weapon);
  }
  weapon = weaponParam;
}

/**
 * @brief method to unequip a specific item
 * @param itemType item to unequip
 */
void Equipment::unequipItem(std::string itemType) {
  if (itemType == "ARMOR" && armor.getItemName() != "INVALID_ITEM") {
    inventory.put(armor);
    Armor a;
    armor = a;
  } else if (itemType == "WEAPON" && weapon.getItemName() != "INVALID_ITEM") {
    inventory.put(weapon);
    Weapon w;
    weapon = w;
  } else {
    inventory.put(otherEquipped.removeByType(itemType));
  }
}

/**
 * @brief method that adds up the specified enchant bonuses
 * @param enchant specific enchant
 * @return sum of bonuses
 */
int Equipment::sumEnchants(std::string enchant) const {
  Functions::convertToUpper(enchant);
  int sum = otherEquipped.sumEnchants(enchant);

  if (armor.getEnchantType() == enchant) {
    sum += armor.getEnchantLevel();
  }
  if (weapon.getEnchantType() == enchant) {
    sum += weapon.getEnchantLevel();
  }
  return sum;
}