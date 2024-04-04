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
    Character(std::string nameParam, int levelParam, std::string styleParam);
    Character(std::string nameParam, int levelParam, std::string styleParam, int xpParam, int hpParam, int scoresParam[6]);
    Character() : Character("INVALID_CHARACTER",1,"BULLY") {};

    void initScores();
    int initScorePriority(const std::string& toInit, std::string& style);
    void initHP();

    // MUTATORS ==================================================
    int takeDamage(int damageTaken);
    void levelUp();
    int gainXP(int experienceGained);
    void setEquipment(Equipment& equipmentParam);

    // SIMPLE ACCESSORS ======================================
    std::string getName() const;
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
    std::string toString();
    static void writeCharactersToFile(std::vector<Character>& charactersToWrite, std::string enemiesOrPlayers);
    static std::vector<Character> readCharactersFromFile(std::string enemiesOrPlayers, std::vector<Equipment> equipments);
    
private:
    //Style and Scores (with indices)
    int STR;
    int DEX;
    int CON;
    int INT = 3;
    int CHA = 4;
    int WIS = 5;
    int scores[6];
    std::string style;

    std::string name;
    //Levels
    int level;
    int xp;
    //Hit Points
    int hp;
    //Inventory (TO ADD) to hold both equipped and unequipped items. We'll know which are equipped due to Decorator EquippedCharacter (TODO)
    Equipment equipment;
};

#endif