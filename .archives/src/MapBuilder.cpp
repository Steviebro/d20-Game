/**
 * @file MapBuilder.cpp
 *
 * @brief the MapBuilder.cpp file follows the guidelines for the Map Builder functionalities.
 * The subclasses in the MapConcreteBuilder.hpp inherits this class to implement the virtual functions.
 *
 * @include fstream for file streaming
 * @include filesystem for file path verification
 * @include string for string manipulation
 * @include iostream for outputting to the console
 * @ref MabBuilder.h
 * @ref MapGeneration.h
 * @author Jungsoo Lee 40174025
 */

#include "../../include/Components/MapBuilder.h"
#include <fstream>
#include <filesystem>
#include <string>
#include <iostream>

namespace fs = std::filesystem;

/**
 * @brief method for returning the map
 * @return the map
 */
GridMap* MapBuilder::getMap() {
    return m_map;
}

/**
 * @brief method to build the basic format of the map
 * @param fileName the file containing the map
 */
void MapBuilder::createNewMapProduct(const std::string& fileName) {
    int width = 0;
    int height = 1;
    fs::path filePath = fileName;
    if (!fs::exists(filePath)) {
        std::cout << "Unable to open file\n";
    }
    std::ifstream fileStream(filePath);
    char letter;
    //skip first line
    fileStream.get(letter);

    //for width
    while (fileStream.get(letter)) {
        if(letter == '\n') {
            break;
        }
        else {
            fileStream.get(letter);
            if(letter == '\n') {
                break;
            }
            fileStream.get(letter);
            if(letter == '\n') {
                break;
            }
            width += 1;
        }
    }

    //for height
    std::string line;
    while (std::getline(fileStream, line)) {
        height += 1;
    }

    fileStream.close();
    m_map = new GridMap(width ,height);

    //section of the code to populate the map with entrance, exit, monsters, chests, etc
    std::ifstream fileStream2(filePath);
    char letter2;
    //coordinates
    int x = 0;
    int y = 0;
    //skip first line
    fileStream2.get(letter);
    while (fileStream2.get(letter)) {
        if(letter == '\n') {
            y += 1;
            x = 0;
            continue;
        }
        else {
            fileStream2.get(letter);
            if(letter == '\n') {
                y += 1;
                x = 0;
                continue;
            }
            if(letter == '*'){
                m_map->increaseChests();
            }
            else if (letter == 'm') {
                m_map->increaseCreatures();
            }
            m_map->setCellBuilder(x, y, letter);
            fileStream2.get(letter);
            x += 1;
            if(letter == '\n') {
                y += 1;
                x = 0;
                continue;
            }
        }
    }
    fileStream2.close();
    m_map->displayMap();
}