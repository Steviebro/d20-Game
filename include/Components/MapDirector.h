/**
 * @file This .h file is the header file for the MapDirector.cpp. It is used to
 * implement the Director features of the map builder.
 *
 * @include string for string manipulation
 */

#ifndef INC_345ASSIGNMENT1_MAPDIRECTOR_H
#define INC_345ASSIGNMENT1_MAPDIRECTOR_H
#include "MapGeneration.h"
#include "MapBuilder.h"
#include <string>

/**
 * @class MapDirector
 * @brief This is the class for creating a Director for the Map Builder.
 */
class MapDirector {

private:
    MapBuilder* m_mapBuilder;
public:
    void setMapBuilder(MapBuilder* mb); //Use a concrete builder
    //get the constructed Map
    GridMap* getMap();
    //Creation process to create a map using the builder
    void constructMap(int charLvl, const std::string& fileName);
};


#endif //INC_345ASSIGNMENT1_MAPDIRECTOR_H
