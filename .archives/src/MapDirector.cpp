/**
 * @file MapDirector.cpp
 *
 * @brief The MapDirector.cpp file acts as the user controlling the MapBuilder class.
 * It constructs the Map by calling the different functions of the MapBuilder class.
 *
 * @author Jungsoo Lee 40174025
 */

#include "../../include/Components/MapDirector.h"

/**
 * @brief Method to set the MapBuilder
 * @param mb the MapBuilder object we wish to link. It should be from a subclass.
 */
void MapDirector::setMapBuilder(MapBuilder* mb) {
    m_mapBuilder = mb;
}

/**
 * @brief Method to get the Map
 * @return the Map object
 */
GridMap* MapDirector::getMap() {
    return m_mapBuilder->getMap();
}

/**
 * @brief method to construct the map according to the concrete builder
 * @param charLvl the level of the character
 * @param fileName the file name containing the map
 */
void MapDirector::constructMap(int charLvl, const std::string& fileName) {
    m_mapBuilder->createNewMapProduct(fileName);
    m_mapBuilder->buildCreatures(charLvl);
    m_mapBuilder->buildChests(charLvl);
}