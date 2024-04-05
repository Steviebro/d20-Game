/**
 * @file MapEditor.cpp
 * @ref MapEditor.h
 * @author Steven Gingras (40098045)
*/

#include "../../include/Components/MapEditor.h"
#include "../../include/Components/MapGeneration.h"
#include "../../include/Components/MapBuilder.h"
#include "../../include/Components/MapDirector.h"
#include "../../include/Components/MapConcreteBuilder.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>

#include <vector>
#include <string>
#include <utility>
#include <list>

#include <algorithm>
#include <cctype>
#include <stdexcept>

MapEditor::MapEditor()
{
    for (const auto& mapFile : std::filesystem::directory_iterator("../maps/")) {
        currentMaps.emplace_back(mapFile.path().filename().string());
    }

    for (const auto& campaignFile : std::filesystem::directory_iterator("../campaigns/")) {
        currentCampaigns.emplace_back(campaignFile.path().filename().string());
    }

    mainMenu();
}

void MapEditor::mainMenu()
{
    char inputChar;
    do {
        std::cout << "Welcome to the interactive map/campaign creator/editor, please select an option from the list below:\n"
        << "1 - CREATE NEW MAP\n"
        << "2 - EDIT MAP\n"
        << "3 - CREATE NEW CAMPAIGN\n"
        << "4 - EDIT CAMPAIGN\n"
        << "0 - EXIT MAP EDITOR\n"
        << "Your selection: ";
        std::cin >> inputChar;

        switch(inputChar) {
            case '1':
            newMap();
            break;
            case '2':
            editMap();
            break;
            case '3':
            newCampaign();
            break;
            case '4':
            editCampaign();
            break;
            case '0':
            break;
            default:
            std::cout << "Invalid input, please try again!\n";
        }
    } while (inputChar != '0');
}

void MapEditor::newMap()
{
    bool valid = true;
    std::string mapName;

    std::cout << "Welcome to the map creator! Please answer the below questions to create your map:\n"
    << "Let's start by naming your new map.\n";

    //1) Naming the map
    do {
        valid = true;
        std::cout << "Please choose a UNIQUE name for your NEW map which is NOT in the following list:\n";
        for (const auto& f : currentMaps) {
            std::cout << f << "\n";
        }
        std::cout << "Your selection (without .txt file extension): ";
        std::cin >> mapName;

        std::transform(mapName.begin(), mapName.end(), mapName.begin(), ::tolower);

        //Check if mapName already exists
        for (const auto& f : currentMaps) {
            if(f == mapName+".txt") {
                valid = false;
                std::cout << "The mapName you entered already exists, please try again.\n";
            }
        }

    } while (!valid);

    std::cout << "Map successfully named " << mapName << " !\n";

    //2) Set Map Size
    int width, height;

    std::cout << "Now you must choose a width and height for your new map:\n"
    << "Map Width: ";
    std::cin >> width;

    std::cout << "Map Height: ";
    std::cin >> height;

    //Construct empty map
    GridMap map(width,height);
    map.displayMap();


    //3) Set Entrance
    std::cout << "Now you must select where you want the entrance and exit of your map.\n"
    << "Note that you MUST place the entrance/exit at the edge of the map AND it can NOT be in the corner.\n"
    << "Examine the above map and give the (x,y) coordinates of where you want the entrance.\n";

    initEOrX(map,'E');
    map.displayMap();
    std::cout << "Entrance successfully added to the map!\n";


    //4) Set Exit
    std::cout << "Now examine the above map and give the (x,y) coordinates for the exit.\n"
    << "Note that it MUST be on the edge of the map AND in a different place than the Entrance\n";

    initEOrX(map,'X');
    map.displayMap();
    std::cout << "Exit successfully added to the map!\n";


    //5) Set Objective
    std::cout << "Now add an objective that will unlock the exit and give the (x,y) coordinates for the objective.\n"
    << "Note that it MUST be within the outside borders and NOT on a pre-existing wall.\n";
    addObjective(map);
    map.displayMap();


    //6) Add Walls
    char input;
    std::cout << "You may now add walls to the map.\n";
    do {
        valid = true;
        std::cout << "Please select from the options below:\n"
        << "1 - Add Walls\n"
        << "0 - No More Walls!\n"
        << "Your selection: ";

        std::cin >> input;

        switch(input) {
            case '1':
            setWalls(map);
            break;
            case '0':
            break;
            default:
            std::cout << "Invalid input, please enter 0 or 1.\n";
            valid = false;
        }
    } while (!valid);


    //7) Add chests
    std::cout << "You may now add chests to the map.\n";
    do {
        valid = true;
        std::cout << "Please select from the options below:\n"
        << "1 - Add A Chest\n"
        << "0 - No Chests\n"
        << "Your selection: ";
        std::cin >> input;

        switch(input) {
            case '1':
            setChests(map);
            break;
            case '0':
            break;
            default:
            std::cout << "Invalid input, please enter 0 or 1.\n";
            valid = false;
        }
    } while (!valid);

    //8) Validate if any more changes to make

    std::cout << "Your map now looks complete:\n";
    map.displayMap();
    std:: cout << "Would you like to make any more changes?\n";
    do {
        valid = true;
        std::cout << "Please select from the below choices:\n"
        << "1 - Make Changes\n"
        << "0 - No Changes, I'm ready to save my map!\n"
        << "Your selection: ";
        std::cin >> input;

        switch (input) {
            case '1':
            editMap(map,mapName);
            break;
            case '0':
            break;
            default:
            std::cout << "Invalid input, please enter 0 or 1\n";
            valid = false;
        }
    } while (!valid);

    //9) Save the new map!

    std::cout << "Now we can save the map! Map " << mapName << " saving...\n";

    saveMap(map, mapName);
    currentMaps.emplace_back(mapName+".txt");

}

