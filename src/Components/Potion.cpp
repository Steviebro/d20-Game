#include "../include/Components/Potion.h"
std::string Potion::getDiceType()
{
  return diceType;
}

void Potion::takePotion(Character &player) {
  int diceRoll = Dice::rollDice(getDiceType());
  player.healDamage(diceRoll + getEnchantLevel());
}