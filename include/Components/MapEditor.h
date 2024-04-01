#ifndef INC_345ASSIGNMENT1_MAPEDITOR_H
#define INC_345ASSIGNMENT1_MAPEDITOR_H
#include <string>
#include <vector>
#include <utility>
#include <list>

#include "MapGeneration.h"
/**
 * @class MapEditor
 * @file MapEditor.h
 * @file MapEditor.cpp
 * @brief the design approach implements an interactive menu where the user can create/edit maps and campaigns and save them to a file
 * @brief game rules involved: ensuring valid creation of maps and campaigns (campaigns can contain the same map more than once)
 * @include string for string usage and manipulation
 * @include vector for vector usage and manipulation
 * @include utility for pair usage and manipulation
 * @include list for list usage and manipulation
 * @include iostream for getting user input
 * @include fstream for getting file input and outputting to files
 * @include sstream for getting file input and outputting to files
 * @include filesystem for getting file input and outputting to files
 * @include algorithm for converting to lower case
 * @include cctype for converting to lower case
 * @include stdexcept for throwing exceptions
 * @author Steven Gingras (40098045)
*/
class MapEditor {
public:

    //HIGH LEVEL MAIN MENUS AND SAVING:=========================================================================================

    /**
     * Constructor, initializes current maps and campaigns with current maps and campaign file names. Then starts the main menu
    */
    MapEditor();
    /**
     * Main menu: the user can choose to either create/edit maps or campaigns and save them to a file
    */
    void mainMenu();
    /**
     * Create new map: creates a map from scratch
    */
    void newMap();
    /**
     * Edit map: gets a saved map and creates a GridMap object to pass to the parameterized editMap() function
    */
    void editMap();
    /**
     * Edit map: gives the option to edit a map object
     * @param map the current GridMap object being edited
     * @param mapName the name of the map being edited
    */
    void editMap(GridMap& map, const std::string& mapName);
    /**
     * Save map: saves the map to a file after having ensured its validity
     * @param map the current GridMap object being edited
     * @param mapName the name of the map being edited
    */
    void saveMap(GridMap& map, std::string mapName);



    //MAP MANIPULATION:==================================================================

    /**
     * Initializes the entrance or exit of the map
     * @param map the current GridMap object being edited
     * @param EorX a char ('E' or 'X') to choose whether to call the function on the entrance or exit
    */
    void initEOrX(GridMap& map, char EorX);
    /**
     * Sets walls in the map
     * @param map the current GridMap object being edited
    */
    void setWalls(GridMap& map);
    /**
     * Sets chests in the map
     * @param map the current GridMap object being edited
    */
    void setChests(GridMap& map);
    /**
     * Removes chests or walls from the map
     * @param map the current GridMap object being edited
    */
    void removeChestsOrWalls(GridMap& map);
    /**
     * Modifies the position of the entrance or exit
     * @param map the current GridMap object being edited
     * @param EorX a char ('E' or 'X') to choose whether to call the function on the entrance or exit
    */
    void changeEOrX(GridMap& map, char EorX);
    /**
     * Gets the (x,y) coordinates of the current position of the entrance or exit
     * @param map the current GridMap object being edited
     * @param EorX a char ('E' or 'X') to choose whether to call the function on the entrance or exit
    */
    std::pair<int,int> findEOrX(GridMap map, char EorX);
    


    //CAMPAIGN MANIPULATION:===================================================================

    /**
     * Creates a new campaign from scratch
    */
    void newCampaign();
    /**
     * Gets a saved campaign and enters the parameterized editCampaign() method
    */
    void editCampaign();
    /**
     * Edits a campaign
     * @param campaignName the name of the campaign being edited
    */
    void editCampaign(std::string campaignName);
    /**
     * Saves a finished campaign by writing the campaign to a file
     * @param campaignName the name of the campaign being edited
    */
    void saveCampaign(std::string campaignName);
    /**
     * Provides the option to insert maps into the campaign into a desired position
     * @param campaignName the name of the campaign being edited
    */
    void insertMaps(std::string campaignName);
    /**
     * Provides the option to remove maps from the campaign from a desired position
     * @param campaignName the name of the campaign being edited
    */
    void removeMaps(std::string campaignName);



    //VALIDATION AND DISPLAYING:====================================================================

    /**
     * Validates that a map exists in the saved files
     * @param mapName the name of the map to check
    */
    bool validateMap(std::string mapName);
    /**
     * Validates that a campaign exists in the saved files
     * @param campaignName the name of the campaign to check
    */
    bool validateCampaign(std::string campaignName);
    /**
     * Validates that a map is in a campaign
     * @param mapName the name of the map to check
    */
    int mapIsInCampaign(std::string mapName);
    /**
     * Displays a map from a saved map file
     * @param mapName the name of the map to display
    */
    void showMapFile(std::string mapName);
    /**
     * Displays the campaign's map order
     * @param campaignName the name of the campaign to display
    */
    void printCampaign(std::string campaignName);
    /**
     * Displays all saved maps
    */
    void printCurrentMaps();
    /**
     * Displays all saved campaigns
    */
    void printCurrentCampaigns();


private:
    
    std::vector<std::string> currentMaps;///< a string vector of the current saved maps
    std::vector<std::string> currentCampaigns;///< a string vector of the current saved campaigns

    std::list<std::string> campaignMaps;///< a string list storing the maps order currently selected by the user
};

#endif