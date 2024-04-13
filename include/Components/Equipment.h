/**
 * @file Equipment.h
 * @brief This file is used for the equipment that a character has
 * it equips the armor, weapon an inventory and other items he has equipped
 * @ref ItemBag.h
 * @ref Armor.h
 * @ref Weapon.h
 * @author Mate Barabas and Steven Gingras
 */
#ifndef INC_345PROJECT_INCLUDE_COMPONENTS_EQUIPMENT_H_
#define INC_345PROJECT_INCLUDE_COMPONENTS_EQUIPMENT_H_
#include "ItemBag.h"
#include "Armor.h"
#include "Weapon.h"
#include "Potion.h"

/**
 * @class Equipment
 * @brief Equipment system that a character has
 */
class Equipment {
public:
  Equipment(std::string nameParam, ItemBag& equippedParam, ItemBag& inventoryParam) : name(nameParam), equipped(equippedParam), inventory(inventoryParam) {};

  Equipment(std::string nameParam) : name(Functions::convertToUpper(nameParam)), equipped(Functions::convertToUpper(nameParam)+"E"), inventory(Functions::convertToUpper(nameParam)+"I") {};
  // ACCESSORS =============================================
  ItemBag& getEquipped();
  ItemBag& getInventory();
  Item* getEquippedItem(std::string itemType);
  Armor* getArmor();
  Weapon* getWeapon();
  std::string getName();

  // MUTATORS ==============================================
  bool equipItem(std::string itemNameToEquip);
  bool unequipItem(std::string itemTypeToUnequip);
  void lootChestOrBody(ItemBag& toLoot);

  // OTHER ==============================================
  std::string toString() const;
  void printEquipment() const;
  static void writeEquipmentsToFile(std::vector<Equipment>& equipmentsToWrite);
  static std::vector<Equipment> readEquipmentsFromFile(std::vector<ItemBag> itemBags);

private:
  std::string name;
  ItemBag equipped;
  ItemBag inventory;
};


#endif //INC_345PROJECT_INCLUDE_COMPONENTS_EQUIPMENT_H_