void MapEditor::editMap()
{
    if (currentMaps.empty()) {
        std::cout << "There are no maps to edit! Try creating a new map instead.\n";
        return;
    }

    bool valid;
    std::string input;
    std::cout << "Welcome to the map editor where you can edit a map.\n";
    do {
        valid = false;
        std::cout << "Before continuing, you must select which map you want to edit from the following list:\n";
        
        for (const auto& f : currentMaps) {
            std::cout << f << "\n";
        }

        std::cout << "Please enter your selection WITHOUT the .txt file extension.\n"
        << "Your selection: ";
        std::cin >> input;
        std::transform(input.begin(), input.end(), input.begin(), ::tolower);

        for (const auto& f : currentMaps) {
            if (f == input+".txt") {
                valid = true;
            }
        }
        if (!valid) {
            std::cout << "Invalid inputs, you must enter an existing map name. Please try again.\n";
        }
    } while (!valid);

    //TODO: invoke builder on filename to create the GridMap object*************************************************
    //MapBuilder mb(input);
    //GridMap toEdit = mb.getGridMap();
    //editMap(toEdit);
    //**************************************************************************************************************

    MapDirector mapCreator;
    MapBuilder* concreteBuilder1 = new MapConcreteBuilderBasic;

    mapCreator.setMapBuilder(concreteBuilder1);
    
    mapCreator.constructMap(1, "../maps/"+input+".txt");
    GridMap* constructor1 = mapCreator.getMap();
    editMap(*constructor1,input);
}

void MapEditor::editMap(GridMap& map, const std::string& mapName)
{
    char input;
    std::cout << "Welcome to the map editor where you can edit your " << mapName << " map:\n";

    do {
        map.displayMap();
        std::cout << "Please select from the below choices:\n"
        << "1 - Add More Walls\n"
        << "2 - Add More Chests\n"
        << "3 - Remove Chests or Walls\n"
        << "4 - Change Entrance Location\n"
        << "5 - Change Exit Location\n"
        << "6 - Add Objective\n"
        << "0 - No Changes, I'm ready to save my map!\n"
        << "Your selection: ";
        std::cin >> input;

        switch (input) {
            case '1':
            setWalls(map);
            break;
            case '2':
            setChests(map);
            break;
            case '3':
            removeChestsOrWalls(map);
            break;
            case '4':
            changeEorXorO(map,'E');
            break;
            case '5':
            changeEorXorO(map,'X');
            break;
            case '6':
            addObjective(map);
            break;
            case '7':
            changeEorXorO(map, '!');
            break;
            case '0':
            break;
            default:
            std::cout << "Invalid input, please enter 0, 1, 2, or 3.\n";
        }
    } while (input != '0');

    saveMap(map,mapName);
}

void MapEditor::saveMap(GridMap &map, std::string mapName)
{
    //Validate map before saving:
    if (!map.hasValidPath('X')) {
        std::cerr << "ERROR saving map: Map does not have a valid path. THE MAP WAS NOT SAVED.\n"
        << mapName << ":\n" << map.toString();
        return;
    }
    
    std::string fileContents = map.toString();
    mapName = mapName + ".txt";

    std::ofstream file("../maps/"+mapName);
    file << fileContents;
    file.close();

    std::cout << "Map successfully saved to file " << mapName << " in the maps/ directory.\n"
    << "Here is the final product:\n";

    map.displayMap();
}

