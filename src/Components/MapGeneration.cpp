/**
 * @file GridMap.cpp
 * @ref GridMap.h
 * @brief Grid-based map is generated. Special cells such as entrance and exit are set manually.
 * @include iostream: for user input to set cells
 * @author Andrew Oh 40166897
 */

#include "../../include/Components/MapGeneration.h"
#include <iostream>
#include <string>

GridMap::GridMap() : Subject(), width(5), height(5){};
GridMap::~GridMap() = default;

void GridMap::populateMap(){
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (i == 0 || i == height - 1 || j == 0 || j == width - 1) {
                map[i][j] = '#';
            }
            else {
                map[i][j] = ' ';
            }
        }
    }
    //add entrance/exit/objective
    map[entrance.second][entrance.first] = 'E';
    map[exit.second][exit.first] = 'X';
    map[objective.second][objective.first] = '!';
    //add walls
    for (auto& wall : walls) {
      map[wall.second][wall.first] = '#';
    }
    //add chests
    for (auto& chest : chests) {
      map[chest.first.second][chest.first.first] = '*';
    }
    //add enemies
    for (auto& enemy : enemies) {
      map[enemy.first.second][enemy.first.first] = 'e';
    }

}

/**
 * @brief Set cell; input must be ' ', '*', '-', '|', 'E', 'X'
 * @param x
 * @param y
 * @param c
 */

bool GridMap::setCell(const int& x, const int& y, const char& c) {
    if (c == 'E' || c == 'X') {
        if ( (x == 0 || x == width-1) && (y > 0 && y < height-1) || (y == 0 || y == height-1) && (x > 0 && x < width-1) ) {
            map[y][x] = c;
            notify();
            return true;
        }
        else {
            std::cout << "Entrance/Exit must be on the boundary and not on the corner\n";
            notify();
            return false;
        }
    }
    else if (c == '#') {
        map[y][x] = c;
        if (x > 0 && map[y][x-1] == '#' || x < width - 1 && map[y][x+1] == '#' || y > 0 && map[y-1][x] == '#' || y < height - 1 && map[y+1][x] == '#') {
            char temp = getCell(x,y);
            map[y][x] = c;
            if (!hasValidPath('X')) {
                map[y][x] = temp;
                std::cout << "Illegal introduction of a wall, the map must have a valid path\n";
                notify();
                return false;
            }
            notify();
            return true;
        };
    }
    else if (c == ' ' || c == '*' || c == 'm' || c == '!') {
        map[y][x] = c;
        notify();
        return true;
    }
    else {
        std::cout << "Invalid cell.";
        notify();
        return false;
    }
    notify();
    return false;
}


/**
 * @brief Get cell
 * @param x
 * @param y
 * @return value of cell
 */
char GridMap::getCell(const int &x, const int &y) const {
    return map[y][x];
}

/**
 * @brief Display the map
 */
void GridMap::displayMap() {
    std::cout << "\n";
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            std::cout << ' ' << map[i][j] << ' ';
        }
        std::cout << '\n';
    }
}

std::string GridMap::toString() {
    std::string result = "\n";
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            result += ' ';
            result += map[i][j];
            result += ' ';
        }
        result += "\n";
    }

    return result;
}

/**
 * @brief Check if cell is valid
 * @param x
 * @param y
 * @return true if cell is valid
 * @return false if cell is invalid
 */
/*
bool GridMap::isValid(const int& x, const int& y) const {
    // Check if cell is within the map and is not a wall
    return (x >= 0 && x < width && y >= 0 && y < height && map[y][x] != '-' && map[y][x] != '|');
}
*/
bool GridMap::isValid(const int& x, const int& y) const {
    // Check if cell is within the map and is not a wall
    return (x >= 0 && x < width && y >= 0 && y < height && map[y][x] != '#');
}


/**
 * @brief Depth First Search
 * @param x
 * @param y
 * @param visited
 * @return true if path is found
 * @return false if path is not found
 */
bool GridMap::DFS(const int& x, const int& y, std::vector<std::vector<bool> >& visited, char target) {
    // Mark the current cell as visited
    visited[y][x] = true;

    // If the current cell is 'X', we have found a path
    if (map[y][x] == target) {
        return true;
    }

    // Define the possible moves (up, down, left, right)
    int dx[] = {-1, 0, 1, 0};
    int dy[] = {0, 1, 0, -1};

    // Try all possible moves
    for (int i = 0; i < 4; i++) {
        int newX = x + dx[i], newY = y + dy[i];

        // If the new cell is valid and not visited, move to it
        if (isValid(newX, newY) && !visited[newY][newX]) {
            if (DFS(newX, newY, visited, target)) {
                return true;
            }
        }
    }

    // If no valid move is found, return false
    return false;
}

/**
 * @brief Check if there is a valid path from 'E' to 'X' using DFS; used for test cases
 * @return true if there is a valid path
 * @return false if there is no valid path
 */
