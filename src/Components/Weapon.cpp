/**
 * @file Weapon.cpp
 * @brief this cpp file writes the functions for each method needed
 * for the weapon class.
 * @ref Weapon.h
 * @author Mate Barabas and Steven Gingras
 */
#include "../include/Components/Weapon.h"

/**
 * @brief method that gets the weapon type
 * @return weapon type
 */
std::string Weapon::getWeaponType()
{
  return weaponType;
}
/**
 * @brief method that gets the range
 * @return range
 */
int Weapon::getRange()
{
  return range;
}
/**
 * @brief method that gets the dice type for the weapon
 * @return dice type
 */
std::string Weapon::getDiceType()
{
  return diceType;
}

std::string Weapon::toString() const
{
  return Item::toString() + " " + weaponType + " " + std::to_string(range) + " " + diceType;
}

void Weapon::writeWeaponsToFile(std::vector<Weapon>& weaponsToWrite)
{
  std::string fileName = "../saved/Item/weapons.txt";
  std::ofstream file(fileName);

  if (file.is_open()) {
    for (auto& weapon : weaponsToWrite) {
      file << weapon.toString() << "\n";
    }
    file.close();
  } else {
    throw std::runtime_error("unable to write to file "+fileName+"\n");
  }
}

std::vector<Weapon> Weapon::readWeaponsFromFile()
{
  std::vector<Weapon> result;
  Weapon temp;
  std::ifstream file("../saved/Item/weapons.txt");
  if (file.is_open()){
    while (file >> temp.itemName >> temp.itemType >> temp.enchantType >> temp.enchantLevel >> temp.weaponType >> temp.range >> temp.diceType) {
      if (temp.initPossibleEnchants()) {
        result.emplace_back(temp);
      } else {
        throw std::invalid_argument("In file ../saved/Item/weapons.txt, itemType "+temp.itemType+" is incompatible with the enchantType "+temp.enchantType+". Item not created!\n");
      }
    }
  } else {
    throw std::runtime_error("unable to read from file ../saved/Item/weapons.txt\n");
  }
  file.close();
  return result;
}