void MapEditor::initEOrX(GridMap &map, char EorX)
{

    EorX = std::toupper(EorX);
    if (EorX != 'X' && EorX != 'E') {
        throw std::runtime_error("Attempting to assign 'E' or 'X' without passing 'E' or 'X' as arguments");
    }

    int x, y;
    bool valid = false;
    do {
        std::cout << "Provide a value for 'x' between 0 and "<< map.getWidth()-1 <<": ";
        std::cin >> x;
        std::cout << "Provide a value for 'y' between 0 and "<< map.getHeight()-1 <<": ";
        std::cin >> y;

        if (x >= 0 && y >= 0 && x < map.getWidth() && y < map.getHeight()) {//checking within range of map
            if ((x != 0 && x != map.getWidth() - 1) || (y != 0 && y != map.getHeight() - 1)) {//checking not a corner
                if (map.getCell(x,y) == '#') {//checking edge
                    valid = true;
                } else {
                    std::cout << "Invalid inputs, MUST put the entrance at the edge of the map.Please try again.\n";
                }
            } else {
                std::cout << "Invalid inputs, cannot put the entrance on a corner.Please try again.\n";
            }
        } else {
            std::cout << "Invalid inputs, values must lie within the width and height of the map. Please try again.\n";
        }
    } while (!valid);

    //Valid Entrance/Exit Location, add it:
    map.setCell(x,y,EorX);
}

void MapEditor::setWalls(GridMap &map)
{
    char input;
    int x, y;
    bool wallAdded = false;

    std::cout << "\nADDING WALLS:\n"
    << "Note that walls MUST be placed adjacent to existing walls and must allow for a valid path from E to X.\n"
    << "Please provide (x,y) coordinates for where you want to place each wall.\n";
    map.displayMap();

    do {
        wallAdded = false;
        std::cout << "Provide a value for 'x' between 1 and "<< map.getWidth()-2 <<": ";
        std::cin >> x;
        std::cout << "Provide a value for 'y' between 1 and "<< map.getHeight()-2 <<": ";
        std::cin >> y;


        if (x > 0 && y > 0 && x < map.getWidth()-1 && y < map.getHeight()-1) {//checking within outside border of map
            if (x > 0 && map.getCell(x-1,y) == '#' || x < map.getWidth()-1 && map.getCell(x+1,y) == '#' || y > 0 && map.getCell(x,y-1) == '#' || y < map.getHeight()-1 && map.getCell(x,y+1) == '#') {//checking that there is adjacent wall
                wallAdded = map.setCell(x,y,'#');//function already checks for valid path and will not set if invalid
            } else {
                std::cout << "Invalid inputs, walls MUST be placed adjacent to existing walls. Please try again.\n";
            }
        } else {
            std::cout << "Invalid inputs, values must lie within the width and height of the map. Please try again.\n";
        }

        if (wallAdded) {
            std::cout << "Wall successfully added!\n";
        } else {
            std::cout << "Wall NOT successfully added.\n";
        }

        map.displayMap();

        std::cout << "Please select an option from the below choices.\n"
        << "1 - Add Another Wall\n"
        << "0 - No More Walls!\n"
        << "Your selection: ";
        std::cin >> input;
    } while (input != '0');
}

void MapEditor::setChests(GridMap &map)
{
    char input;
    int x, y;
    bool chestAdded = false;

    std::cout << "\nADDING CHESTS:\n"
    << "Note that chests must be placed within the map border walls.\n"
    << "Please provide (x,y) coordinates for where you want to place each chest.\n";
    map.displayMap();

    do {
        chestAdded = false;
        std::cout << "Provide a value for 'x' between 1 and "<< map.getWidth()-2 <<": ";
        std::cin >> x;
        std::cout << "Provide a value for 'y' between 1 and "<< map.getHeight()-2 <<": ";
        std::cin >> y;


        if (x > 0 && y > 0 && x < map.getWidth()-1 && y < map.getHeight()-1) {//checking within outside border
            if (map.getCell(x,y) != '#') {//checking that chest will not be placed on a wall
                chestAdded = map.setCell(x,y,'*');
            } else {
                std::cout << "Invalid inputs, can NOT place a chest on a wall! Please try again.\n";
                chestAdded = false;
            }
        } else {
            std::cout << "Invalid inputs, values must lie within the outside border of the map. Please try again.\n";
            chestAdded = false;
        }

        if (chestAdded) {
            std::cout << "Chest successfully added!\n";
        } else {
            std::cout << "Chest NOT successfully added.\n";
        }

        map.displayMap();

        std::cout << "Please select an option from the below choices.\n"
        << "1 - Add Another Chest.\n"
        << "0 - No More Chests!\n"
        << "Your selection: ";
        std::cin >> input;
    } while (input != '0');    
}

