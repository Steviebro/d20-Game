#include "../include/Components/Character.h"
#include "../include/Static/Functions.h"

#include <iostream>

int main() {
  //Some sample items that we will bring in from files
  Armor leather_armor("leather_armor", "armor", "armor_class", 3, "light", 11);
  Armor medium_armor("medium_armor", "armor", "armor_class", 3, "medium", 14);
  Weapon str_sword("str_sword", "weapon", "damage_bonus", 2, "str", 5, "1d6");
  Item ring1("ring1", "ring", "constitution", 4);
  //Same here, sample itembag to bring in from file
  ItemBag starterItems("STARTER_ITEMS");
  starterItems.put(leather_armor);
  starterItems.put(medium_armor);
  starterItems.put(str_sword);
  starterItems.put(ring1);
  
  //create a character
  Character c1(1, "BULLY");
  c1.printCharacter();

  //put the starter items in c1's inventory
  c1.getEquipment().getInventory().putMany(starterItems,false);

  std::cout << "Now the Character has some equipment:\n";
  c1.getEquipment().printEquipment();
  c1.printCharacter();

  //equip the armor
  c1.getEquipment().equipItem("leather_armor");
  std::cout << "Armor equipped!\n";
  c1.printCharacter();

  //equip the other 2 items
  c1.getEquipment().equipItem("str_sword");
  c1.getEquipment().equipItem("ring1");
  std::cout << "Now the character has all items equipped\n";
  c1.printCharacter();

  //equip already equipped test
  c1.getEquipment().equipItem("medium_armor");
  std::cout << "Now the character has equipped a new armor\n";
  c1.printCharacter();

  //unequip test
  c1.getEquipment().unequipItem("armor");
  std::cout << "Now the character has his armor unequipped\n";
  c1.printCharacter();

  //equip it back test
  c1.getEquipment().equipItem("leather_armor");
  std::cout << "Now the character has equipped back his armor\n";
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