#include "../../include/Controller/GameEngine.h"

void GameEngine::initPlayerPosition()
{
  std::pair<int,int> entrancePos = map.getEntrancePosition();
  if (entrancePos.first == 0) {
    playerPosition.first = entrancePos.first + 1;
    playerPosition.second = entrancePos.second;
  } else if (entrancePos.first == map.getWidth() - 1) {
    playerPosition.first = entrancePos.first - 1;
    playerPosition.second = entrancePos.second;
  } else if (entrancePos.second == 0) {
    playerPosition.first = entrancePos.first;
    playerPosition.second = entrancePos.second + 1;
  } else if (entrancePos.second == map.getHeight() - 1) {
    playerPosition.first = entrancePos.first;
    playerPosition.second = entrancePos.second - 1;
  } else {
    throw std::runtime_error("Something wrong with init player position\n");
  }
  map.setCell(playerPosition.first,playerPosition.second,'P');
  map.displayMap();
//  std::cout << "DISPLAYING MAP RIGHT AFTER FIRST INIT OF PLAYER ON MAP===========================================\n";
}

void GameEngine::loopTurns()
{
  char input;
  initiativeRoll();
  while (!exitReached) {
    for (auto& c : turnOrder) {
      // if character name is blank, continue;
      if (player.getHP() > 0 && !(c->getName().empty())) {
        if (c == &player) {//it's the player's turn
          std::cout << "IT'S YOUR TURN!\n";
          playerTurn();
          if (exitReached) { break; }
        } else {//it's an enemy's turn
          if (c->getHP() > 0) {
            std::cout << "Enemy " << c->getName() << "'s turn!\n";
            std::cout << "Press any key to continue: ";
            std::cin >> input;
            enemyPlayTurn(c);
          }
        }
      }
    }
    //prints at end of everyone's turn
//    for (auto& e : map.getEnemies()) {
//      std::cout << "Enemy " << e.second.getName() << " has ended in position " << e.first.first << "," << e.first.second << "\n";
//    }
    map.displayMap();
  }
}
void GameEngine::initiativeRoll() {
  std::vector<std::pair<int, Character*>> turnPriority;
  for (auto &e : map.getEnemies()) {
    turnPriority.emplace_back(Dice::rollDice("1d20") + e.second.getModifier("DEXTERITY"), &e.second);
  }
  turnPriority.emplace_back(Dice::rollDice("1d20") + player.getModifier("DEXTERITY"), &player);
  //sort turnPriority in desc by int value
  std::sort(std::begin(turnPriority),std::end(turnPriority),[](std::pair<int, Character*> a, std::pair<int, Character*> b) { return a.first > b.first; });

  //TOREMOVE: JUST SOME TEST PRINTS========================================
  for (auto &tp : turnPriority) {
    turnOrder.emplace_back(tp.second);
//    std::cout << "Initiative for " << tp.second->getName() << " is " << tp.first << "\n";
  }
//  int order = 1;
//  for (auto &to : turnOrder) {
//    std::cout << "Character " << to->getName() << " is at position " << order++ << "\n";
//  }
}

void GameEngine::playerTurn()
{
  playerMove();
  if (!exitReached) {
    playerAttack();
    playerFreeActions();
  }
}

void GameEngine::enemyPlayTurn(Character* c)
{
  enemyMove(c);
  enemyAttack(c);
}

