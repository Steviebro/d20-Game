/**
 * @file Armor.cpp
 * @brief this file writes the functionality for the armor
 * functions that are needed to create the armor object.
 * @ref Armor.h
 * @author Mate Barabas and Steven Gingras
 */
#include "../include/Components/Armor.h"

/**
 * @brief method that gets the armor type for the armor
 * @return armor type
 */
std::string Armor::getArmorType()
{
  return armorType;
}

/**
 * @brief method that returns the base armor class of the armor
 * @return baseArmorAC
 */
int Armor::getBaseArmorAC() {
  return baseArmorAC;
}

std::string Armor::toString() const {
  return Item::toString() + " " + armorType + " " + std::to_string(baseArmorAC);
}

void Armor::writeArmorsToFile(std::vector<Armor>& armorsToWrite)
{
  std::string fileName = "../saved/Item/armors.txt";
  std::ofstream file(fileName);

  if (file.is_open()) {
    for (auto& armor : armorsToWrite) {
      file << armor.toString() << "\n";
    }
    file.close();
  } else {
    throw std::runtime_error("unable to write to file "+fileName+"\n");
  }
}

std::vector<Armor> Armor::readArmorsFromFile()
{
  std::vector<Armor> result;
  Armor temp;
  std::ifstream file("../saved/Item/armors.txt");
  if (file.is_open()){
    while (file >> temp.itemName >> temp.itemType >> temp.enchantType >> temp.enchantLevel >> temp.armorType >> temp.baseArmorAC) {
      if (temp.initPossibleEnchants()) {
        result.emplace_back(temp);
      } else {
        throw std::invalid_argument("In file ../saved/Item/armors.txt, itemType "+temp.itemType+" is incompatible with the enchantType "+temp.enchantType+". Item not created!\n");
      }
    }
  } else {
    throw std::runtime_error("unable to read from file ../saved/Item/armors.txt\n");
  }
  file.close();
  return result;
}