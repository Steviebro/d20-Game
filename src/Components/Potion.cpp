#include "../include/Components/Potion.h"
std::string Potion::getDiceType()
{
  return diceType;
}

int Potion::takePotion() {
   int diceRoll = Dice::rollDice("2d4");
   return diceRoll;
}