void MapEditor::removeChestsOrWalls(GridMap& map)
{
    char input;
    int x, y;
    bool tileRemoved;
    std::string toRemove;

    std::cout << "\nREMOVING CHESTS OR WALLS:\n"
    << "Note that you may not remove map border walls.\n"
    << "Please provide (x,y) coordinates for where you want to remove each chest/wall.\n";
    map.displayMap();

    do {
        tileRemoved = false;
        std::cout << "Provide a value for 'x' between 1 and "<< map.getWidth()-2 <<": ";
        std::cin >> x;
        std::cout << "Provide a value for 'y' between 1 and "<< map.getHeight()-2 <<": ";
        std::cin >> y;

        

        if (x > 0 && y > 0 && x < map.getWidth()-1 && y < map.getHeight()-1) {//checking within outside border
            
            //Check what we are removing
            switch(map.getCell(x,y)) {
                case '#':
                toRemove = "WALL";
                break;
                case '*':
                toRemove = "CHEST";
                break;
                case ' ':
                toRemove = "";
                break;
                default:
                throw std::runtime_error("Value retrieved from getCell("+std::to_string(x)+","+std::to_string(y)+") is unexpected in map:\n"+map.toString());
            }

            //if we're removing something
            if (toRemove != "") {
                do {
                    std::cout << "Are you sure you would like to remove the " << toRemove << " at coordinates (" << x << "," << y << ")?\n"
                    << "1 - Yes, remove it!\n"
                    << "0 - No, don't remove it!\n"
                    << "Your selection: ";
                    std::cin >> input;

                    switch (input) {
                        case '1':
                        std::cout << "Removing the " << toRemove << " at coordinates (" << x << "," << y << ")\n";
                        tileRemoved = map.setCell(x,y,' ');
                        break;
                        case '0':
                        tileRemoved = false;
                        break;
                        default:
                        std::cout << "Invalid inputs, please enter 0 or 1.\n";
                    }

                } while (input != '0' && input != '1');
            } else {//if we're removing nothing
                std::cout << "There is nothing to remove at coordinates (" << x << "," << y << ").\n";
                tileRemoved = false;
            }
            
        } else {
            std::cout << "Invalid inputs, values must lie within the outside border of the map. Please try again.\n";
            tileRemoved = false;
        }

        if (tileRemoved) {
            std::cout << toRemove << " successfully removed from the map!\n";
        } else {
            std::cout << "Nothing was removed from the map.\n";
        }

        map.displayMap();

        std::cout << "Please select an option from the below choices.\n"
        << "1 - Remove more Chests/Walls.\n"
        << "0 - No More Removing!\n"
        << "Your selection: ";
        std::cin >> input;
    } while (input != '0');
}

