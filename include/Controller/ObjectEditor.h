//
// Created by Mate Barabas on 2024-04-12.
//

#ifndef INC_345PROJECT_INCLUDE_CONTROLLER_OBJECTEDITOR_H_
#define INC_345PROJECT_INCLUDE_CONTROLLER_OBJECTEDITOR_H_
#include "../Components/Character.h"
#include "../Components/MapGeneration.h"

#include <vector>
#include <iostream>

class ObjectEditor {
 public:
  ObjectEditor();

  void mainMenu();
  void saveObjects();

  void createMap();
  void createCampaign();
  void createItem();



 private:
  std::vector<Item> items;
  std::vector<Weapon> weapons;
  std::vector<Armor> armors;
  std::vector<ItemBag> itemBags;

  std::vector<Equipment> equipments;
  //std::vector<Character> players;
  std::vector<Character> enemies;

  std::vector<GridMap> maps;
  std::vector<std::list<std::string>> campaigns;
};




#endif //INC_345PROJECT_INCLUDE_CONTROLLER_OBJECTEDITOR_H_
