#include "../include/Components/Character.h"
#include "../include/Static/Functions.h"

#include <iostream>

int main() {
  Armor light("leather_armor", "ARMOR", "ARMOR_CLASS", 0, "LIGHT", 11);
  Weapon sword("sword_weapon", "WEAPON", "ATTACK_BONUS", 0, "STR", 5, "1d6");
  ItemBag i;
  ItemBag ie;
  Equipment equip(light, sword, i, ie);

  Character c1(1, "BULLY");
    c1.printCharacter();
    c1.setEquipment(equip);
    c1.printCharacter();

//    Character c2(12, "NImble");
//    c2.printCharacter();
//
//    Character c3(21, "taNk");
//    c3.printCharacter();
//
//    Character c4(-1000, "bullY");
//    c4.printCharacter();
    
    

}