void GameEngine::playerMove() {
  char input;
  int movement = 0;
  std::pair<int,int> prev = playerPosition;

  do {
    std::cout << "Enter Where you would like to move (U,D,L,R): ";
    std::cin >> input;
  } while (input != 'U' && input != 'u' && input != 'D' && input != 'd' && input != 'L' && input != 'l' && input != 'R' && input != 'r');

  do {
    std::cout << "Enter by how many spaces, you have a maximum of 6: ";
    std::cin >> movement;
  } while (movement < 0 || movement > 6);

  // main movement loop
  for (int i = 0; i < movement; i++) {
    if (input == 'U' || input == 'u') {
      // invalid movement, lose a turn
      if (map.getCell(playerPosition.first, playerPosition.second - 1) == '#'
          || map.getCell(playerPosition.first, playerPosition.second - 1) == 'e') {
        std::cout << "You fell over, lose your turn\n";
        map.displayMap();
        return;
      } else if (map.getCell(playerPosition.first, playerPosition.second - 1) == 'f') {
        std::cout << "NPC: 'Hey, watch it!'\n";
        map.displayMap();
        return;
      }
      // update position
      playerPosition.second = playerPosition.second - 1;

    } else if (input == 'D' || input == 'd') {
      // invalid movement, lose a turn
      if (map.getCell(playerPosition.first, playerPosition.second + 1) == '#'
          || map.getCell(playerPosition.first, playerPosition.second + 1) == 'e') {
        std::cout << "You fell over, lose your turn\n";
        map.displayMap();
        return;
      } else if (map.getCell(playerPosition.first, playerPosition.second + 1) == 'f') {
        std::cout << "NPC: 'Hey, watch it!'\n";
        map.displayMap();
        return;
      }
      //update position
      playerPosition.second = playerPosition.second + 1;

    } else if (input == 'L' || input == 'l') {
      // invalid movement, lose a turn
      if (map.getCell(playerPosition.first - 1, playerPosition.second) == '#'
          || map.getCell(playerPosition.first - 1, playerPosition.second) == 'e') {
        std::cout << "You fell over, lose your turn\n";
        map.displayMap();
        return;
      } else if (map.getCell(playerPosition.first - 1, playerPosition.second) == 'f') {
        std::cout << "NPC: 'Hey, watch it!'\n";
        map.displayMap();
        return;
      }
      // update position
      playerPosition.first = playerPosition.first - 1;

    } else if (input == 'R' || input == 'r') {
      // invalid movement, lose a turn
      if (map.getCell(playerPosition.first + 1, playerPosition.second) == '#'
          || map.getCell(playerPosition.first + 1, playerPosition.second) == 'e') {
        std::cout << "You fell over, lose your turn\n";
        map.displayMap();
        return;
      } else if (map.getCell(playerPosition.first + 1, playerPosition.second) == 'f') {
        std::cout << "NPC: 'Hey, watch it!'\n";
        map.displayMap();
        return;
      }
      //update position
      playerPosition.first = playerPosition.first + 1;
    }

    // check for special cells
    if (map.getCell(playerPosition.first, playerPosition.second) == 'c' || map.getCell(playerPosition.first, playerPosition.second) == 'd') {
      //Get the chest and put contents in inventory
      for (auto it = map.getChests().begin() ; it < map.getChests().end() ; it++) {
        if (it->first.first == playerPosition.first && it->first.second == playerPosition.second) {
          //Put chest contents in inventory
          player.getEquipment().getInventory().putMany(it->second, false);

          //Remove chest from map
          map.getChests().erase(it);

          //Print status
          if (map.getCell(playerPosition.first, playerPosition.second) == 'd') {
            std::cout << "Enemy body looted!\n";
          } else {
            std::cout << "Chest looted!\n";
          }
          player.getEquipment().printEquipment();
        }
      }
    } else if (map.getCell(playerPosition.first, playerPosition.second) == '!') {
      objectiveReached = true;
      std::cout << "OBJECTIVE REACHED!-----------------------------\n";
    } else if (map.getCell(playerPosition.first, playerPosition.second) == 'X') {
      if (objectiveReached) {
        exitReached = true;
      } else {
        std::cout << "Exit not unlocked, find objective\n";
        // player's turn ends
        return;
      }
    }
    // clear past cell
    map.setCell(prev.first, prev.second, ' ');
    // update player on map
    map.setCell(playerPosition.first, playerPosition.second, 'P');
    prev = playerPosition;
  }
  map.displayMap();
}