void MapEditor::changeEorXorO(GridMap& map, char EorXorO)
{
  bool EorX = false;
  if (EorXorO == 'E' || EorXorO == 'X'){
    EorXorO = std::toupper(EorXorO);
    EorX = true;
  }
  if (EorXorO != 'X' && EorXorO != 'E' && EorXorO != '!') {
    throw std::runtime_error("Attempting to assign 'E', 'X', or '!' without passing 'E', 'X', or '!' as arguments");
  }
  std::string toChange;
  switch (EorXorO) {
    case 'E':
      toChange = "ENTRANCE";
      break;
    case 'X':
      toChange = "EXIT";
      break;
    case '!':
      toChange = "OBJECTIVE";
      break;
    default:
      std::cerr << "Something went wrong, not E, X, or '!' passed";
      return;
  }

  std::pair<int,int> currentLocation = findEOrX(map,EorXorO);
  int x, y;
  bool valid = false;
  if (EorX) {
    std::cout << "\nCHANGING " << toChange << " LOCATION:\n"
              << "Note that you MUST place the " << toChange
              << " at the edge of the map AND it can NOT be in the corner.\n"
              << "Also note that the new " << toChange << " location must allow for a valid path from E to X.\n"
              << "Examine the below map and give the (x,y) coordinates of where you want the " << toChange << ".\n";
  } else {
    std::cout << "\nCHANGING OBJECTIVE LOCATION:\n"
              << "Note that the objective must be placed within the map border walls.\n"
              << "Please provide (x,y) coordinates for where you want to place the objective.\n";
  }
  map.displayMap();

  if (EorX) {
    do {
      std::cout << "Provide a value for 'x' between 0 and " << map.getWidth() - 1 << ": ";
      std::cin >> x;
      std::cout << "Provide a value for 'y' between 0 and " << map.getHeight() - 1 << ": ";
      std::cin >> y;

      if (x >= 0 && y >= 0 && x < map.getWidth() && y < map.getHeight()) {//checking within range of map
        if ((x != 0 && x != map.getWidth() - 1) ||
            (y != 0 && y != map.getHeight() - 1)) {//checking not a corner
          if (x == 0 || x == map.getWidth() - 1 || y == 0 || y == map.getHeight() - 1) {//checking is edge
            if (map.getCell(x, y) != 'X' && map.getCell(x, y) != 'E') {//checking not already assigned
              valid = true;
            } else {
              std::cout
                  << "Invalid inputs, an entrance/exit is already assigned here. Please try again.\n";
            }
          } else {
            std::cout
                << "Invalid inputs, MUST put the entrance at the edge of the map. Please try again.\n";
          }
        } else {
          std::cout << "Invalid inputs, cannot put the entrance on a corner. Please try again.\n";
        }
      } else {
        std::cout
            << "Invalid inputs, values must lie within the width and height of the map. Please try again.\n";
      }
    } while (!valid);
  } else {
    do {
      std::cout << "Provide a value for 'x' between 1 and " << map.getWidth() - 2 << ": ";
      std::cin >> x;
      std::cout << "Provide a value for 'y' between 1 and " << map.getHeight() - 2 << ": ";
      std::cin >> y;

      if (x > 0 && y > 0 && x < map.getWidth() - 1 && y < map.getHeight() - 1) {//checking within outside border
        if (map.getCell(x, y) != '#') {//checking that objective will not be placed on a wall
          valid = true;
        } else {
          std::cout << "Invalid inputs, can NOT place the objective on a wall! Please try again.\n";
          valid = false;
        }
      } else {
        std::cout << "Invalid inputs, values must lie within the outside border of the map. Please try again.\n";
        valid = false;
      }
    } while (!valid);
  }
  //Valid Entrance/Exit Location, add it:
  map.setCell(x,y,EorXorO);

  //Ensure valid path, revert if not
  if (EorX && !map.setCell(currentLocation.first,currentLocation.second,'#')) {//setting invalid wall is reverted in GridMap class
    std::cerr << "New " << toChange << " location is invalid, does not allow for a valid path from E to X or !.\n";
    map.setCell(x,y,'#');//reverting new entrance/exit location to wall
    std::cout << "Map changes reverted.\n";
  } else if (!EorX && !map.hasValidPath('!')) {
    std::cerr << "New objective location is invalid, does not allow for a valid path from E to X or !.\n";
    map.setCell(x, y, ' ');//reverting new objective location to empty
    std::cout << "Map changes reverted.\n";
  } else {
    std::cout << toChange << " changed successfully!\n";
  }
}

// add objective cell (!) to enable exit
void MapEditor::addObjective(GridMap& map) {
    int x, y;
    bool objectiveAdded = false;

    std::cout << "\nADDING OBJECTIVE:\n"
              << "Note that the objective must be placed within the map border walls.\n"
              << "Please provide (x,y) coordinates for where you want to place the objective.\n";
    map.displayMap();

    do {
        std::cout << "Provide a value for 'x' between 1 and " << map.getWidth() - 2 << ": ";
        std::cin >> x;
        std::cout << "Provide a value for 'y' between 1 and " << map.getHeight() - 2 << ": ";
        std::cin >> y;
        if (x > 0 && y > 0 && x < map.getWidth() - 1 && y < map.getHeight() - 1) {//checking within outside border
            if (map.getCell(x, y) != '#') {//checking that objective will not be placed on a wall
                objectiveAdded = map.setCell(x, y, '!');
            } else {
                std::cout << "Invalid inputs, can NOT place the objective on a wall! Please try again.\n";
                objectiveAdded = false;
            }
        } else {
            std::cout << "Invalid inputs, values must lie within the outside border of the map. Please try again.\n";
            objectiveAdded = false;
        }
    } while (!objectiveAdded);
    if (!map.hasValidPath('!')) {
        std::cerr << "ERROR adding objective: Map does not have a valid path. THE OBJECTIVE WAS NOT ADDED.\n"
                  << ":\n"
                  << map.toString();
        map.setCell(x, y, ' ');
        return;
    } else {
        std::cout << "Objective successfully added!\n";
    }
}

