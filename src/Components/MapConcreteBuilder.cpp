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

#include "../../include/Components/MapConcreteBuilder.h"
#include "../../include/Components/Item.h"
#include "../../include/Components/ItemBag.h"
#include "../../include/Static/Dice.h"
#include "../../include/Components/Equipment.h"
#include "../../include/Components/Character.h"
#include <iostream>

/**
 * @brief method for building the creatures with level 1
 * @param charLvl the level of the character chosen
 */
void MapConcreteBuilderBasic::buildCreatures(int charLvl) {
    Dice dice;
    std::cout << "There are " << m_map->getCreatures() << " creatures in the map\n\n";

    //Creature 1
    Item atkStrAxe("atkStrAxe", "weapon","attack bonus", 2, "strength");
    AbilityScores scores1(1);
    scores1.setCreatureScores();
    scores1.setProficiency(1);
    scores1.setModifiers();
    Equipment equipCreature1(1);
    equipCreature1.addItem(atkStrAxe);
    Character creature1(1, scores1, equipCreature1, dice);
    creature1.createCharacter();
    std::cout << "Creature 1:\n";
    creature1.printCharacter();
    std::cout <<"\n";


    //Creature 2
    AbilityScores scores2(1);
    scores2.setCreatureScores();
    scores2.setProficiency(1);
    scores2.setModifiers();
    Equipment equipCreature2(1);
    equipCreature2.addItem(atkStrAxe);
    Character creature2(1, scores2, equipCreature2, dice);
    creature2.createCharacter();
    std::cout << "Creature 2:\n";
    creature2.printCharacter();
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
    ItemBag chest1("CHEST 1",10);

    //put both in the chest
    chest1.put(i1);
    chest1.put(i2);

    //to see chest contents
    std::cout << chest1.getAllInfo() << "\n";

    Item i3("metal helmet","helmet","intelligence",1);
    Item i4("dragon ring","ring","constitution",1);

    //create chest ItemBag
    ItemBag chest2("CHEST 2",10);

    //put both in the chest
    chest2.put(i3);
    chest2.put(i4);

    //to see chest contents
    std::cout << chest2.getAllInfo() << "\n";
}

/**
 * @brief method for building creatures with the chosen level
 * @param charLvl the level of the character
 */
void MapConcreteBuilderComplex::buildCreatures(int charLvl) {
    Dice dice;
    std::cout << "There are " << m_map->getCreatures() << " creatures in the map\n\n";

    //Creature 1
    Item atkStrAxe("atkStrAxe", "weapon","attack bonus", 2, "strength");
    AbilityScores scores1(charLvl);
    scores1.setCreatureScores();
    scores1.setProficiency(charLvl);
    scores1.setModifiers();
    Equipment equipCreature1(1);
    equipCreature1.addItem(atkStrAxe);
    Character creature1(charLvl, scores1, equipCreature1, dice);
    creature1.createCharacter();
    std::cout << "Creature 1:\n";
    creature1.printCharacter();
    std::cout <<"\n";

    //Creature 2
    AbilityScores scores2(charLvl);
    scores2.setCreatureScores();
    scores2.setProficiency(charLvl);
    scores2.setModifiers();
    Equipment equipCreature2(1);
    equipCreature2.addItem(atkStrAxe);
    Character creature2(charLvl, scores2, equipCreature2, dice);
    creature2.createCharacter();
    std::cout << "Creature 2:\n";
    creature2.printCharacter();
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
    ItemBag chest1("CHEST 1",10);

    //put both in the chest
    chest1.put(i1);
    chest1.put(i2);

    //to see chest contents
    std::cout << chest1.getAllInfo() << "\n";

    Item i3("human helmet","helmet","intelligence",charLvl);
    Item i4("gnome ring","ring","constitution",charLvl);

    //create chest ItemBag
    ItemBag chest2("CHEST 2",10);

    //put both in the chest
    chest2.put(i3);
    chest2.put(i4);

    //to see chest contents
    std::cout << chest2.getAllInfo() << "\n";
}
