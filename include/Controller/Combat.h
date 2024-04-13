//
// Created by Mate Barabas on 2024-04-10.
//

#ifndef INC_345PROJECT_INCLUDE_CONTROLLER_COMBAT_H_
#define INC_345PROJECT_INCLUDE_CONTROLLER_COMBAT_H_

#include "../Components/Character.h"
class Combat {
public:
  static bool attack(Character& attacker, Character& defender);

  static int attackRoll(Character& attacker, Character& defender);

  static int damageRoll(Character& attacker, Character& defender);

};








#endif //INC_345PROJECT_INCLUDE_CONTROLLER_COMBAT_H_
