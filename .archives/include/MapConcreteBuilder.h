/**
 * @file This .h file is the header file for the MapConcreteBuilder.cpp It is used
 * to implement the features of the concrete builders.
 *
 * @ref MapBuilder.h
 * @author Jungsoo Lee 40174025
 */

#ifndef INC_345ASSIGNMENT1_MAPCONCRETEBUILDER_H
#define INC_345ASSIGNMENT1_MAPCONCRETEBUILDER_H
#include "MapBuilder.h"

/**
 * @class MapConcreteBuilderBasic
 * @brief This is the basic subclass that will inherit from the MapBuilder parent class.
 * It is basic because it will set all creatures and chests to level 1.
 */
class MapConcreteBuilderBasic : public MapBuilder { //Concrete Builder 1
public:
    virtual void buildCreatures(int charLvl);
    virtual void buildChests(int charLvl);
};

/**
 * @class MapConcreteBuilderComplex
 * @brief This is the complex subclass that will inherit from the MapBuilder parent class.
 * It is complex because it will set all creatures and chests to the given level.
 */
class MapConcreteBuilderComplex : public MapBuilder {
public:
    virtual void buildCreatures(int charLvl);
    virtual void buildChests(int charLvl);
};

#endif //INC_345ASSIGNMENT1_MAPCONCRETEBUILDER_H
