/**
 * @file ItemBag.h
 * @brief this file is used for creating the item bag
 * which will hold all the different items that a character has so they
 * can equip and use them.
 * @ref Item.h
 * @author Mate Barabas and Steven Gingras
 */
#ifndef INC_345PROJECT_INCLUDE_COMPONENTS_ITEMBAG_H_
#define INC_345PROJECT_INCLUDE_COMPONENTS_ITEMBAG_H_
#include "Item.h"

/**
 *@class ItemBag
 * @brief this class is used for the item bag object which will hold
 * all the different items a character has.
 */
class ItemBag {
public:
  ItemBag(std::string bagNameParam) : bagName(Functions::convertToUpper(bagNameParam)) {};

  ItemBag() : bagName("DEFAULT_BAG") {};

  bool hasItemType(std::string itemType);
  void put(Item& toPut);
  Item& get(std::string itemName);
  Item& getByType(std::string itemType);
  Item& remove(std::string itemName);
  Item& removeByType(std::string itemTypeToRemove);

  int sumEnchants(std::string enchant) const;

private:
  std::string bagName;
  std::vector<Item> storage;
};


#endif //INC_345PROJECT_INCLUDE_COMPONENTS_ITEMBAG_H_
