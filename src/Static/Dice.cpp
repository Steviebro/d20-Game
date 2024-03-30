/**
 * @file Dice.cpp
 *
 * @brief the Dice.cpp file follows the d20 game rules for dice rolling.
 * The rollDice() function can be used to roll a specified number of dice of a specified type and then adds or
 * reduces it by an optional modifier value. The only type of dice accepted are d4, d6, d8, 10, d12, d20 and d100.
 *
 * @include regex for patter matching
 * @include string for string usage and manipulation
 * @include cstdlib for random number generator
 * @include ctime for setting the seed for the random number generator
 * @ref Dice.h
 * @author Jungsoo Lee 40174025
 */

#include "../../include/Static/Dice.h"
#include <regex>
#include <string>
#include <cstdlib>
#include <ctime>

bool Dice::isSeeded = false;


int Dice::rollDice(const std::string& userInput) {

    //generate the seed to randomize the numbers
    if (!isSeeded) {
        std::srand(static_cast<unsigned int>(std::time(0)));
        isSeeded = true;
    }

    int nbOfDice = 0;
    int diceType = 0;
    int optionalValue = 0;
    int rollNumber = 0;

    //check if the string matches the valid format
    std::regex correctFormat(R"((\d+)d(4|6|8|10|12|20|100)(\[(\+|-)(\d+)\])?)");
    std::smatch separatedInput;

    if (std::regex_match(userInput, separatedInput, correctFormat)) {
        nbOfDice = std::stoi(separatedInput[1]);
        diceType = std::stoi(separatedInput[2]);
        if (separatedInput[5].matched) {
            optionalValue = std::stoi(separatedInput[5]);
        }
        for (int i = 0; i < nbOfDice; ++i) {
            rollNumber = rollNumber + std::rand() % diceType + 1;
        }
        if(separatedInput[4].matched) {
            //if modifier is negative
            if(separatedInput[4] == "-") {
                rollNumber = rollNumber - optionalValue;
            }
            //if modiefier is positive
            else {
                rollNumber = rollNumber + optionalValue;
            }
        }
    }
    return rollNumber;
}