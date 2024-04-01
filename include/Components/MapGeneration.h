/**
 * @file MapGeneration.h
 * @brief This is the header file for the MapGeneration class
 * @details This class is used to generate a map and check if there is a valid path from the entrance to the exit
 * @date 2024-02-12
 * @author Andrew Oh 40166897
 */

#ifndef INC_345ASSIGNMENT1_MAPGENERATION_H
#define INC_345ASSIGNMENT1_MAPGENERATION_H
#include <vector>
#include <string>
#include "Observer.h"
#include "Subject.h"
#include "Position.h"

/**
 * @brief GridMap class
 */
class GridMap : public Subject{
private:
    int width;
    int height;
    int chests;
    int creatures;
    std::vector<std::vector<char> > map;

public:
    /**
     * @brief Construct a new Grid Map object
     * @param w
     * @param h
     */
    GridMap();
    ~GridMap();
    GridMap(const int& w, const int& h) {
        width = w;
        height = h;
        chests = 0;
        creatures = 0;
        map.resize(height, std::vector<char>(width, ' '));
        GridMap::populateMap();
    }
    void populateMap();

    bool setCell(const int& x, const int& y, const char& c);

    [[nodiscard]] char getCell(const int& x, const int& y) const;

    [[nodiscard]] bool isValid(const int& x, const int& y) const;

    bool DFS(const int& x, const int& y, std::vector<std::vector<bool> >& visited);

    bool hasValidPath();

    void displayMap();

    std::string toString();

    int getWidth();

    int getHeight();

    void setCellBuilder(const int& x, const int& y, const char& c);

    void increaseChests();

    void increaseCreatures();

    int getChests();

    int getCreatures();

    bool isValidPosition(Position position);

};
#endif