std::pair<int, int> MapEditor::findEOrX(GridMap map, char EorX)
{
    EorX = std::toupper(EorX);
    if (EorX != 'X' && EorX != 'E') {
        throw std::runtime_error("Attempting to find 'E' or 'X' without passing 'E' or 'X' as arguments");
    }

    int height = map.getHeight();
    int width = map.getWidth();

    for (int i = 0 ; i < height ; i++) {
        for (int j = 0 ; j < width ; j++) {
            if (map.getCell(j,i) == EorX) {
                return std::make_pair(j,i);
            }
        }
    }

    //if reaching end of search without finding, error
    throw std::runtime_error("Unable to find "+std::to_string(EorX)+" in the map:\n"+map.toString());
}

void MapEditor::newCampaign()
{
    if (currentMaps.size() == 0) {
        std::cout << "There are no maps to add to a campaign! Try creating a new map first.\n";
        return;
    }

    bool valid = true;
    std::string campaignName;
    char input;
    int mapNum = 1;
    std::string mapName;

    campaignMaps.clear();

    std::cout << "Welcome to the campaign creator! Please answer the below questions to create your campaign:\n"
    << "Let's start by naming your new campaign.\n";

    //1) Naming the campaign

    do {
        valid = true;
        std::cout << "Please choose a UNIQUE name for your NEW campaign which is NOT in the following list:\n";
        for (const auto& f : currentCampaigns) {
            std::cout << f << "\n";
        }
        std::cout << "Your selection (without .txt file extension): ";
        std::cin >> campaignName;

        std::transform(campaignName.begin(), campaignName.end(), campaignName.begin(), ::tolower);

        //Check if campaignName already exists
        for (const auto& f : currentCampaigns) {
            if(f == campaignName+".txt") {
                valid = false;
                std::cout << "The campaignName you entered already exists, please try again.\n";
            }
        }

    } while (!valid);

    std::cout << "Campaign successfully named " << campaignName << " !\n";


    //2) Establishing map order

    std::cout << "You must now select maps that you wish to add to the campaign.\n"
    << "You will add the maps one at a time, sequentially, starting with the first one.\n";

    do {
        do {
            valid = false;
            std::cout << "\nChoosing map #" << mapNum << "\n"
            << "Please choose a map from the following list:\n";

            for (const auto& map : currentMaps) {
                std::cout << map << "\n";
            }

            std::cout << "Your selection: ";
            std::cin >> mapName;
            std::transform(mapName.begin(), mapName.end(), mapName.begin(), ::tolower);

            valid = validateMap(mapName);

            if (!valid) {
                std::cout << "Invalid inputs, you must select a map from the list of current maps. Please try again.\n";
            }
        } while (!valid);

        //Show user the map and ask to confirm addition
        std::cout << "The chosen map " << mapName << " was found.\n"
        << "This is how it looks:\n";

        showMapFile(mapName);

        std::cout << "Are you sure you want to add this map to position #" << mapNum << "?\n"
        << "1 - Yes, add the map!\n"
        << "0 - No, don't add it.\n"
        << "Your selection: ";
        std::cin >> input;

        if (input == '1') {
            campaignMaps.emplace_back(mapName+".txt");
            std::cout << "Map #" << mapNum << " successfully set as " << mapName << " in campaign " << campaignName << "!\n";
            mapNum++;
        } else {
            std::cout << "Map " << mapName << " was NOT set in the campaign.\n";
        }

        printCampaign(campaignName);

        std::cout << "Please choose from the below options:\n"
        << "1 - Add More Maps!\n"
        << "0 - No More Maps.\n"
        << "Your selection: ";
        std::cin >> input;
    } while (input != '0');


    //3) Request if any changes to make

    std::cout << "Your campaign looks complete!\n"
    << "Here is how it looks:\n";
    mapNum = 1;

    printCampaign(campaignName);

    std:: cout << "Would you like to make any more changes or continue working on this campaign?\n";
    do {
        valid = true;
        std::cout << "Please select from the below choices:\n"
        << "1 - Make Changes And Continue Working\n"
        << "0 - No Changes, I'm ready to save my campaign!\n"
        << "Your selection: ";
        std::cin >> input;

        switch (input) {
            case '1':
            editCampaign(campaignName);
            break;
            case '0':
            break;
            default:
            std::cout << "Invalid input, please enter 0 or 1\n";
            valid = false;
        }
    } while (!valid);


    //4) Save campaign (if flow didn't go to editCampaign())
    if (input != '1') {
        std::cout << "Now we can save the campaign! Campaign " << campaignName << " saving...\n";

        saveCampaign(campaignName);
        currentCampaigns.emplace_back(campaignName+".txt");
    }


}

