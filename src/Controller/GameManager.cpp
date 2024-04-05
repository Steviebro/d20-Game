#include "../../include/Controller/GameManager.h"

Character GameManager::initPlayer()
{
  char input;
  std::cout << "GAME MANAGER ====================!\n";
  do {
    std::cout << "Would you like to create a new Player Character or select an existing one?\n"
    << "1 - Create New Player Character!\n"
    << "2 - Select from existing.\n"
    << "Your selection: ";
    std::cin >> input;

    switch(input) {
      case '1':
      return createNewPlayer();
      break;
      case '2':
      return selectExistingPlayer();
      break;
      default:
      std::cout << "You have entered an invalid input, please try again!\n";
    }
  } while (input != '1' && input != '2');
  Character defaultCharacter;
  return defaultCharacter;

}

Character GameManager::createNewPlayer()
{
  int level;
  std::string style, name;
  bool nameIsUnique;

  std::cout << "CHARACTER CREATION=======================\n";
  do {
    nameIsUnique = true;
    std::cout << "Please input a unique name for your character: \n";
    std::cin >> name;
    Functions::convertToUpper(name);

    for (auto& p : players) {
      if (p.getName() == name) {
        nameIsUnique = false;
        break;
      }
    }
    for (auto& e : enemies) {
      if (e.getName() == name) {
        nameIsUnique = false;
        break;
      }
    }
  } while (!nameIsUnique);
  
  std::cout << "Please input a level for your character between 1-20: ";
  std::cin >> level;//automatically set between 1-20 in Character constructor

  do {
    std::cout << "Please input a style for your character amongst BULLY, NIMBLE, TANK: ";
    std::cin >> style;
    Functions::convertToUpper(style);
  } while (style != "BULLY" && style != "NIMBLE" && style != "TANK");

  Character c(name,level,style);
  newPlayerCreated = true;
  return c;
}

void GameManager::equipNewPlayer()
{
  std::string inputStr;
  bool itemFound;
  std::cout << "You may now select some starting equipment for your new player:\n"
  << "Here are the items you may choose from:\n";
  for (auto& i : items) {
    std::cout << i.toString() << "\n";
  }
  for (auto& w : weapons) {
    std::cout << w.toString() << "\n";
  }
  for (auto& a : armors) {
    std::cout << a.toString() << "\n";
  }
  std::cout << "Please enter the item names for the items you want to add to your equipment, enter stop to stop adding:\n";
  do {
    itemFound = false;
    std::cout << "Your selection (or stop): ";
    std::cin >> inputStr;
    Functions::convertToUpper(inputStr);

    if (inputStr != "STOP") {
      for (auto& i : items) {
        if (i.getItemName() == inputStr){
          itemFound = true;
          player.getEquipment().getInventory().put(i);
          player.getEquipment().equipItem(i.getItemName());
        }
      }
      for (auto& w : weapons) {
        if (w.getItemName() == inputStr){
          itemFound = true;
          player.getEquipment().getInventory().put(w);
          player.getEquipment().equipItem(w.getItemName());
        }
      }
      for (auto& a : armors) {
        if (a.getItemName() == inputStr){
          itemFound = true;
          player.getEquipment().getInventory().put(a);
          player.getEquipment().equipItem(a.getItemName());
        }
      }
      if (!itemFound) { std::cout << "Item not found, please try again\n"; }
    }
  } while (inputStr != "STOP");
}

Character GameManager::selectExistingPlayer()
{
  std::string selectedCharacterName;
  bool validInput;
  do {
    validInput = false;
    std::cout << "Here are the saved players:\n";
    for (auto& p : players) {
      std::cout << p.getName() << "\n";
    }
    std::cout << "Please enter the name of the selected player: ";
    std::cin >> selectedCharacterName;
    Functions::convertToUpper(selectedCharacterName);
    
    //Validate existence and display, validate choice
    for (auto& p : players) {
      if (p.getName() == selectedCharacterName) {
        std::cout << "You have chosen the player " << selectedCharacterName << ". Here is the player: \n";
        p.printCharacter();
        std::cout << "Enter any key to continue or 0 to cancel.\n";
        char input;
        std::cin >> input;
        if (input == '0') {
          validInput = false;
        } else {
          validInput = true;
        }
        break;
      }
    }
  } while (!validInput);

  for (auto& p : players) {
    if (p.getName() == selectedCharacterName) {
      return p;
    }
  }
}

void GameManager::startGame()
{

  char input;
  for (auto& map : maps) {
    map.displayMap();

    std::cout
    << map.getWidth() << "\n"
    << map.getHeight() << "\n"
    << map.getCell(1,8) << "\n"
    << map.hasValidPath('X') << "\n";
    map.setCell(1,8,'#');
    map.setCell(2,2,'#');
    map.displayMap();

    std::cout << "end of loop\n";
  }


  //select campaign
  //campaignMaps = chosen campaign

  //for (auto& map : campaignMaps) {
  //MapEngine(&map,&player)
  //}
  
  //save objects
  saveObjects();

  //once function terminates, control will return to main menu in main
}

void GameManager::saveObjects()
{
  //add newly created player if created new player
  if (newPlayerCreated) {
    players.emplace_back(player);
    equipments.emplace_back(player.getEquipment());
    itemBags.emplace_back(player.getEquipment().getEquipped());
    itemBags.emplace_back(player.getEquipment().getInventory());
  }

  Item::writeItemsToFile(items);
  Weapon::writeWeaponsToFile(weapons);
  Armor::writeArmorsToFile(armors);
  ItemBag::writeBagsToFile(itemBags);

  Equipment::writeEquipmentsToFile(equipments);
  Character::writeCharactersToFile(players,"players");
  Character::writeCharactersToFile(enemies,"enemies");
  GridMap::writeMapsToFile(maps);
  //TOADD: campaigns
}
