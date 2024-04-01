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

/**
 * @class Equipment
 * @brief Equipment system that a character has
 */
class Equipment {
public:
  Equipment(ItemBag& equippedParam, ItemBag& inventoryParam) : equipped(equippedParam), inventory(inventoryParam) {};

  Equipment() : equipped("EQUIPPED_ITEMS"), inventory("INVENTORY_ITEMS") {};
  // ACCESSORS =============================================
  ItemBag& getEquipped();
  ItemBag& getInventory();
  Item* getEquippedItem(std::string itemType);
  Armor* getArmor();
  Weapon* getWeapon();

  // MUTATORS ==============================================
  bool equipItem(std::string itemNameToEquip);
  bool unequipItem(std::string itemTypeToUnequip);
  void lootChestOrBody(ItemBag& toLoot);

  // OTHER ==============================================
  std::string toString() const;
  void printEquipment() const;

private:
  //Armor armor;
  //Weapon weapon;
  ItemBag equipped;
  ItemBag inventory;
};


#endif //INC_345PROJECT_INCLUDE_COMPONENTS_EQUIPMENT_H_
