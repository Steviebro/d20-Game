/**
 * @file This .h file is the header file for the MapBuilder.cpp. It is used to implement
 * the map builder features.
 *
 * @include string for string manipulation
 * @ref MapGeneration.h
 * @author Jungsoo Lee 40174025
 */

#ifndef INC_345ASSIGNMENT1_MAPBUILDER_H
#define INC_345ASSIGNMENT1_MAPBUILDER_H
#include "MapGeneration.h"
#include <string>

/**
 * @class MapBuilder
 * @brief This is the class for creating a super Map Builder. This is not meant to be created
 * as an object but it is meant to be inherited.
 */
class MapBuilder {
public:
    //get the build Map from the Builder
    GridMap* getMap();
    //build a generic empty Map
    void createNewMapProduct(const std::string& file);
    //create each part of the Map according to the subtypes
    virtual void buildCreatures(int charLvl) = 0;
    virtual void buildChests(int charLvl) = 0;
protected:
    //Map built by Map Builder
    GridMap* m_map;
};


#endif //INC_345ASSIGNMENT1_MAPBUILDER_H
