/**
 * @file ItemBag.cpp
 * @brief this cpp files writes the functions for each method needed
 * for the item bag class.
 * @ref ItemBag.h
 * @author Mate Barabas and Steven Gingras
 */
#include "../../include/Components/ItemBag.h"

/**
 * @brief method that checks if it has a specific item type
 * @param itemType type of the item that we are checking for
 * @return boolean true or false
 */
bool ItemBag::hasItemType(std::string itemType)
{
  Functions::convertToUpper(itemType);

  for (auto& item : storage) {
    if (item.getItemType() == itemType) {
      return true;
    }
  }
  return false;
}

/**
 * @brief method that adds a specific item to the item bag.
 * @param toPut item that needs to be added
 */
void ItemBag::put(Item& toPut)
{
  storage.emplace_back(toPut);
}

/**
 * @brief method that gets the specified item from the item bag thats being looked for.
 * @param itemNameToGet name of item to get
 * @return specified item
 */
Item& ItemBag::get(std::string itemNameToGet)
{
  Functions::convertToUpper(itemNameToGet);

  for (auto& item : storage) {
    if (item.getItemName() == itemNameToGet) {
      return item;
    }
  }
  Item result;
  return result;
}

/**
 * @brief method that removes the item from the item bag and returns it
 * @param itemNameToRemove name of item to remove
 * @return item that was specified.
 */
Item& ItemBag::remove(std::string itemNameToRemove)
{
  Functions::convertToUpper(itemNameToRemove);

  for (auto it = storage.begin() ; it != storage.end() ; it++) {
    if (it->getItemName() == itemNameToRemove) {
      Item result = *it;
      storage.erase(it);
      return result;
    }
  }

}

/**
 * @brief method that adds all the different bonuses from the items
 * in the item bag that a character has depending on the enchant type.
 * @return total bonuses added up
 */
int ItemBag::sumEnchants(std::string enchant) const {
  Functions::convertToUpper(enchant);
  int sum = 0;
  for(auto& item : storage){
    if (item.getEnchantType() == enchant) {
      sum += item.getEnchantLevel();
    }
  }
  return sum;
}

/**
 * @brief method that gets by the type of the item
 * @param itemTypeToGet type of item to get
 * @return item returned by the type search
 */
Item& ItemBag::getByType(std::string itemTypeToGet){
  Functions::convertToUpper(itemTypeToGet);

  for (auto& item : storage) {
    if (item.getItemType() == itemTypeToGet) {
      return item;
    }
  }
  Item result;
  return result;
}

/**
 * @brief method that removes the item from the item bag and returns it
 * @param itemNameToRemove name of item to remove
 * @return item that was specified.
 */
Item& ItemBag::removeByType(std::string itemTypeToRemove)
{
  Functions::convertToUpper(itemTypeToRemove);

  for (auto it = storage.begin() ; it != storage.end() ; it++) {
    if (it->getItemType() == itemTypeToRemove) {
      Item result = *it;
      storage.erase(it);
      return result;
    }
  }

}