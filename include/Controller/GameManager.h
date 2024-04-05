#ifndef INC_345PROJECT_INCLUDE_COMPONENTS_GAMEMANAGER_H_
#define INC_345PROJECT_INCLUDE_COMPONENTS_GAMEMANAGER_H_
#include "../Components/Character.h"
#include "../Components/MapGeneration.h"

#include <vector>
#include <iostream>

class GameManager {
public:
    GameManager() : newPlayerCreated(false), items(Item::readItemsFromFile()), weapons(Weapon::readWeaponsFromFile()), armors(Armor::readArmorsFromFile()),
    itemBags(ItemBag::readBagsFromFile(items,armors,weapons)), equipments(Equipment::readEquipmentsFromFile(itemBags)),
    players(Character::readCharactersFromFile("players",equipments)), enemies(Character::readCharactersFromFile("enemies",equipments)),
    maps(GridMap::readMapsFromFile(itemBags,enemies)),//TOADD HERE: campaigns
    player()
    {
        player = initPlayer();
        if (newPlayerCreated) { equipNewPlayer(); }
        std::cout << "Player successfully created or imported from saved:\n";
        player.printCharacter();
        startGame();
    };
    
    Character initPlayer();
    Character createNewPlayer();
    void equipNewPlayer();
    Character selectExistingPlayer();

    void startGame();

    void saveObjects();


private:
    bool newPlayerCreated;
    Character player;
    //std::vector<Map> campaignMaps; (for CHOSEN campaign)

    std::vector<Item> items;
    std::vector<Weapon> weapons;
    std::vector<Armor> armors;
    std::vector<ItemBag> itemBags;

    std::vector<Equipment> equipments;
    std::vector<Character> players;
    std::vector<Character> enemies;
    std::vector<GridMap> maps;
    //TOADD: maps, campaigns

};

#endif //INC_345PROJECT_INCLUDE_COMPONENTS_GAMEMANAGER_H_