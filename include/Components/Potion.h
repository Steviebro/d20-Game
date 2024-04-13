#ifndef INC_345PROJECT_INCLUDE_COMPONENTS_POTION_H_
#define INC_345PROJECT_INCLUDE_COMPONENTS_POTION_H_
#include "Item.h"
#include "../Static/Dice.h"
class Potion : public Item {
 public:
  Potion(std::string itemNameParam, std::string itemTypeParam, std::string enchantTypeParam, int enchantLevelParam, std::string diceTyeParam) : Item(itemNameParam, itemTypeParam, enchantTypeParam, enchantLevelParam), diceType(diceTyeParam){};
  Potion() : Item(), diceType("-"){};
  std::string getDiceType();
  int takePotion();
 private:
  std::string diceType;

};
#endif //INC_345PROJECT_INCLUDE_COMPONENTS_POTION_H_
