#include "../../include/Components/Character.h"
#include "../../include/Components/Weapon.h"

#include <iostream>

Character::Character(std::string nameParam, int levelParam, std::string styleParam)
: name(Functions::convertToUpper(nameParam)), level(levelParam), style(Functions::convertToUpper(styleParam)), xp(0), equipment(nameParam),
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

Character::Character(std::string nameParam, int levelParam, std::string styleParam, int xpParam, int hpParam, int scoresParam[6])
: name(Functions::convertToUpper(nameParam)), level(levelParam), style(Functions::convertToUpper(styleParam)), xp(xpParam), hp(hpParam), equipment(nameParam),
STR(initScorePriority("STR", styleParam)), DEX(initScorePriority("DEX", styleParam)), CON(initScorePriority("CON", styleParam))
{
    //initialize the scores
    for (int i = 0 ; i < 6 ; i++) {
        scores[i] = scoresParam[i];
    }

    //Validate style
    if (style != "BULLY" && style != "NIMBLE" && style != "TANK") {
        throw std::invalid_argument("Invalid style passed in Character constructor: must fall within: BULLY, NIMBLE, TANK.\n");
    }

    //Validate level
    if (level > 20) { level = 20; }
    if (level < 1) { level = 1; }
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

void Character::healDamage(int damageHealed){
  if (damageHealed > 0){
    hp += damageHealed;
  }
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

std::string Character::getName() const
{
    return name;
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

int Character::getScore(std::string scoreName)
{
    Functions::convertToUpper(scoreName);
    if (scoreName == "STR" || scoreName == "STRENGTH") {
        return std::min(scores[STR] + equipment.getEquipped().sumEnchants("STRENGTH"), 20);
    } else if (scoreName == "DEX" || scoreName == "DEXTERITY") {
        return std::min(scores[DEX] + equipment.getEquipped().sumEnchants("DEXTERITY"), 20);
    } else if (scoreName == "CON" || scoreName == "CONSTITUTION") {
        return std::min(scores[CON] + equipment.getEquipped().sumEnchants("CONSTITUTION"), 20);
    } else if (scoreName == "INT" || scoreName == "INTELLIGENCE") {
        return std::min(scores[INT] + equipment.getEquipped().sumEnchants("INTELLIGENCE"), 20);
    } else if (scoreName == "CHA" || scoreName == "CHARISMA") {
        return std::min(scores[CHA] + equipment.getEquipped().sumEnchants("CHARISMA"), 20);
    } else if (scoreName == "WIS" || scoreName == "WISDOM") {
        return std::min(scores[WIS] + equipment.getEquipped().sumEnchants("WISDOM"), 20);
    } else {
        throw std::invalid_argument("Invalid argument passed for getScore() method: "+scoreName);
    }
}

Equipment& Character::getEquipment()
{
    return equipment;
}

int Character::getModifier(std::string modifierType)
{
    Functions::convertToUpper(modifierType);
    return std::min(static_cast<int>(std::floor((getScore(modifierType) - 10)/2.0)),10);
}

void Character::setEquipment(Equipment& equipmentParam) {
  equipment = equipmentParam;
}

int Character::getArmorClass()
{
    int result = getModifier("DEX") + equipment.getEquipped().sumEnchants("ARMOR_CLASS");

    Armor* equippedArmorPtr = equipment.getArmor();
    if (equippedArmorPtr != nullptr) {
        result += equippedArmorPtr->getBaseArmorAC();
    }
    return result;
}

int Character::getAttackBonus()
{

    int result = getProficiencyBonus() + equipment.getEquipped().sumEnchants("ATTACK_BONUS");

    if (style == "BULLY") {
        return result + getModifier("STR");
    } else {
        return result + getModifier("DEX");
    }
}

int Character::getDamageBonus()
{
  if (style == "BULLY") {
    return getModifier("STR") + equipment.getEquipped().sumEnchants("DAMAGE_BONUS");
  } else {
    return getModifier("DEX") + equipment.getEquipped().sumEnchants("DAMAGE_BONUS");
  }
}

int Character::getProficiencyBonus() const
{
    return 2 + ((level - 1)/4);
}

void Character::printCharacter()
{
    std::cout << "\nCHARACTER: ==========================================="
    << "\nNAME: " << name
    << "\nSTYLE: " << style
    << "\nLEVEL: " << level
    << "\nEXPERIENCE: " << xp << "/" << level * 100
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
    << "\nPROFICIENCY BONUS: " << getProficiencyBonus();
    equipment.printEquipment();
    std::cout << "=====================================================\n";
}

std::string Character::toString()
{
    return name + " " + std::to_string(level) + " " + style + " " + std::to_string(xp) + " " + std::to_string(hp) + " "
    + std::to_string(scores[0]) + " " + std::to_string(scores[1]) + " " + std::to_string(scores[2]) + " " + std::to_string(scores[3]) + " " + std::to_string(scores[4]) + " " + std::to_string(scores[5]);
}

void Character::writeCharactersToFile(std::vector<Character>& charactersToWrite, std::string enemiesOrPlayers)
{
    Functions::convertToLower(enemiesOrPlayers);
    if (enemiesOrPlayers == "enemies" || enemiesOrPlayers == "players") {
        std::string fileName = "../saved/Character/" + enemiesOrPlayers + ".txt";
        std::ofstream file(fileName);

        if (file.is_open()) {
            for (auto& character : charactersToWrite) {
                file << character.toString() << "\n";
            }
            file.close();
        } else {
            throw std::runtime_error("unable to write to file "+fileName+"\n");
        }
    } else {
        throw std::invalid_argument("Parameter enemiesOrPlayers did not pass in enemies or players, passed in: "+enemiesOrPlayers);
    }
}
std::vector<Character> Character::readCharactersFromFile(std::string enemiesOrPlayers, std::vector<Equipment> equipments)
{
    Functions::convertToLower(enemiesOrPlayers);
    std::vector<Character> result;
    int levelP, hpP, xpP, scoresP[6];
    std::string nameP, styleP;
    if (enemiesOrPlayers == "enemies" || enemiesOrPlayers == "players") {
        std::string fileName = "../saved/Character/" + enemiesOrPlayers + ".txt";
        std::ifstream file(fileName);
        if (file.is_open()) {
            while (file >> nameP >> levelP >> styleP >> xpP >> hpP >> scoresP[0] >> scoresP[1] >> scoresP[2] >> scoresP[3] >> scoresP[4] >> scoresP[5]) {
                Character c(nameP, levelP, styleP, xpP, hpP, scoresP);
                for (auto& equip : equipments) {
                    if (equip.getName() == c.getName()) {
                        c.setEquipment(equip);
                    }
                }
                result.emplace_back(c);
            }
            file.close();
        } else {
            throw std::runtime_error("unable to read from file "+fileName+"\n");
        }
    } else {
        throw std::invalid_argument("Parameter enemiesOrPlayers did not pass in enemies or players, passed in: "+enemiesOrPlayers);
    }
    return result;
}