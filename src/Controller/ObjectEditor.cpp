//
// Created by Mate Barabas on 2024-04-12.
//
#include "../../include/Controller/ObjectEditor.h"

ObjectEditor::ObjectEditor() : items(Item::readItemsFromFile()), weapons(Weapon::readWeaponsFromFile()), armors(Armor::readArmorsFromFile()),
                               itemBags(ItemBag::readBagsFromFile(items,armors,weapons)), equipments(Equipment::readEquipmentsFromFile(itemBags)),
                               enemies(Character::readCharactersFromFile("enemies",equipments)),
                               maps(GridMap::readMapsFromFile(itemBags,enemies)), campaigns(GridMap::readCampaignsFromFile(maps))
{
  mainMenu();
}

void ObjectEditor::mainMenu()
{
  char input;
  std::cout << "OBJECT CREATOR ====================!\n";
  do {
    std::cout << "Please select from the below choices what you want to create!\n"
              << "1 - Create Maps\n"
              << "2 - Create Campaigns\n"
              << "3 - Create Items\n"
              << "0 - Save all changes and return to the main menu\n"
              << "Your selection: ";
    std::cin >> input;

    switch(input) {
      case '1':
        createMap();
        break;
      case '2':
        createCampaign();
        break;
      case '3':
        createItem();
        break;
      case '0':
        break;
      default:
        std::cout << "You have entered an invalid input, please try again!\n";
    }
  } while (input != '0');

  saveObjects();
}

void ObjectEditor::saveObjects()
{
  Item::writeItemsToFile(items);
  Weapon::writeWeaponsToFile(weapons);
  Armor::writeArmorsToFile(armors);
  ItemBag::writeBagsToFile(itemBags);

  Equipment::writeEquipmentsToFile(equipments);
  //Character::writeCharactersToFile(players,"players");
  Character::writeCharactersToFile(enemies,"enemies");
  GridMap::writeMapsToFile(maps);
  GridMap::writeCampaignsToFile(campaigns);
}

