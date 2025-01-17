/**
 * @file Item.cpp
 * @brief cpp files which writes the functionalities for the item methods
 * that are needed for improving our characters.
 * @ref Item.h
 * @author Mate Barabas and Steven Gingras
 */
#include "../include/Components/Item.h"

/**
 * @brief method that initializes the possible enchants that an item can have.
 */
bool Item::initPossibleEnchants()
{
  if (itemType == "HELMET") {
    possibleEnchants = {"INTELLIGENCE", "WISDOM", "ARMOR_CLASS"};
  } else if (itemType == "ARMOR" || itemType == "SHIELD") {
    possibleEnchants = {"ARMOR_CLASS"};
  } else if (itemType == "RING") {
    possibleEnchants = {"ARMOR_CLASS", "STRENGTH", "CONSTITUTION", "WISDOM", "CHARISMA"};
  } else if (itemType == "BELT") {
    possibleEnchants = {"CONSTITUTION", "STRENGTH"};
  } else if (itemType == "BOOTS") {
    possibleEnchants = {"ARMOR_CLASS", "DEXTERITY"};
  } else if (itemType == "WEAPON") {
    possibleEnchants = {"ATTACK_BONUS", "DAMAGE_BONUS"};
  } else if(itemType == "POTION"){
    possibleEnchants = { "-" };
  } else {
    throw std::runtime_error("Invalid item type passed: "+itemType+". Item type must be part of these 7 types (NOT case-sensitive): helmet, armor, shield, ring, belt, boots, weapon");
  }

  bool validEnchant = false;
  for (auto& possibleEnchant : possibleEnchants) {
    if (possibleEnchant == enchantType) {
      validEnchant = true;
      break;
    }
  }
  return validEnchant;
}


/**
 * @brief method which sets the enchant type for the items according to the possible enchants,
 * enchantType and level;
 * @param enchantTypeParam what will be improved
 * @param enchantLevelParam bonus of improvement
 */
void Item::setEnchant(std::string enchantTypeParam, int enchantLevelParam)
{
  if (enchantTypeParam == "-") {
    enchantType = "-";
    enchantLevel = 0;
    return;
  }

  Functions::convertToUpper(enchantTypeParam);

  //Validate enchantType
  bool validEnchant = false;
  for (auto& e : possibleEnchants) {
    if (e == enchantTypeParam) {
      validEnchant = true;
      break;
    }
  }

  if (!validEnchant) {
    throw std::runtime_error("Invalid enchantType "+enchantTypeParam+" for the itemType "+itemType);
  }
  enchantType = enchantTypeParam;
  setEnchantLevel(enchantLevelParam);

}

/**
 * @brief method that returns the enchant type
 * @return enchant type
 */
std::string Item::getEnchantType() const {
  return enchantType;
}

/**
 * @brief method that sets the enchant level to a minimum of 1 and max of 5.
 * @param enchantLevelParam level that enchant will be set too
 */
void Item::setEnchantLevel(int enchantLevelParam)
{
  if (enchantType == "-") {
    return;
  }
  if (enchantLevelParam < 1) {
    enchantLevel = 1;
  } else if (enchantLevelParam > 5) {
    enchantLevel = 5;
  } else {
    enchantLevel = enchantLevelParam;
  }
}

/**
 * @brief method that gets the enchant level
 * @return enchant level
 */
int Item::getEnchantLevel() const {
  return enchantLevel;
}

std::vector<std::string> Item::getPossibleEnchants() const
{
  return possibleEnchants;
}

/**
 * @brief method that gets the item name
 * @return item name
 */
std::string Item::getItemName() const {
  return itemName;
}

/**
 * @brief method that gets the item type
 * @return item type
 */
std::string Item::getItemType() const {
  return itemType;
}

/**
 * @brief method that will increase the enchant level bonus by a given number
 * @param levelsToAdd number to increase enchant by
 * @return new enchant level
 */
int Item::incrementEnchantLevel(int levelsToAdd)
{
  if (levelsToAdd < 1) {
    return enchantLevel;
  }
  enchantLevel += levelsToAdd;
  if (enchantLevel > 5) {
    enchantLevel = 5;
  }
  return enchantLevel;
}

std::string Item::toString() const
{
  return itemName + " " + itemType + " " + enchantType + " " + std::to_string(enchantLevel);
}

void Item::writeItemsToFile(std::vector<Item>& itemsToWrite)
{
  std::string fileName = "../saved/Item/items.txt";
  std::ofstream file(fileName);

  if (file.is_open()) {
    for (auto& item : itemsToWrite) {
      file << item.toString() << "\n";
    }
    file.close();
  } else {
    throw std::runtime_error("unable to write to file "+fileName+"\n");
  }
}

std::vector<Item> Item::readItemsFromFile()
{
  std::vector<Item> result;
  Item temp;
  std::ifstream file("../saved/Item/items.txt");
  if (file.is_open()){
    while (file >> temp.itemName >> temp.itemType >> temp.enchantType >> temp.enchantLevel) {
      if (temp.initPossibleEnchants()) {
        result.emplace_back(temp);
      } else {
        throw std::invalid_argument("In file ../saved/Item/items.txt, itemType "+temp.itemType+" is incompatible with the enchantType "+temp.enchantType+". Item not created!\n");
      }
    }
  } else {
    throw std::runtime_error("unable to read from file ../saved/Item/items.txt\n");
  }
  file.close();
  return result;
}