void GameEngine::enemyMove(Character* c) {
  for (auto & enemy : map.getEnemies()) {
    if (enemy.second.getName() == c->getName()){
      // get position differences
      int dx = playerPosition.first - enemy.first.first;
      int dy = playerPosition.second - enemy.first.second;
      // currently basic, does not check for obstacles
      // enemy movement algorithm
      if (abs(dx) > abs(dy)) {
        if (dx > 0) { // move right
          // check for valid movement
          if (map.getCell(enemy.first.first+1, enemy.first.second) == '#'
              || map.getCell(enemy.first.first+1, enemy.first.second) == 'P'
              || map.getCell(enemy.first.first+1, enemy.first.second) == 'f') {
            return;
          } else {
            // update map and positions
            map.setCell(enemy.first.first, enemy.first.second, ' ');
            map.setCell(enemy.first.first+1, enemy.first.second, 'e');
            enemy.first.first = enemy.first.first+1;
          }
        } else { // move left
          // check for valid movement
          if (map.getCell(enemy.first.first-1, enemy.first.second) == '#'
              || map.getCell(enemy.first.first-1, enemy.first.second) == 'P'
              || map.getCell(enemy.first.first-1, enemy.first.second) == 'f') {
            return;
          } else {
            // update map and positions
            map.setCell(enemy.first.first, enemy.first.second, ' ');
            map.setCell(enemy.first.first-1, enemy.first.second, 'e');
            enemy.first.first = enemy.first.first-1;
          }
        }
      } else {
        if (dy < 0) { // move up
          // check for valid movement
          if (map.getCell(enemy.first.first, enemy.first.second-1) == '#'
              || map.getCell(enemy.first.first, enemy.first.second-1) == 'P'
              || map.getCell(enemy.first.first, enemy.first.second-1) == 'f') {
            return;
          } else {
            // update map and positions
            map.setCell(enemy.first.first, enemy.first.second, ' ');
            map.setCell(enemy.first.first, enemy.first.second-1, 'e');
            enemy.first.second = enemy.first.second-1;
          }
        } else { // move down
          // check for valid movement
          if (map.getCell(enemy.first.first, enemy.first.second+1) == '#'
              || map.getCell(enemy.first.first, enemy.first.second+1) == 'P'
              || map.getCell(enemy.first.first, enemy.first.second+1) == 'f') {
            return;
          } else {
            // update map and positions
            map.setCell(enemy.first.first, enemy.first.second, ' ');
            map.setCell(enemy.first.first, enemy.first.second+1, 'e');
            enemy.first.second = enemy.first.second+1;
          }
        }
      }
    }
  }
  map.displayMap();
}

void GameEngine::playerAttack()
{
  char input;
  std::string inputStr;
  std::cout << "PLAYER ATTACK PHASE-----------------------------------------------------------------------------------------\n";
  std::cout << "Your turn to attack. Press any key to continue: ";
  std::cin >> input;

  std::vector<std::pair<int,int>> targetablePositions;
  std::vector<Character*> targetableEnemies;

  //Check range of player
  int range = (player.getEquipment().getWeapon()->getRange())/5;
  std::pair<int,int> tempPair;

  for (int x = playerPosition.first - range ; x <= playerPosition.first + range ; x++) {
    for (int y = playerPosition.second - range ; y <= playerPosition.second + range ; y++) {
      // manhattan distance check
      if (abs(x - playerPosition.first) + abs(y - playerPosition.second) <= range) {
        tempPair.first = x;
        tempPair.second = y;
        targetablePositions.emplace_back(tempPair);
      }
    }
  }
//  std::cout << "Player's targetable positions are: ";
//  for (auto& target :targetablePositions) {
//    std::cout << target.first << "," << target.second << "|";
//  }
//  std::cout << "\n";

  //Check if there are enemies in range
  for (auto& enemy : map.getEnemies()) {
    for (auto& targetablePosition : targetablePositions) {
      if (enemy.first.first == targetablePosition.first && enemy.first.second == targetablePosition.second) {
        targetableEnemies.emplace_back(&(enemy.second));
      }
    }
  }

  //display enemies in range and prompt user to select one to attack
  bool validInput;
  if (!targetableEnemies.empty()) { // >= 1 targetable
    std::cout << "There are enemies in range to attack!\n";
    do {
      validInput = false;
      std::cout << "Select from the following list which enemy you would like to attack:\n";
      for (auto& targetableEnemy : targetableEnemies) {
        std::cout << targetableEnemy->getName() << "\n";
      }
      std::cout << "Your selection: ";
      std::cin >> inputStr;
      Functions::convertToUpper(inputStr);

      for (auto& targetableEnemy : targetableEnemies) {
        if (inputStr == targetableEnemy->getName()) {
          validInput = true;
          Character& chosenEnemy = *targetableEnemy;

          //Attack using Combat::attack(player,enemy);
          bool enemyDead = Combat::attack(player, chosenEnemy);

          //if enemy dies: remove enemy from map, add dead body to map
          if (enemyDead) {
            for (auto it = map.getEnemies().begin() ; it < map.getEnemies().end() ; it++) {
              if (it->second.getName() == chosenEnemy.getName()) {
                //Store position
                tempPair.first = it->first.first;
                tempPair.second = it->first.second;

                //Get the enemy's loot
                Character* fallenEnemy = &(it->second);
                ItemBag fallenEnemyLoot = fallenEnemy->getEquipment().getEquipped();
                fallenEnemyLoot.putMany(fallenEnemy->getEquipment().getInventory(), false);

                //Add the loot to the map's chests
                map.getChests().emplace_back(tempPair,fallenEnemyLoot);
                map.setCell(tempPair.first,tempPair.second,'d');

                //Erase the enemy from the map
                auto itt = std::find(turnOrder.begin(), turnOrder.end(), fallenEnemy);
                if (itt != turnOrder.end()) {
                  turnOrder.erase(itt);
                }
                map.getEnemies().erase(it);
              }
            }
          }
        }
      }
    } while (!validInput);
  } else {//none targetable
      std::cout << "No targetable enemies, ending turn";
      return;
  }
}