void ObjectEditor::createMap() {
  /**
   * GridMap(std::string mapNameP, const int coords[8], std::vector<std::pair<std::pair<int,int>,ItemBag>> chestsP, std::vector<std::pair<std::pair<int,int>,Character>> enemiesP, std::vector<std::pair<int,int>> wallsP)
  : mapName(mapNameP), width(coords[0]), height(coords[1]), entrance(coords[2],coords[3]), exit(coords[4],coords[5]), objective(coords[6],coords[7]), chests(chestsP), enemies(enemiesP), walls(wallsP)
  {
    map.resize(height, std::vector<char>(width, ' '));
    GridMap::populateMap();
  }
  */
  std::string strInput;
  char charInput;
  bool validInput;

  std::string mapName;
  int coords[8];
  std::vector<std::pair<std::pair<int, int>, ItemBag>> chestsP;
  std::vector<std::pair<std::pair<int, int>, Character>> enemiesP;
  std::vector<std::pair<int, int>> wallsP;
  std::vector<std::pair<int, int>> friendlyP;

  std::cout << "MAP CREATOR ====================!\n";
  do {
    validInput = true;
    std::cout << "Enter a UNIQUE name for your map: ";
    std::cin >> mapName;
    Functions::convertToUpper(mapName);

    for (auto &map : maps) {
      if (map.getMapName() == mapName) {
        validInput = false;
      }
    }
  } while (!validInput);

  std::cout << "Enter the map's width: ";
  std::cin >> coords[0];
  std::cout << "Enter the map's height: ";
  std::cin >> coords[1];

  do {
    validInput = true;
    std::cout << "Map entrance:\n";
    std::cout << "Enter a value for x: ";
    std::cin >> coords[2];
    std::cout << "Enter a value for y: ";
    std::cin >> coords[3];

    //validate that the entrance position is valid (UNFINISHED)=================================================================================
    if (false) {
      validInput = false;
    }
  } while (!validInput);

  do {
      validInput = true;
      std::cout << "Map exit:\n";
      std::cout << "Enter a value for x: ";
      std::cin >> coords[4];
      std::cout << "Enter a value for y: ";
      std::cin >> coords[5];

      //validate that the exit position is valid (UNFINISHED)=================================================================================
      if (false) {
        validInput = false;
      }
  } while (!validInput);

  do {
      validInput = true;
      std::cout << "Objective location:\n";
      std::cout << "Enter a value for x: ";
      std::cin >> coords[6];
      std::cout << "Enter a value for y: ";
      std::cin >> coords[7];

      //validate that the objective position is valid (UNFINISHED)=================================================================================
      if (false) {
        validInput = false;
      }
  } while (!validInput);

    //Chests
  do {
      std::pair<std::pair<int,int>, ItemBag> toAdd;
      std::cout << "Select the chest you want to add from the following list:\n";
      for (auto &chest : itemBags) {
        std::cout << chest.getBagName() << "\n";
      }
      std::cout << "Your selection (or enter stop to stop): ";
      std::cin >> strInput;
      Functions::convertToUpper(strInput);

      if (strInput != "STOP") {
        for (auto &bag : itemBags) {
          if (bag.getBagName() == strInput) {
            toAdd.second = bag;
            std::cout << "Where do you want to place the chest?\n";
            std::cout << "Enter a value for x: ";
            std::cin >>  toAdd.first.first;
            std::cout << "Enter a value for y: ";
            std::cin >> toAdd.first.second;

            // if valid:
            chestsP.emplace_back(toAdd);
          }
        }
      }
  } while (strInput != "STOP");

  //enemies
  do {
    std::pair<std::pair<int,int>, Character> toAdd;
    std::cout << "Select the enemy you want to add from the following list:\n";
    for (auto &enemy : enemies) {
      std::cout << enemy.getName() << "\n";
    }
    std::cout << "Your selection (or enter stop to stop): ";
    std::cin >> strInput;
    Functions::convertToUpper(strInput);

    if (strInput != "STOP") {
      for (auto &enemy : enemies) {
        if (enemy.getName() == strInput) {
          toAdd.second = enemy;
          std::cout << "Where do you want to place the enemy?\n";
          std::cout << "Enter a value for x: ";
          std::cin >>  toAdd.first.first;
          std::cout << "Enter a value for y: ";
          std::cin >> toAdd.first.second;

          // if valid:
          enemiesP.emplace_back(toAdd);
        }
      }
    }
  } while (strInput != "STOP");

  //Walls
  do {
    pair<int,int> toAdd;
    std::cout << "Adding walls\n";
    std::cout << "Enter any key to continue or 0 to stop adding walls: ";
    std::cin >> charInput;
    if (charInput != '0') {
      std::cout << "Enter a value for x: ";
      std::cin >>  toAdd.first;
      std::cout << "Enter a value for y: ";
      std::cin >> toAdd.second;

      //if valid:
      wallsP.emplace_back(toAdd);
    }
  } while (charInput != '0');

  //friendly npcs
  do {
    pair<int,int> toAdd;
    std::cout << "Adding friendly NPCs\n";
    std::cout << "Enter any key to continue or 0 to stop adding friendly NPCs: ";
    std::cin >> charInput;
    if (charInput != '0') {
      std::cout << "Enter a value for x: ";
      std::cin >>  toAdd.first;
      std::cout << "Enter a value for y: ";
      std::cin >> toAdd.second;

      //if valid:
      friendlyP.emplace_back(toAdd);
    }
  } while (charInput != '0');

  GridMap addedMap(mapName,coords,chestsP,enemiesP,wallsP,friendlyP);
  maps.emplace_back(addedMap);
}

