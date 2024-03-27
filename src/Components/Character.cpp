#include "../../include/Components/Character.h"




#include <iostream>

Character::Character(int levelParam, std::string styleParam)
: level(levelParam), style(Functions::convertToUpper(styleParam)), experience(0),
STR(initScorePriority("STR", styleParam)), DEX(initScorePriority("DEX", styleParam)), CON(initScorePriority("CON", styleParam))
{
    //Validate style
    if (style != "BULLY" && style != "NIMBLE" && style != "TANK") {
        throw std::invalid_argument("Invalid style passed in Character constructor: must fall within: BULLY, NIMBLE, TANK.\n");
    }

    //Validate level
    if (level > 20) { level = 20; }
    if (level < 1) { level = 1; }

    //Initialize 6 scores randomly and order in DESC
    initScores();

    //Initialize Hit Points
    initHitPoints();
}

void Character::initScores()
{
    //assign 6 scores and order in DESC
    int rolls[4];
    int sum = 0;
    for (auto& s : scores) {
        for (int i = 0 ; i < 4 ; i++) {
            rolls[i] = Dice::rollDice("1d6");
            sum += rolls[i];
        }
        s = sum - std::min(std::min(std::min(rolls[0], rolls[1]), rolls[2]), rolls[3]);
        sum = 0;
    }
    std::sort(std::begin(scores), std::end(scores), [](int a, int b) { return a > b; });
}

int Character::initScorePriority(const std::string& toInit, std::string& style)
{
    style = Functions::convertToUpper(style);
    if (style == "BULLY") {
        if (toInit == "STR") { return 0; }
        else if (toInit == "DEX") { return 2; }
        else if (toInit == "CON") { return 1; }
    } else if (style == "NIMBLE") {
        if (toInit == "STR") { return 2; }
        else if (toInit == "DEX") { return 0; }
        else if (toInit == "CON") { return 1; }
    } else if (style == "TANK") {
        if (toInit == "STR") { return 2; }
        else if (toInit == "DEX") { return 1; }
        else if (toInit == "CON") { return 0; }
    }

    throw std::invalid_argument("Function Character::initIndex() failed, either style "+style+" or toInit "+toInit+" not found in method.\n");
}

void Character::initHitPoints()
{
    hitPoints = 10 + getModifier("CON");

    int levelUps = level - 1;
    level = 1;

    while (levelUps > 0) {
        levelUp();
        levelUps--;
    }
}

int Character::takeDamage(int damageTaken)
{
    if (damageTaken > 0) {
        hitPoints -= damageTaken;
    }
    return hitPoints;
}

void Character::levelUp()
{
    if (level < 20) {
        hitPoints += (Dice::rollDice("1d10") + getModifier("CON"));
        level++;
    }
    
}

int Character::gainExperience(int experienceGained)
{
    //Ensure parameter > 0 and level < 20
    if (experienceGained <= 0 || level >= 20) {
        return experience;
    }
    experience += experienceGained;

    //Check for levelUp(s) required
    int experienceRequiredForLevelUp = level * 100;

    while (experience >= experienceRequiredForLevelUp && level < 20) {
        experience -= experienceRequiredForLevelUp;
        levelUp();
        experienceRequiredForLevelUp = level * 100;
    }

    //Set experience to 0 if max level reached
    if (level == 20) {
        experience = 0;
    }

    return experience;
}

std::string Character::getStyle() const
{
    return style;
}

int Character::getHitPoints() const
{
    return hitPoints;
}

int Character::getLevel() const
{
    return level;
}

int Character::getExperience() const
{
    return experience;
}

int Character::getScore(std::string scoreName) const
{
    Functions::convertToUpper(scoreName);
    if (scoreName == "STR" || scoreName == "STRENGTH") {
        return std::min(scores[STR], 20);
    } else if (scoreName == "DEX" || scoreName == "DEXTERITY") {
        return std::min(scores[DEX], 20);
    } else if (scoreName == "CON" || scoreName == "CONSTITUTION") {
        return std::min(scores[CON], 20);
    } else if (scoreName == "INT" || scoreName == "INTELLIGENCE") {
        return std::min(scores[INT], 20);
    } else if (scoreName == "CHA" || scoreName == "CHARISMA") {
        return std::min(scores[CHA], 20);
    } else if (scoreName == "WIS" || scoreName == "WISDOM") {
        return std::min(scores[WIS], 20);
    } else {
        throw std::invalid_argument("Invalid argument passed for getScore() method: "+scoreName);
    }
}

int Character::getModifier(std::string modifierType) const
{
    Functions::convertToUpper(modifierType);
    return static_cast<int>(std::floor((getScore(modifierType) - 10)/2.0));
}

int Character::getArmorClass() const
{
    return 10 + getModifier("DEX");
}

int Character::getAttackBonus() const
{
    if (style == "BULLY") {
        return level + getModifier("STR");
    } else {
        return level + getModifier("DEX");
    }
}

int Character::getDamageBonus() const
{
    return getModifier("STR");
}

int Character::getProficiencyBonus() const
{
    return 2 + ((level - 1)/4);
}

void Character::printCharacter() const
{
    std::cout << "\nCHARACTER: ==========================================="
    << "\nSTYLE: " << style
    << "\nLEVEL: " << level
    << "\nEXPERIENCE: " << experience << "/" << level * 1000
    << "\nHIT POINTS: " << hitPoints
    << "\nSTR: " << getScore("STR") << " | STR MOD: " << getModifier("STR")
    << "\nDEX: " << getScore("DEX") << " | DEX MOD: " << getModifier("DEX")
    << "\nCON: " << getScore("CON") << " | CON MOD: " << getModifier("CON")
    << "\nINT: " << getScore("INT") << " | INT MOD: " << getModifier("INT")
    << "\nCHA: " << getScore("CHA") << " | CHA MOD: " << getModifier("CHA")
    << "\nWIS: " << getScore("WIS") << " | WIS MOD: " << getModifier("WIS")
    << "\nARMOR CLASS: " << getArmorClass()
    << "\nATTACK BONUS: " << getAttackBonus()
    << "\nDAMAGE BONUS: " << getDamageBonus()
    << "\nPROFICIENCY BONUS: " << getProficiencyBonus()
    << "\n=====================================================\n";
}