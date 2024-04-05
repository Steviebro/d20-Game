#ifndef INC_345PROJECT_INCLUDE_COMPONENTS_GAMEENGINE_H_
#define INC_345PROJECT_INCLUDE_COMPONENTS_GAMEENGINE_H_
#include "../Components/Character.h"
#include "../Components/MapGeneration.h"
#include "../Static/Dice.h"


class GameEngine {
public:
    GameEngine(GridMap mapParam, Character& playerParam) : map(mapParam), player(playerParam), exitReached(false) {
      initPlayerPosition();
      loopTurns();
    };

    void initPlayerPosition();
    void loopTurns();
    void initiativeRoll();

    void playerTurn();
    void playerMove();
    void playerAttack();
    void playerFreeActions();

    void enemyPlayTurn(Character* c);
    void enemyMove(Character* c);
    void enemyAttack(Character* c);


private:
    std::pair<int,int> playerPosition;
    GridMap map;
    Character& player;
    std::vector<Character*> turnOrder;
    bool objectiveReached;
    bool exitReached;
};

#endif //INC_345PROJECT_INCLUDE_COMPONENTS_GAMEENGINE_H_