#ifndef INC_345PROJECT_CHARACTER_H
#define INC_345PROJECT_CHARACTER_H

#include "../Static/Functions.h"
#include "../Static/Dice.h"
#include "ItemBag.h"
#include "Equipment.h"


#include <stdexcept>
#include <string>
#include <cmath>

class Character {
public:
    // CONSTRUCTOR & CONSTRUCTOR HELPERS ====================================
    Character(int levelParam, std::string styleParam);

    void initScores();
    int initScorePriority(const std::string& toInit, std::string& style);
    void initHP();

    // MUTATORS ==================================================
    int takeDamage(int damageTaken);
    void levelUp();
    int gainXP(int experienceGained);
    void setEquipment(Equipment& equipmentParam);

    // SIMPLE ACCESSORS ======================================
    std::string getStyle() const;
    int getHP() const;
    int getLevel() const;
    int getXP() const;
    int getScore(std::string scoreName);
    Equipment& getEquipment();

    // COMPUTED ACCESSORS ======================================
    int getModifier(std::string modifierType);
    int getArmorClass();
    int getAttackBonus();
    int getDamageBonus();
    int getProficiencyBonus() const;



    // OTHER ==================================================
    void printCharacter();
    
private:
    //Style and Scores (with indices)
    const int STR;
    const int DEX;
    const int CON;
    const int INT = 3;
    const int CHA = 4;
    const int WIS = 5;
    int scores[6];
    const std::string style;

    //Levels
    int level;
    int xp;
    //Hit Points
    int hp;
    //Inventory (TO ADD) to hold both equipped and unequipped items. We'll know which are equipped due to Decorator EquippedCharacter (TODO)
    Equipment equipment;
};

#endif