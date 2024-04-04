#ifndef INC_345PROJECT_INCLUDE_COMPONENTS_GAMEMANAGER_H_
#define INC_345PROJECT_INCLUDE_COMPONENTS_GAMEMANAGER_H_
#include "../Components/Character.h"

#include <vector>
#include <iostream>

class GameManager {
public:
    GameManager() : items(Item::readItemsFromFile()), weapons(Weapon::readWeaponsFromFile()), armors(Armor::readArmorsFromFile()),
    itemBags(ItemBag::readBagsFromFile(items,armors,weapons)),//TOADD HERE: maps, campaigns, characters
    player(initPlayer())
    {

    };
    
    Character initPlayer();
    Character createNewCharacter();

    void saveObjects();


private:
    Character player;
    std::vector<Item> items;
    std::vector<Weapon> weapons;
    std::vector<Armor> armors;
    std::vector<ItemBag> itemBags;
    //TOADD: maps, campaigns, characters

};

#endif //INC_345PROJECT_INCLUDE_COMPONENTS_GAMEMANAGER_H_