#ifndef INC_345PROJECT_CHARACTER_H
#define INC_345PROJECT_CHARACTER_H

#include "../Static/Functions.h"
#include "../Static/Dice.h"
#include "../Components/ItemBag.h"


#include <stdexcept>
#include <string>
#include <cmath>

class Character {
public:
    // CONSTRUCTOR & CONSTRUCTOR HELPERS ====================================
    Character(int levelParam, std::string styleParam);

    void initScores();
    int initScorePriority(const std::string& toInit, std::string& style);
    void initHitPoints();

    // MUTATORS ==================================================
    int takeDamage(int damageTaken);
    void levelUp();
    int gainExperience(int experienceGained);

    // SIMPLE ACCESSORS ======================================
    std::string getStyle() const;
    int getHitPoints() const;
    int getLevel() const;
    int getExperience() const;
    virtual int getScore(std::string scoreName) const;

    // COMPUTED ACCESSORS ======================================
    int getModifier(std::string modifierType) const;
    virtual int getArmorClass() const;
    virtual int getAttackBonus() const;
    virtual int getDamageBonus() const;
    int getProficiencyBonus() const;

    // OTHER ==================================================
    void printCharacter() const;
    
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
    int experience;
    //Hit Points
    int hitPoints;
    //Inventory (TO ADD) to hold both equipped and unequipped items. We'll know which are equipped due to Decorator EquippedCharacter (TODO)
    //ItemBag inventory;
};

#endif