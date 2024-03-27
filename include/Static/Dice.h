/**
 * @file Dice.h
 * @brief This .h file is the header file for the Dice.cpp. It is used to
 * implement the dice features for a d20 game.
 *
 * @include string for string variable
 * @author Jungsoo Lee 40174025
 */

#ifndef INC_345PROJECT_DICE_H
#define INC_345PROJECT_DICE_H
#include <string>

/**
 * @class Dice
 * @brief This is the class for creating a Dice object according to the d20 rules.
 * The functions are explained in more thorough detail in the according cpp file.
 */
class Dice {
public:
    /**
    * @brief method for rolling a set number of dice of a dice type with a modifier
    * @param userInput the string containing the number of dice, dice type, and modifier
    * @return the total roll value
    */
    static int rollDice(const std::string& userInput);
private: 
    static bool isSeeded;///< A bool initialized to false ensuring the rand function is seeded only once
};


#endif //INC_345ASSIGNMENT1_DICE_H
