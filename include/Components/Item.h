/**
 * @file Item.h
 * @brief parent file for items, different items can be created with different enchants to help make the
 * character stronger to be able to win his battles. It creates the necessary functions needed for items.
 * @author Mate Barabas and Steven Gingras
 */
#ifndef INC_345PROJECT_INCLUDE_COMPONENTS_ITEM_H_
#define INC_345PROJECT_INCLUDE_COMPONENTS_ITEM_H_

#include <string>

#include "../Static/Functions.h"
/**
 * @class Item
 * @brief class used for creating the different items that I character can equip and use
 * to their advantage in combat.
 */
class Item{
 public:
  Item(std::string itemNameParam, std::string itemTypeParam, std::string enchantTypeParam, int enchantLevelParam) : itemName(Functions::convertToUpper(itemNameParam)), itemType(Functions::convertToUpper(itemTypeParam)){
    //Set the enchant
    initPossibleEnchants();
    setEnchant(enchantTypeParam, enchantLevelParam);
  };
  Item() : itemName("INVALID_ITEM"), enchantLevel(0) {};
  // ACCESSORS ===============================
  std::string getItemName() const;
  std::string getItemType() const;
  std::string getEnchantType() const;
  int getEnchantLevel() const;
  // MUTATORS ================================
  void initPossibleEnchants();
  void setEnchant(std::string enchantTypeParam, int enchantLevelParam);
  void setEnchantLevel(int enchantLevelParam);
  int incrementEnchantLevel(int levelsToAdd);

 private:
  std::string itemName;
  std::string itemType;
  std::string enchantType;
  int enchantLevel;
  std::vector<std::string> possibleEnchants;
};
#endif //INC_345PROJECT_INCLUDE_COMPONENTS_ITEM_H_