bool GridMap::hasValidPath(char t) {
    // Create a visited matrix
    std::vector<std::vector<bool> > visited(height, std::vector<bool>(width, false));

    // Find the cell marked 'E'
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (map[i][j] == 'E') {
                // Start DFS from 'E'
                return DFS(j, i, visited, t);
            }
        }
    }

    // If 'E' is not found, return false
    return false;
}

int GridMap::getWidth()
{
    return width;
}

int GridMap::getHeight()
{
    return height;
}


void GridMap::setCellBuilder(const int& x, const int& y, const char& c) {
    map[y][x] = c;
}

//void GridMap::increaseChests() {
//    chests += 1;
//}
//
//void GridMap::increaseCreatures() {
//    creatures += 1;
//}
//
//int GridMap::getChests() {
//    return chests;
//}
//
//int GridMap::getCreatures() {
//    return creatures;
//}

std::string GridMap::toStringF()
{
  std::string result = mapName + " " + std::to_string(width) + " " + std::to_string(height) + " " + std::to_string(entrance.first) + " " + std::to_string(entrance.second) + " " + std::to_string(exit.first) + " " + std::to_string(exit.second) + " " + std::to_string(objective.first) + " " + std::to_string( objective.second) + "\n";
  for (auto& chest : chests) {
    result += chest.second.getBagName() + " " + std::to_string(chest.first.first) + " " + std::to_string(chest.first.second) + " ";
  }
  result += "\n";
  for (auto& enemy : enemies) {
    result += enemy.second.getName() + " " + std::to_string(enemy.first.first) + " " + std::to_string(enemy.first.second) + " ";
  }
  result += "\n";
  for (auto& wall : walls) {
    result += std::to_string(wall.first) + " " + std::to_string(wall.second) + " ";
  }
  result += "\n";
  return result;

}

void GridMap::writeMapsToFile(std::vector<GridMap> mapsToWrite)
{
  std::string fileName = "../saved/Map/maps.txt";
  std::ofstream file(fileName);

  if (file.is_open()) {
    for (auto& map : mapsToWrite) {
      file << map.toStringF() << "\n";
    }
    file.close();
  } else {
    throw std::runtime_error("unable to write to file "+fileName+"\n");
  }
}

std::vector<GridMap> GridMap::readMapsFromFile(const std::vector<ItemBag>& itemBags, const std::vector<Character>& enemies)
{
  std::vector<GridMap> result;
  int coords[8];
  int cx, cy;
  std::string mname, bname, ename;
  std::pair<int,int> posWallPairTemp;
  std::pair<std::pair<int,int>,ItemBag> posBagPairTemp;
  std::pair<std::pair<int,int>,Character> posEnemyPairTemp;
  std::vector<std::pair<std::pair<int,int>,ItemBag>> chestsP;
  std::vector<std::pair<std::pair<int,int>,Character>> enemiesP;
  std::vector<std::pair<int,int>> wallsP;

// campaigns: 1, 2, 3, ... [choose 1]
// campaign1.txt -> line 1 map name
  std::ifstream file("../saved/Map/maps.txt");
  if (file.is_open()){
    std::string line1, line2, line3, line4;
    while (std::getline(file, line1) && std::getline(file, line2) && std::getline(file, line3) && std::getline(file,line4)) {
      std::istringstream iss1(line1), iss2(line2), iss3(line3), iss4(line4);
      if (iss1 >> mname >> coords[0] >> coords[1] >> coords[2] >> coords[3] >> coords[4] >> coords[5] >> coords[6] >> coords[7]) {
        Functions::convertToUpper(mname);
        while (iss2 >> bname >> cx >> cy) {
          posBagPairTemp.first.first = cx;
          posBagPairTemp.first.second = cy;
          //get the item bag
          for (auto& bag : itemBags) {
            if (bag.getBagName() == bname) {
              posBagPairTemp.second = bag;
            }
          }
          chestsP.emplace_back(posBagPairTemp);
        }
        while (iss3 >> ename >> cx >> cy) {
          posEnemyPairTemp.first.first = cx;
          posEnemyPairTemp.first.second = cy;
          //get the enemy
          for (auto& enemy : enemies) {
            if (enemy.getName() == ename) {
              posEnemyPairTemp.second = enemy;
            }
          }
          enemiesP.emplace_back(posEnemyPairTemp);
        }
        while (iss4 >> cx >> cy) {
          posWallPairTemp.first = cx;
          posWallPairTemp.second = cy;
          wallsP.emplace_back(posWallPairTemp);
        }
      }
      //construct map using P parameters
      GridMap m(mname,coords,chestsP,enemiesP,wallsP);

      //emplace constructed map to result
      result.emplace_back(m);
      m = GridMap();
    }


  } else {
    throw std::runtime_error("unable to read from file ../saved/Map/maps.txt\n");
  }
  file.close();

  return result;
}
