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
  std::cout << "DISPLAYING MAP RIGHT AFTER FIRST INIT OF PLAYER ON MAP===========================================\n";
}

void GameEngine::loopTurns()
{
  char input;
  initiativeRoll();
  while (!exitReached) {
    for (auto& c : turnOrder) {
      if (c == &player) {//it's the player's turn
        std::cout << "IT'S YOUR TURN!\n";
        playerTurn();
        if (exitReached) { break; }
      } else {//it's an enemy's turn
        std::cout << "Enemy " << c->getName() << "'s turn, does nothing!\n";
        std::cout << "Press any key to continue to the next turn: ";
        std::cin >> input;
        //enemyPlayTurn(c);
      }
    }
    //prints at end of everyone's turn
    for (auto& e : map.getEnemies()) {
      std::cout << "Enemy " << e.second.getName() << " has ended in position " << e.first.first << "," << e.first.second << "\n";
    }
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
    std::cout << "Initiative for " << tp.second->getName() << " is " << tp.first << "\n";
  }
  int order = 1;
  for (auto &to : turnOrder) {
    std::cout << "Character " << to->getName() << " is at position " << order++ << "\n";
  }
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

/**
*  #  #  #  E  #  #  #  #
   #     c  #           #
   #                    #
   #        *           #
   #                    #
   #  #                 X
   #                    #
   #  #  #  #  #  #  #  #
   for (0 < i < movement) {
    /move player here/
    /check if player runs into walls/ -> "player ran into wall, end turn"
    /check if player goes over any special cells/
   }
*/
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
        std::cout << "player fell over\n";
        return;
      }
      // update position
      playerPosition.second = playerPosition.second - 1;

    } else if (input == 'D' || input == 'd') {
      // invalid movement, lose a turn
      if (map.getCell(playerPosition.first, playerPosition.second + 1) == '#'
          || map.getCell(playerPosition.first, playerPosition.second + 1) == 'e') {
        std::cout << "player fell over\n";
        return;
      }
      //update position
      playerPosition.second = playerPosition.second + 1;

    } else if (input == 'L' || input == 'l') {
      // invalid movement, lose a turn
      if (map.getCell(playerPosition.first - 1, playerPosition.second) == '#'
          || map.getCell(playerPosition.first - 1, playerPosition.second) == 'e') {
        std::cout << "player fell over\n";
        return;
      }
      // update position
      playerPosition.first = playerPosition.first - 1;

    } else if (input == 'R' || input == 'r') {
      // invalid movement, lose a turn
      if (map.getCell(playerPosition.first + 1, playerPosition.second) == '#'
          || map.getCell(playerPosition.first + 1, playerPosition.second) == 'e') {
        std::cout << "player fell over\n";
        return;
      }
      //update position
      playerPosition.first = playerPosition.first + 1;
    }

    // check for special cells
    if (map.getCell(playerPosition.first, playerPosition.second) == '*') {
      std::cout << "open chest";
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
  /* iterate through enemies in list from map
   enemy -> element in vector from map.Enemies
   vector<pair<pair<int,int>, Character> -> vector of pair<position, Character>
   i.e.,

   typedef pair<int,int> = position
   typedef <pair<position, Character> = cPosition;

   c.getRange() -> use this for conditional
   move until c.getRange == dx,dy*/

  for (auto & enemy : map.getEnemies()) {
    // if passing character doesn't work, use:
    //  if (enemy.second.getName() == enemyName)

    // search for correct enemy based on parameter
    if (enemy.second.getName() == c->getName()){
      // get position differences
      int dx = playerPosition.first - enemy.first.first;
      int dy = playerPosition.second - enemy.first.second;

      // currently basic, does not check for obstacles
      // enemy movement algorithm
      if (abs(dx) > abs(dy)) {
        if (dx > 0) { // move right
          // check for valid movement
          if (map.getCell(playerPosition.first+1, playerPosition.second) == '#'
              || map.getCell(playerPosition.first+1, playerPosition.second) == 'P') {
            return;
          } else {
            // update map and positions
            map.setCell(enemy.first.first, enemy.first.second, ' ');
            map.setCell(enemy.first.first+1, enemy.first.second, 'e');
            enemy.first.first = enemy.first.first+1;
          }
        } else { // move left
          // check for valid movement
          if (map.getCell(playerPosition.first-1, playerPosition.second) == '#'
              || map.getCell(playerPosition.first-1, playerPosition.second) == 'P') {
            return;
          } else {
            // update map and positions
            map.setCell(enemy.first.first, enemy.first.second, ' ');
            map.setCell(enemy.first.first-1, enemy.first.second, 'e');
            enemy.first.first = enemy.first.first-1;
          }
        }
      } else {
        if (dy > 0) { // move up
          // check for valid movement
          if (map.getCell(playerPosition.first, playerPosition.second+1) == '#'
              || map.getCell(playerPosition.first, playerPosition.second+1) == 'P') {
            return;
          } else {
            // update map and positions
            map.setCell(enemy.first.first, enemy.first.second, ' ');
            map.setCell(enemy.first.first, enemy.first.second+1, 'e');
            enemy.first.second = enemy.first.second+1;
          }
        } else { // move down
          // check for valid movement
          if (map.getCell(playerPosition.first, playerPosition.second-1) == '#'
              || map.getCell(playerPosition.first, playerPosition.second-1) == 'P') {
            return;
          } else {
            // update map and positions
            map.setCell(enemy.first.first, enemy.first.second, ' ');
            map.setCell(enemy.first.first, enemy.first.second-1, 'e');
            enemy.first.second = enemy.first.second-1;
          }
        }
      }
    } else { // name not found in list of enemies
      std::cout << "Enemy name not found\n";
      return;
    }
  }
}

void GameEngine::playerAttack()
{
  char input;
  std::cout << "PLAYER ATTACK PHASE-----------------------------------------------------------------------------------------\n";
  std::cout << "Combat not yet implemented. Press any key to continue: ";
  std::cin >> input;
}

void GameEngine::enemyAttack(Character* c)
{
  char input;
  std::cout << "ENEMY " << c->getName() << " ATTACK PHASE----------------------------------------------------------------------------\n";
  std::cout << "Press any key to continue: ";
  std::cin >> input;
}

void GameEngine::playerFreeActions()
{
  char input;
  do {
    std::cout << "PLAYER FREE ACTIONS PHASE-----------------------------------------------------------------------------------------\n"
    << "1 - View your character's stats\n"
    << "2 - View your equipment\n"
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
    case '0':
    break;
    default:
      break;
    }
  } while (input != '0');
}

// combat -> list enemies in range (i.e., based on player's weapon)