void MapEditor::editCampaign()
{
    if (currentCampaigns.size() == 0) {
        std::cout << "There are no campaigns to edit! Try creating a new campaign instead.\n";
        return;
    }

    bool valid;
    std::string input;
    std::cout << "Welcome to the campaign editor where you can edit a campaign.\n";
    do {
        valid = false;
        std::cout << "Before continuing, you must select which campaign you want to edit from the following list:\n";
        
        printCurrentCampaigns();

        std::cout << "Please enter your selection WITHOUT the .txt file extension.\n"
        << "Your selection: ";
        std::cin >> input;
        std::transform(input.begin(), input.end(), input.begin(), ::tolower);

        valid = validateCampaign(input);
        if (!valid) {
            std::cout << "Invalid inputs, you must enter an existing campaign name. Please try again.\n";
        }
    } while (!valid);

    editCampaign(input);
}

void MapEditor::editCampaign(std::string campaignName)
{
    //First, if not coming from newCampaign(), get the campaign from the file and store its data in campaignMaps
    if (validateCampaign(campaignName)) {
        campaignMaps.clear();
        std::ifstream file("../campaigns/"+campaignName+".txt");

        std::string fileContents((std::istreambuf_iterator<char>(file)),std::istreambuf_iterator<char>());

        std::istringstream campaignMapStream(fileContents);
        std::string mapFileName;
        while (std::getline(campaignMapStream,mapFileName)) {
            if (!mapFileName.empty()) {
                campaignMaps.emplace_back(mapFileName);
            }
        }
    }
    //otherwise just continue, we already have our data in campaignMaps

    char input;

    std::cout << "Welcome to the campaign editor where you can edit your " << campaignName << " campaign.\n";

    do {
        printCampaign(campaignName);
        std::cout << "Please select an option from the below choices:\n"
        << "1 - Insert Maps\n"
        << "2 - Remove Maps\n"
        << "0 - No Changes. I'm ready to save my campaign!\n"
        << "Your selection: ";
        std::cin >> input;


        switch (input) {
            case '1':
            insertMaps(campaignName);
            break;
            case '2':
            removeMaps(campaignName);
            break;
            case '0':
            break;
            default:
            std::cout << "Invalid input, please select 1, 2 or 0.\n";
        }

    } while (input != '0');

    saveCampaign(campaignName);
}

void MapEditor::saveCampaign(std::string campaignName)
{
    //Check validity of campaign
    bool valid;
    for (const auto& mapFileName : campaignMaps) {
        valid = false;
        for (const auto& map : currentMaps) {
            if (mapFileName == map) {
                valid = true;
            }
        }
        if (!valid) {
            std::cerr << "ERROR: Invalid campaign, it contains a map which is not in the current maps.\n"
            << mapFileName << " was not found in the list of current maps.\n"
            << "The campaign " << campaignName << " was NOT SAVED.\n"
            << "Campaign:\n";
            for (const auto& c : campaignMaps) {
                std::cout << c << "\n";
            }
            return;
        }
    }

    //Add campaign to campaigns directory
    campaignName = campaignName + ".txt";
    std::string fileContents;
    for (const auto& mapFileName : campaignMaps) {
        fileContents += mapFileName;
        fileContents += "\n";
    }

    std::ofstream file("../campaigns/"+campaignName);
    file << fileContents;
    file.close();

    std::cout << "Campaign successfully saved to file " << campaignName << " in the campaigns/ directory.\n"
    << "Here is the final product:\n"
    << fileContents;

    campaignMaps.clear();
}

void MapEditor::insertMaps(std::string campaignName)
{
    bool valid;
    char input;

    std::string mapToInsert;
    int posToInsert;
    
    std::cout << "\nINSERTING MAPS:\n"
    << "For each map you wish to insert, please provide the name of the map and the the position where you want to insert it.\n";
    printCampaign(campaignName);

    do {
        std::cout << "Please provide a map from the below list (without .txt) to insert into the campaign:\n";
        printCurrentMaps();
        std::cout << "Your selection: ";
        std::cin >> mapToInsert;
        std::transform(mapToInsert.begin(), mapToInsert.end(), mapToInsert.begin(), ::tolower);

        valid = validateMap(mapToInsert);

        if (valid) {
            std::cout << "Here is the selected map:\n";
            showMapFile(mapToInsert);

            std::cout << "Where do you want to insert the map?\n"
            << "Note that the position specified will be replaced by your chosen map and the maps below it will be shifted down.\n"
            << "Enter " << campaignMaps.size()+1 << " if you wish to place the map at the end of the campaign.\n"
            << "Your selection: ";
            std::cin >> posToInsert;

            //Make sure position is within the campaign's size
            if (posToInsert > 0 && posToInsert <= campaignMaps.size()+1) {
                std::cout << "You are about to insert the above map into position #" << posToInsert << ".\n"
                << "Are you sure you wish to proceed?\n"
                << "1 - Yes, insert it!\n"
                << "0 - No, don't insert it.\n"
                << "Your selection: ";
                std::cin >> input;

                if (input != '0') {
                    auto it = campaignMaps.begin();
                    std::advance(it, posToInsert - 1);
                    campaignMaps.emplace(it, mapToInsert+".txt");
                    std::cout << "Map successfully inserted!\n";
                }
            } else {
                std::cout << "Invalid inputs, the entered position is out of bounds. Please try again.\n";
            }

        } else {
            std::cout << "Invalid inputs, the entered map does not exist. Please try again.\n";
        }

        printCampaign(campaignName);

        std::cout << "Please choose from the below options:\n"
        << "1 - Insert More Maps!\n"
        << "0 - No More Inserting.\n"
        << "Your selection: ";
        std::cin >> input;
    } while (input != '0');

}

