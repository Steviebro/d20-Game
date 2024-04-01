/**
 * @file Equipment.cpp
 * @brief This cpp file writes the functionality for the equipmen methods
 * which helps know what a character has equipped or in his inventory.
 * @ref Equipment.h
 * @author Mate Barabas and Steven Gingras
 */
#include "../../include/Components/Equipment.h"

ItemBag& Equipment::getEquipped()
{
  return equipped;
}

ItemBag& Equipment::getInventory()
{
  return inventory;
}

Item* Equipment::getEquippedItem(std::string itemType)
{
  return equipped.getOrRemove(Functions::convertToUpper(itemType),false,true);
}


Armor* Equipment::getArmor() {
  return static_cast<Armor*>(getEquippedItem("ARMOR"));
}

Weapon* Equipment::getWeapon() {
  return static_cast<Weapon*>(getEquippedItem("WEAPON"));
}


/**
 * @brief method which allows a character to equip an item from his inventory
 * @param itemNameToEquip a string of the itemName of the Item to be equipped
 * @return a bool of whether the target item is in inventory (i.e. success of equipping)
 */
bool Equipment::equipItem(std::string itemNameToEquip) {
  //search inventory for itemName
  Item* itemToEquipPtr = inventory.getOrRemove(Functions::convertToUpper(itemNameToEquip), true, false);
  if (itemToEquipPtr == nullptr) { return false; }//item passed is not in inventory

  //check if itemType is already equipped, if so, unequip it
  if (equipped.hasItemType(itemToEquipPtr->getItemType())) {
    unequipItem(itemToEquipPtr->getItemType());
  }

  //put the item in equipped
  equipped.put(*itemToEquipPtr);
  return true;
}

/**
 * @brief method to unequip a specific item
 * @param itemTypeToUnequip the itemType to be unequipped
 * @return true if successful, false if itemType is not currently equipped
 */
bool Equipment::unequipItem(std::string itemTypeToUnequip) {
  //remove the passed itemtype item from equipped
  Item* unequippedItemPtr = equipped.getOrRemove(itemTypeToUnequip,true,true);
  if (unequippedItemPtr == nullptr) { return false; }//itemType is not already equipped

  inventory.put(*unequippedItemPtr);
  return true;
}

void Equipment::lootChestOrBody(ItemBag& toLoot)
{
  inventory.putMany(toLoot, true);
}

std::string Equipment::toString() const
{
  return equipped.getBagName() + " " + inventory.getBagName();
}

void Equipment::printEquipment() const
{
  std::cout << "\nEQUIPMENT: =========================="
  << "\nEquipped: " << equipped.toString()
  << "\nInventory: " << inventory.toString()
  << "\n=========================================\n";
}