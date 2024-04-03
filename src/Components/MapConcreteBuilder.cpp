/**
 * @file MapConcreteBuilder.cpp
 *
 * @brief the MapConcreteBuilder.cpp file contains the subclasses inheriting from the
 * MapBuilder class. It implements the virtual function of the parent class.
 *
 * @include iostream for outputting to the console
 *
 * @author Jungsoo Lee 40174025
 */

#include "../include/Components/MapConcreteBuilder.h"
#include "../include/Components/Item.h"
#include "../include/Components/ItemBag.h"
#include "../include/Components/Equipment.h"
#include "../include/Components/Character.h"
#include <iostream>

/**
 * @brief method for building the creatures with level 1
 * @param charLvl the level of the character chosen
 */
void MapConcreteBuilderBasic::buildCreatures(int charLvl) {
    std::cout << "There are " << m_map->getCreatures() << " creatures in the map\n\n";

    //Creature 1
    Armor light("leather_armor", "ARMOR", "ARMOR_CLASS", 0, "LIGHT", 11);
    Weapon atkStrAxe("str_axe", "WEAPON","ATTACK_BONUS", 0,"LIGHT", 11, "1d6");
    ItemBag i;
    ItemBag ie;
    Equipment equip(light, atkStrAxe, i, ie);
    Character creature1(1, "BULLY");
    creature1.setEquipment(equip);
    creature1.printCharacter();
    std::cout <<"\n";


    //Creature 2
    Equipment equip2(light, atkStrAxe, i, ie);
    Character creature2(1, "BULLY");
    creature1.setEquipment(equip);
    creature1.printCharacter();
    std::cout <<"\n";

}

/**
 * @brief method for building the chests with items of level 1
 * @param charLvl the level of the character chosen
 */
void MapConcreteBuilderBasic::buildChests(int charLvl) {
    std::cout << "There are " << m_map->getChests() << " chests in the map\n\n";
    //create 2 Items
    Item i1("leather helmet","helmet","intelligence",1);
    Item i2("tank ring","ring","constitution",1);

    //create chest ItemBag
    ItemBag chest1;

    //put both in the chest
    chest1.put(i1);
    chest1.put(i2);


    Item i3("metal helmet","helmet","intelligence",1);
    Item i4("dragon ring","ring","constitution",1);

    //create chest ItemBag
    ItemBag chest2;

    //put both in the chest
    chest2.put(i3);
    chest2.put(i4);

}

/**
 * @brief method for building creatures with the chosen level
 * @param charLvl the level of the character
 */
void MapConcreteBuilderComplex::buildCreatures(int charLvl) {
    std::cout << "There are " << m_map->getCreatures() << " creatures in the map\n\n";

    //Creature 1
    Armor light("leather_armor", "ARMOR", "ARMOR_CLASS", 0, "LIGHT", 11);
    Weapon atkStrAxe("str_axe", "WEAPON","ATTACK_BONUS", 0,"LIGHT", 11, "1d6");
    ItemBag i;
    ItemBag ie;
    Equipment equip(light, atkStrAxe, i, ie);
    Character creature1(1, "BULLY");
    creature1.setEquipment(equip);
    creature1.printCharacter();
    std::cout <<"\n";


    //Creature 2
    Equipment equip2(light, atkStrAxe, i, ie);
    Character creature2(1, "BULLY");
    creature1.setEquipment(equip);
    creature1.printCharacter();
    std::cout <<"\n";

}

/**
 * @brief method for building the chests with items of the chosen level
 * @param charLvl the level of the character
 */
void MapConcreteBuilderComplex::buildChests(int charLvl) {
    std::cout << "There are " << m_map->getChests() << " chests in the map\n\n";

    //create 2 Items
    Item i1("shaky helmet","helmet","intelligence",charLvl);
    Item i2("loose ring","ring","constitution",charLvl);

    //create chest ItemBag
    ItemBag chest1;

    //put both in the chest
    chest1.put(i1);
    chest1.put(i2);


    Item i3("human helmet","helmet","intelligence",charLvl);
    Item i4("gnome ring","ring","constitution",charLvl);

    //create chest ItemBag
    ItemBag chest2;

    //put both in the chest
    chest2.put(i3);
    chest2.put(i4);

    //to see chest contents
}
