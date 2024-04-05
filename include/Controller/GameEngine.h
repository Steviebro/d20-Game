#ifndef INC_345PROJECT_INCLUDE_COMPONENTS_GAMEENGINE_H_
#define INC_345PROJECT_INCLUDE_COMPONENTS_GAMEENGINE_H_
#include "../Components/Character.h"
#include "../Components/MapGeneration.h"


class GameEngine {
public:
    GameEngine(GridMap mapParam, Character& playerParam) : map(mapParam), player(playerParam) {};

    void loopTurns();
    void initiativeRoll();

    void playerTurn();
    void playerMove();
    void playerAttack();
    void playerFreeActions();

    void enemyPlayTurn(std::string enemyName);
    void enemyMove(std::string enemyName);
    void enemyAttack(std::string enemyName);


private:
    GridMap map;
    Character& player;
    std::list<std::string> turnOrder;
};

#endif //INC_345PROJECT_INCLUDE_COMPONENTS_GAMEENGINE_H_