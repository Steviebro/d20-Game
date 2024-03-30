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
  Equipment(Armor& armorParam, Weapon& weaponParam, ItemBag& otherEquippedParam, ItemBag& inventoryParam) : armor(armorParam), weapon(weaponParam),
                                                                                                        otherEquipped(otherEquippedParam), inventory(inventoryParam) {};

  Equipment() {};
  Armor getArmor() const;
  Weapon getWeapon() const;


  void equipItem(Item itemToEquip);
  void unequipItem(std::string itemType);
  void equipArmor(Armor& armorParam);
  void equipWeapon(Weapon& weaponParam);

  int sumEnchants(std::string enchant) const;

private:
  Armor armor;
  Weapon weapon;
  ItemBag otherEquipped;
  ItemBag inventory;
};


#endif //INC_345PROJECT_INCLUDE_COMPONENTS_EQUIPMENT_H_
