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
#include <iostream>//for print method
#include <fstream>
#include <sstream>

#include "Item.h"
#include "Armor.h"
#include "Weapon.h"

/**
 *@class ItemBag
 * @brief this class is used for the item bag object which will hold
 * all the different items a character has.
 */
class ItemBag {
public:
  ItemBag(std::string bagNameParam) : bagName(Functions::convertToUpper(bagNameParam)) {};

  ItemBag() : bagName("DEFAULT_BAG") {};
  // ACCESSOR =======================================
  std::string getBagName() const;

  // INSERTION =======================================
  void put(Item& toPut);
  int putMany(ItemBag& bagToPut, bool emptyContents);

  // RETREIVAL AND REMOVAL =================================================
  Item* getOrRemove(std::string targetItemNameOrType, bool removeItem, bool searchByType);
  
  // OTHER GAME FUNCTIONS =======================================
  bool hasItemType(std::string itemType);
  int sumEnchants(std::string enchant) const;

  // FILE I/O & PRINTING =======================================
  std::string toString() const;
  void printBag() const;
  static void writeBagsToFile(std::vector<ItemBag>& bagsToWrite);
  static std::vector<ItemBag> readBagsFromFile(std::vector<Item>& importedItems, std::vector<Armor>& importedArmors, std::vector<Weapon>& importedWeapons);

private:
  std::string bagName;
  std::vector<Item*> storage;
};


#endif //INC_345PROJECT_INCLUDE_COMPONENTS_ITEMBAG_H_
