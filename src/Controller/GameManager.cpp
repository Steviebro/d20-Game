#include "../../include/Controller/GameManager.h"

Character GameManager::initPlayer()
{
  char input;
  std::cout << "GAME MANAGER ====================!\n";
  do {
    std::cout << "Would you like to create a new Character or select an existing one?\n"
    << "1 - Create New Character!\n"
    << "2 - Select from existing.\n"
    << "Your selection: ";
    std::cin >> input;

    switch(input) {
      case '1':
      return createNewCharacter();
      break;
      case '2':
      //TOADD: choose existing. For now just do same as case 1:
      return createNewCharacter();
      break;
      default:
      std::cout << "You have entered an invalid input, please try again!\n";
    }
  } while (input != '1' && input != '2');
}

Character GameManager::createNewCharacter()
{
  int level;
  std::string style;

  std::cout << "CHARACTER CREATION=======================\n"
  << "Please input a level for your character between 1-20:";
  std::cin >> level;//automatically set between 1-20 in Character constructor

  do {
    std::cout << "Please input a style for your character amongst BULLY, NIMBLE, TANK: ";
    std::cin >> style;
    Functions::convertToUpper(style);
  } while (style != "BULLY" && style != "NIMBLE" && style != "TANK");

  Character c(level,style);
  //add this character to character vector
  return c;
}

void GameManager::saveObjects()
{
  Item::writeItemsToFile(items);
  Weapon::writeWeaponsToFile(weapons);
  Armor::writeArmorsToFile(armors);
  ItemBag::writeBagsToFile(itemBags);
  //TOADD: maps, campaigns, characters
}
