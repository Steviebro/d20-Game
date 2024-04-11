#include "../../include/Controller/Combat.h"
bool Combat::attack(Character& attacker, Character& defender)
{
  int damage;
  //attack roll
  int touch = attackRoll(attacker, defender);

  if (touch == 0) {
    std::cout << "The Character " << attacker.getName() << " got a MISS!\n";
    return false;
  }else if( touch ==2 ){
    std::cout << "The Character " << attacker.getName() << " got a CRITICAL HIT!\n";
    damage = damageRoll(attacker, defender) + damageRoll(attacker, defender);
  } else {
    std::cout << "The Character " << attacker.getName() << " got a HIT!\n";
    damage = damageRoll(attacker, defender);
  }
  //do damage
  int defenderHp = defender.takeDamage(damage);
  //if killed, do exp
  if(defenderHp <=0){
    std::cout << "The Character " << defender.getName() << " has taken " << damage << " damage and is now dead!\n";
    return true;
  } else {
    std::cout << "The Character " << defender.getName() << " has taken " << damage << " damage and is now at " << defender.getHP() << " hit points.\n";
    return false;
  }
}

int Combat::attackRoll(Character& attacker, Character& defender)
{
  int diceRoll = Dice::rollDice("1d20");


  if (diceRoll == 1) {
    std::cout<<"Attack roll rolled a " << diceRoll << " You need a " << defender.getArmorClass() << " to hit!\n";
    return 0;
  } else if (diceRoll == 20) {
    std::cout<<"Attack roll rolled a " << diceRoll << " You need a " << defender.getArmorClass() << " to hit!\n";
    return 2;
  } else if (diceRoll + attacker.getAttackBonus() >= defender.getArmorClass()){
    std::cout<<"Attack roll rolled a " << diceRoll + attacker.getAttackBonus() << " You need a " << defender.getArmorClass() << " to hit!\n";
    return 1;
  }

  return 0;

}

int Combat::damageRoll(Character& attacker, Character& defender)
{
  //get the weapon's damage
  Weapon* weapon = attacker.getEquipment().getWeapon();

  int damage = Dice::rollDice(weapon->getDiceType()) + attacker.getDamageBonus();

  return damage;
}