void ObjectEditor::createCampaign()
{
  bool validInput;
  std::string strInput;
  std::list<std::string> toAdd;
  std::cout << "Campaign creator\n";

  do {
    validInput = true;
    std::cout << "Enter a UNIQUE name for your new campaign: ";
    std::cin >> strInput;
    Functions::convertToUpper(strInput);

    for (auto& campaign : campaigns) {
      if (*campaign.begin() == strInput) {
        validInput = false;
      }
    }
  } while (!validInput);

  toAdd.emplace_back(strInput);//name put in first pos of list

  std::cout << "Select from the maps below to add to your campaign:\n";
  for (auto& map : maps) {
    std::cout << map.getMapName() << "\n";
  }
  do {
    std::cout << "Your selection (or enter stop): ";
    std::cin >> strInput;
    Functions::convertToUpper(strInput);

    for (auto& map : maps) {
      if (map.getMapName() == strInput) {
        toAdd.emplace_back(map.getMapName());
      }
    }
  } while (strInput != "STOP");

  campaigns.emplace_back(toAdd);
}

void ObjectEditor::createItem()
{
  bool validInput;
  std::string itemName;
  std::string itemType;
  std::string enchantType;
  int enchantLevel;

  do {
    validInput = true;
    std::cout<<"INPUT A UNIQUE NEW ITEM NAME: ";
    std::cin>>itemName;
    Functions::convertToUpper(itemName);

    // if item already exists
    for (auto& item : items) {
      if (item.getItemName() == itemName) {
        validInput = false;
      }
    }
  } while (!validInput);

  std::cout << "INPUT ITEM TYPE: ";
  std::cin >> itemType;
  Functions::convertToUpper(itemType);

  std::cout << "INPUT ENCHANT TYPE: ";
  std::cin >> enchantType;
  Functions::convertToUpper(enchantType);

  std::cout << "INPUT ENCHANT LEVEL, MAX 5: ";
  std::cin >> enchantLevel;
  Item toAdd(itemName,itemType,enchantType,enchantLevel);

//  do {
//    validInput = true;
//    try {
//      std::cout << "INPUT ITEM TYPE: ";
//      std::cin >> itemType;
//      Functions::convertToUpper(itemType);
//      std::cout << "INPUT ENCHANT TYPE: ";
//      std::cin >> enchantType;
//      Functions::convertToUpper(enchantType);
//      std::cout << "INPUT ENCHANT LEVEL, MAX 5: ";
//      std::cin >> enchantLevel;
//      Item toAdd(itemName,itemType,enchantType,enchantLevel);
//    } catch (exception e) {
//      std::cout << "Error creating item\n";
//      validInput = false;
//    }
//  } while (!validInput);

  //Item toAdd(itemName,itemType,enchantType,enchantLevel);
  items.emplace_back(toAdd);
}

/*    if (coords[2] >= 0 && coords[3] >= 0
        && coords[2] < coords[0]
        && coords[3] < coords[1]) { //checking within range of map
      if ((coords[2] != 0 && coords[2] != coords[0] - 1)
          || (coords[3] != 0 && coords[3] != coords[1] - 1)) {//checking not a corner
        // if x == 0 or width and y == 0 or height
        if ((coords[2] == 0 || coords[3] == 0 || coords[2] == coords[0] - 1 || coords[3] == coords[1] - 1)
            && !(coords[2] == 0 && coords[3] == 0) && !(coords[2] == 0 && coords[3] == coords[1] - 1)
            && !(coords[2] == coords[0] - 1 && coords[3] == 0) && !(coords[2] == coords[0] - 1
            && coords[3] == coords[1] - 1)) { //checking edge
          validInput = true;
        } else {
          std::cout << "Invalid inputs, MUST put the entrance at the edge of the map.Please try again.\n";
        }
      } else {
        std::cout << "Invalid inputs, cannot put the entrance on a corner.Please try again.\n";
      }
    } else {
      std::cout << "Invalid inputs, values must lie within the width and height of the map. Please try again.\n";
    }
  } while (!validInput);*/