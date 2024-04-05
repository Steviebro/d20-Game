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
#include "../include/Components/Subject.h"
#include "../include/Components/Position.h"
#include "../include/Components/ItemBag.h"
#include "../include/Components/Character.h"

/**
 * @brief GridMap class
 * hash map for characters and chests
 */
class GridMap : public Subject{
private:
  int width;
  int height;
  //int chest;
  //int creatures;
  std::string mapName;
  std::pair<int,int> entrance;
  std::pair<int,int> exit;
  std::pair<int,int> objective;
  // vector [{pos,bag}] -> pos: {x,y} -> bag: ItemBag
  std::vector<std::pair<std::pair<int,int>,ItemBag>> chests;
  std::vector<std::pair<std::pair<int,int>,Character>> enemies;
  // [<1,3>, <2,3>, <3,3>, ... <6,3>]
  std::vector<std::pair<int,int>> walls;
  std::vector<std::vector<char> > map;
//w h ex ey xx xy ox oy
//bname x y bname x y
//ename x y, ename x y
//x y x y x y x y x y

public:
  /**
   * @brief Construct a new Grid Map object
   * @param w
   * @param h
   */
   //std::vector<std::pair<std::pair<int,int>,ItemBag>> chestsP;
   //  std::vector<std::pair<std::pair<int,int>,Character>> enemiesP;
  GridMap();
  GridMap(int w, int h){
    map.resize(height, std::vector<char>(width,' '));
    GridMap::populateMap();
  }
  ~GridMap();
  GridMap(std::string mapNameP, const int coords[8], std::vector<std::pair<std::pair<int,int>,ItemBag>> chestsP, std::vector<std::pair<std::pair<int,int>,Character>> enemiesP, std::vector<std::pair<int,int>> wallsP)
  : mapName(mapNameP), width(coords[0]), height(coords[1]), entrance(coords[2],coords[3]), exit(coords[4],coords[5]), objective(coords[6],coords[7]), chests(chestsP), enemies(enemiesP), walls(wallsP)
  {
    map.resize(height, std::vector<char>(width, ' '));
    GridMap::populateMap();
  }
  void populateMap();

  bool setCell(const int& x, const int& y, const char& c);

  [[nodiscard]] char getCell(const int& x, const int& y) const;

  [[nodiscard]] bool isValid(const int& x, const int& y) const;

  bool DFS(const int& x, const int& y, std::vector<std::vector<bool> >& visited, char target);

  bool hasValidPath(char t);

  void displayMap();

  std::string toString();

  std::string getMapName();

  int getWidth();

  int getHeight();

  std::pair<int,int> getEntrancePosition();

  std::vector<std::pair<std::pair<int,int>,Character>>& getEnemies();

  std::vector<std::pair<std::pair<int,int>,ItemBag>>& getChests();

  void setCellBuilder(const int& x, const int& y, const char& c);

//  void increaseChests();
//
//  void increaseCreatures();
//
//  int getChests();
//
//  int getCreatures();

  std::string toStringF();

  static void writeMapsToFile(std::vector<GridMap> mapsToWrite);

  static std::vector<GridMap> readMapsFromFile (std::vector<ItemBag> itemBags, std::vector<Character> enemies);

  static void writeCampaignsToFile(std::vector<std::list<std::string>> campaignsToWrite);

  static std::vector<std::list<std::string>> readCampaignsFromFile(std::vector<GridMap> maps);

};
#endif
