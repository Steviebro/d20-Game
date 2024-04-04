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
      Item* itemResult = *it;
      if (removeItem) { storage.erase(it); }
      return itemResult;
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

void ItemBag::writeBagsToFile(std::vector<ItemBag>& bagsToWrite)
{
  std::string fileName = "../saved/ItemBag/itembags.txt";
  std::ofstream file(fileName);

  if (file.is_open()) {
    for (auto& itembag : bagsToWrite) {
      file << itembag.toString() << "\n";
    }
    file.close();
  } else {
    throw std::runtime_error("unable to write to file "+fileName+"\n");
  }
}

std::vector<ItemBag> ItemBag::readBagsFromFile(std::vector<Item>& importedItems, std::vector<Armor>& importedArmors, std::vector<Weapon>& importedWeapons)
{
  std::vector<ItemBag> result;
  ItemBag tempBag;
  std::string itemName;
  std::ifstream file("../saved/ItemBag/itembags.txt");
  if (file.is_open()){
    std::string line;
    while (std::getline(file, line)) {
      std::istringstream iss(line);
      if (iss >> tempBag.bagName) {
        while (iss >> itemName) {
          bool itemFound = false;
          //search for itemname in vectors
          for (auto& item : importedItems) {
            if (itemName == item.getItemName()) {
              tempBag.storage.emplace_back(&item);
              itemFound = true;
              break;
            }
          }
          if (!itemFound) {
            for (auto& weapon : importedWeapons) {
              if (itemName == weapon.getItemName()) {
                tempBag.storage.emplace_back(&weapon);
                itemFound = true;
                break;
              }
            }
          }
          if (!itemFound) {
            for (auto& armor : importedArmors) {
              if (itemName == armor.getItemName()) {
                tempBag.storage.emplace_back(&armor);
                itemFound = true;
                break;
              }
            }
          }
          if (!itemFound) {
            throw std::runtime_error("itemName "+itemName+" not found in the items!\n");
          }
        }
        //emplace tempBag in result and reset tempBag = ItemBag()
        result.emplace_back(tempBag);
        tempBag = ItemBag();
      }
    }
  } else {
    throw std::runtime_error("unable to read from file ../saved/Item/itembags.txt\n");
  }
  file.close();
  return result;
}