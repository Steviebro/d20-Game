/**
 * @file ItemBag.cpp
 * @brief this cpp files writes the functions for each method needed
 * for the item bag class.
 * @ref ItemBag.h
 * @author Mate Barabas and Steven Gingras
 */
#include "../../include/Components/ItemBag.h"

std::string ItemBag::getBagName() const
{
  return bagName;
}

/**
 * @brief method that adds a specific item to the item bag.
 * @param toPut item that needs to be added
 */
void ItemBag::put(Item& itemToPut)
{
  storage.emplace_back(&itemToPut);
}

int ItemBag::putMany(ItemBag& bagToPut, bool emptyContents)
{
  int putCount = 0;
  for (auto& itemPtr : bagToPut.storage) {
    if (itemPtr != nullptr) {
      put(*itemPtr);
      putCount++;
    }
  }
  if (emptyContents) {
    bagToPut.storage.clear();
  }
  return putCount;
}

/**
 * @brief method that searches for an item by name or type then gets or removes the item from the item bag and returns it
 * @param targetItemNameOrType a string of the name or type of the target item
 * @param removeItem a bool specifying whether the Item should be removed from the ItemBag
 * @param searchByType a bool specifying if the target string is an itemType (true) or an itemName (false)
 * @return Item& that was specified.
 */
Item* ItemBag::getOrRemove(std::string targetItemNameOrType, bool removeItem, bool searchByType)
{
  Functions::convertToUpper(targetItemNameOrType);

  for (auto it = storage.begin() ; it != storage.end() ; it++) {
    if ((!searchByType && (*it)->getItemName() == targetItemNameOrType) || (searchByType && (*it)->getItemType() == targetItemNameOrType)) {
      if ((*it)->getItemType() == "ARMOR") {
        Armor* armorResult = dynamic_cast<Armor*>(*it);
        if (removeItem) { storage.erase(it); }
        return armorResult;
      } else if ((*it)->getItemType() == "WEAPON") {
        Weapon* weaponResult = dynamic_cast<Weapon*>(*it);
        if (removeItem) { storage.erase(it); }
        return weaponResult;
      } else {
        auto& itemResult = *it;
        if (removeItem) { storage.erase(it); }
        return itemResult;
      }
    }
  }
  return nullptr;
}

/**
 * @brief method that checks if it has a specific item type
 * @param itemType type of the item that we are checking for
 * @return boolean true or false
 */
bool ItemBag::hasItemType(std::string itemType)
{
  Functions::convertToUpper(itemType);

  for (auto itemPtr : storage) {
    if (itemPtr->getItemType() == itemType) {
      return true;
    }
  }
  return false;
}

/**
 * @brief method that adds all the different bonuses from the items
 * in the item bag that a character has depending on the enchant type.
 * @return total bonuses added up
 */
int ItemBag::sumEnchants(std::string enchant) const {
  Functions::convertToUpper(enchant);
  int sum = 0;
  for(auto itemPtr : storage){
    if (itemPtr->getEnchantType() == enchant) {
      sum += itemPtr->getEnchantLevel();
    }
  }
  return sum;
}

//might need to change this
std::string ItemBag::toString() const
{
  std::string result = bagName;
  for (auto itemPtr : storage) {
    result += " ";
    result += itemPtr->getItemName();
  }
  return result;
}

void ItemBag::printBag() const
{
  std::string result = "\nITEMBAG:==========================\nName: " + bagName + "\n";
  for (auto itemPtr : storage) {
    if (itemPtr != nullptr) {
      result += itemPtr->toString();
      result += "\n";
    }
  }
  result += "===================================================\n";
  std::cout << result;
}