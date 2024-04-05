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

std::string Equipment::getName()
{
  return name;
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
  return name + " " + equipped.getBagName() + " " + inventory.getBagName();
}

void Equipment::printEquipment() const
{
  std::cout << "\nEQUIPMENT: =========================="
  << "\nName: " << name
  << "\nEquipped: " << equipped.toString()
  << "\nInventory: " << inventory.toString()
  << "\n=========================================\n";
}

void Equipment::writeEquipmentsToFile(std::vector<Equipment>& equipmentsToWrite)
{
  std::string fileName = "../saved/Equipment/equipments.txt";
  std::ofstream file(fileName);

  if (file.is_open()) {
    for (auto& equipment : equipmentsToWrite) {
      file << equipment.toString() << "\n";
    }
    file.close();
  } else {
    throw std::runtime_error("unable to write to file "+fileName+"\n");
  }
}

std::vector<Equipment> Equipment::readEquipmentsFromFile(std::vector<ItemBag> itemBags)
{
  std::vector<Equipment> result;
  std::string equipName, equippedBagName, inventoryBagName;
  ItemBag equippedTemp, inventoryTemp;
  bool equippedBagFound, inventoryBagFound;
  std::ifstream file("../saved/Equipment/equipments.txt");
  if (file.is_open()){
    while (file >> equipName >> equippedBagName >> inventoryBagName) {
      equippedBagFound = false;
      inventoryBagFound = false;
      for (auto& itemBag : itemBags) {
        if (itemBag.getBagName() == equippedBagName) {
          equippedTemp = itemBag;
          equippedBagFound = true;
        }
        if (itemBag.getBagName() == inventoryBagName) {
          inventoryTemp = itemBag;
          inventoryBagFound = true;
        }
      }
      if (!equippedBagFound || !inventoryBagFound) {
        throw std::runtime_error("either "+equippedBagName+" or "+inventoryBagName+" not found in the itembags!\n");
      }
      Equipment e(equipName,equippedTemp,inventoryTemp);
      e.printEquipment();
      result.emplace_back(e);
    }
  } else {
    throw std::runtime_error("unable to read from file ../saved/Equipment/equipments.txt\n");
  }
  file.close();
  return result;
}