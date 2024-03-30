#include "../../include/Components/Character.h"
#include "../../include/Components/Weapon.h"

#include <iostream>

Character::Character(int levelParam, std::string styleParam)
: level(levelParam), style(Functions::convertToUpper(styleParam)), xp(0),
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
    initHP();
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

void Character::initHP()
{
    hp = 10 + getModifier("CON");

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
        hp -= damageTaken;
    }
    return hp;
}

void Character::levelUp()
{
    if (level < 20) {
        hp += (Dice::rollDice("1d10") + getModifier("CON"));
        level++;
    }
    
}

int Character::gainXP(int xpGained)
{
    //Ensure parameter > 0 and level < 20
    if (xpGained <= 0 || level >= 20) {
        return xp;
    }
    xp += xpGained;

    //Check for levelUp(s) required
    int xpRequiredForLevelUp = level * 100;

    while (xp >= xpRequiredForLevelUp && level < 20) {
        xp -= xpRequiredForLevelUp;
        levelUp();
        xpRequiredForLevelUp = level * 100;
    }

    //Set experience to 0 if max level reached
    if (level == 20) {
        xp = 0;
    }

    return xp;
}

std::string Character::getStyle() const
{
    return style;
}

int Character::getHP() const
{
    return hp;
}

int Character::getLevel() const
{
    return level;
}

int Character::getXP() const
{
    return xp;
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
    return std::min(static_cast<int>(std::floor((getScore(modifierType) - 10)/2.0)),10);
}

void Character::setEquipment(Equipment& equipmentParam) {
  equipment = equipmentParam;
}
int Character::getArmorClass() const
{
    return getModifier("DEX") + equipment.sumEnchants("ARMOR_CLASS")+ equipment.getArmor().getBaseArmorAC();
}

int Character::getAttackBonus() const
{
    if (style == "BULLY") {
        return getProficiencyBonus() + getModifier("STR") + equipment.sumEnchants("ATTACK_BONUS");
    } else {
        return getProficiencyBonus() + getModifier("DEX") + equipment.sumEnchants("ATTACK_BONUS");
    }
}

int Character::getDamageBonus() const
{
  if (style == "BULLY") {
    return getModifier("STR");
  } else {
    return getModifier("DEX");
  }
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
    << "\nEXPERIENCE: " << xp << "/" << level * 1000
    << "\nHIT POINTS: " << hp
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