void GameEngine::enemyAttack(Character* c)
{
  char input;
  std::pair<int,int> tempPair;
  std::pair<int,int> tempPairPosition;
  std::cout << "ENEMY " << c->getName() << " ATTACK PHASE----------------------------------------------------------------------------\n";
  std::cout << "Press any key to continue: ";
  std::cin >> input;
  std::vector<std::pair<int,int>> targetablePositions;
  bool playerInRange = false;
  //Find c's position
  for (auto& enemy : map.getEnemies()) {
    if (enemy.second.getName() == c->getName()) {
      tempPairPosition.first = enemy.first.first;
      tempPairPosition.second = enemy.first.second;
    }
  }
  // uncomment to check enemy's position for debugging
//  std::cout << "Enemy's position is " << tempPairPosition.first << " " << tempPairPosition.second << "\n";


  //Check range of enemy
  int range = (c->getEquipment().getWeapon()->getRange())/5;
  // uncomment to check enemy's range for debugging
//  std::cout << "Enemy's range is " << range << "\n";


  for (int x = tempPairPosition.first - range ; x <= tempPairPosition.first + range ; x++) {
    for (int y = tempPairPosition.second - range ; y <= tempPairPosition.second + range ; y++) {
      // manhattan distance check
      if (abs(x - tempPairPosition.first) + abs(y - tempPairPosition.second) <= range) {
        tempPair.first = x;
        tempPair.second = y;

        targetablePositions.emplace_back(tempPair);
      }

    }
  }

  // uncomment to see targetable positions for debugging
//  std::cout << "Enemy's targetable positions are: ";
//  for (auto& target :targetablePositions) {
//    std::cout << target.first << "," << target.second << "|";
//  }
//  std::cout << "\n";

  //Check for player in range
  for (auto& targetablePosition : targetablePositions) {
    if (playerPosition.first == targetablePosition.first && playerPosition.second == targetablePosition.second) {
      playerInRange = true;
//      std::cout << "Player is in range, at position " << playerPosition.first << "," << playerPosition.second << " attacking\n";
    }
  }


  //attack player if in range
  if (playerInRange) {// >= 1 targetable
    bool playerDead = Combat::attack(*c, player);
    if(playerDead){
      std::cout<< "Game Over! Womp Womp! \n Bye.";
      exit(1);
    }
  } else {//none targetable
    //std::cout << "No targetable enemies, ending turn";
    return;
  }
}

void GameEngine::playerFreeActions()
{
  char input;
  do {
    std::cout << "PLAYER FREE ACTIONS PHASE-----------------------------------------------------------------------------------------\n"
    << "1 - View your character's stats\n"
    << "2 - View your equipment\n"
    << "3 - Take a health potion\n"
    << "0 - End your turn\n"
    << "Your selection: ";
    std::cin >> input;

    switch (input)
    {
    case '1':
    player.printCharacter();
    break;
    case '2':
    player.getEquipment().printEquipment();
    break;
    case '3': {
      if (player.getPotions() == 0) {
        std::cout << "Out of potions!";
        break;
      } else {
        Potion potion("HEAL", "POTION", "-", 0, "2d4");
        player.healDamage(potion.takePotion());
        player.decrementPotions();
        break;
      }
    }
    case '0':
      break;
    default:
      break; // continue?
    }
  } while (input != '0');
}