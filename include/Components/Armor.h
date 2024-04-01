/**
 * @file Armor.h
 * @brief this file is used for creating the armor object
 * that characters equip to icnrease their ac stat to make it harder
 * to hit them.
 * @ref Item.h
 * @author Mate Barabas and Steven Gingras
 */
#ifndef INC_345PROJECT_INCLUDE_COMPONENTS_ARMOR_H_
#define INC_345PROJECT_INCLUDE_COMPONENTS_ARMOR_H_
#include "Item.h"

/**
 * @class Armor
 * @brief this class is used for creating the armor object according to
 * the d20 rules.
 * It inherits from the item object.
 */
class Armor : public Item {
 public:
  Armor(std::string itemNameParam, std::string itemTypeParam, std::string enchantTypeParam, int enchantLevelParam, std::string armorTypeParam, int baseArmorACParam) : Item(itemNameParam, itemTypeParam, enchantTypeParam, enchantLevelParam), armorType(Functions::convertToUpper(armorTypeParam)), baseArmorAC(baseArmorACParam){};
  Armor() : Item(), armorType("-"), baseArmorAC(0) {};
  // ACCESSORS =====================================
  std::string getArmorType();
  int getBaseArmorAC();

  std::string toString() const;
 private:
  std::string armorType;
  int baseArmorAC;
};
#endif //INC_345PROJECT_INCLUDE_COMPONENTS_ARMOR_H_