void MapEditor::removeMaps(std::string campaignName)
{
    bool valid;
    char input;

    std::string mapToRemove;
    int posToRemove;
    
    std::cout << "\nREMOVING MAPS:\n"
    << "For each map you wish to remove, please provide the name of the map.\n";
    printCampaign(campaignName);

    do {
        if (campaignMaps.empty()) {
            std::cout << "Your campaign is now empty! You may no longer remove maps from it.\n";
            return;
        }
        std::cout << "Please provide a position from your campaign (without .txt) to remove from the campaign:\n";
        printCampaign(campaignName);
        std::cout << "Your selection: ";
        std::cin >> posToRemove;

        if (posToRemove > 0 && posToRemove <= campaignMaps.size()) {
            auto it = campaignMaps.begin();
            std::advance(it, posToRemove - 1);

            mapToRemove = *it;

            if (mapToRemove.length() >= 0) {
                mapToRemove = mapToRemove.substr(0, mapToRemove.length() - 4);
            } else {
                std::cerr << "An ERROR occurred, unexpected values in position " << posToRemove << " in campaignMaps list";
            }

            std::cout << "Here is the selected map:\n";
            showMapFile(mapToRemove);
            

            std::cout << "You are about to remove the above map from position #" << posToRemove << " .\n"
            << "Are you sure you wish to proceed?\n"
            << "1 - Yes, remove it!\n"
            << "0 - No, don't remove it.\n"
            << "Your selection: ";
            std::cin >> input;

            if (input != '0') {
                campaignMaps.erase(it);
                std::cout << "Map successfully removed!\n";
            }
            

        } else {
            std::cout << "Invalid inputs, the entered map is not in the campaign. Please try again.\n";
        }

        printCampaign(campaignName);

        std::cout << "Please choose from the below options:\n"
        << "1 - Remove More Maps!\n"
        << "0 - No More Removing.\n"
        << "Your selection: ";
        std::cin >> input;
    } while (input != '0');
}

bool MapEditor::validateMap(std::string mapName)
{
    for (const auto& map : currentMaps) {
        if (map == mapName+".txt") {
            return true;
        }
    }
    return false;
}

bool MapEditor::validateCampaign(std::string campaignName)
{
    for (const auto& f : currentCampaigns) {
        if (f == campaignName+".txt") {
            return true;
        }
    }
    return false;
}

int MapEditor::mapIsInCampaign(std::string mapName)
{
    int pos = 0;
    for (const auto& map : campaignMaps) {
        if (map == mapName+".txt") {
            return pos;
        }
        pos++;
    }
    return -1;
    
}

void MapEditor::showMapFile(std::string mapName)
{
    mapName = mapName + ".txt";

    std::ifstream file("../maps/"+mapName);

    std::string fileContents((std::istreambuf_iterator<char>(file)),std::istreambuf_iterator<char>());

    std::cout << fileContents;
}

void MapEditor::printCampaign(std::string campaignName)
{
    int mapNum = 1;

    std::cout << "\nCampaign: " << campaignName << "\n"
    << "Maps:\n";

    for (const auto& mapFileName : campaignMaps) {
        std::cout << "Map #" << mapNum++<< ": " << mapFileName << "\n";
    }
    std::cout << "\n";
}

void MapEditor::printCurrentMaps()
{
    for (const auto& f : currentMaps) {
        std::cout << f << "\n";
    }
}

void MapEditor::printCurrentCampaigns()
{
    for (const auto& f : currentCampaigns) {
        std::cout << f << "\n";
    }
}