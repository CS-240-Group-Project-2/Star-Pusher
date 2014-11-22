#include "Board.h"

//!Constructor
Board::Board(vector<string> newMap, vector<images> imageDatabase){
    //!!!!!!!! Load in the string vector map here !!!!!!!!!
    //Setup array height and width of map loaded into new Board object.
    int mapHeight = newMap.size();
    int mapWidth = 0;
    for(int i = 0; i < newMap.size() - 1; ++i){
        if(newMap[i].length() > mapWidth){
            mapWidth = newMap[i].length();
        }
    }
    //!!!!!!!! Convert string vector map to array !!!!!!!!!
    //Create mapArray matrices, according to mapHeight/mapWidth, from newMap vector.
    char mapArray[mapHeight][mapWidth];
    for(int i = 0; i < mapHeight - 1; ++i){
        for(int j = 0; j < mapWidth - 1; ++j){
            //!!!!! Might need to assess strings that are less than mapWidth? !!!!!!
            mapArray[i][j] = {newMap[i].at(j)};
        }
    }
    //!!!!!!!! Find and set player position       !!!!!!!!!

    //!!!!!!!! Find and set star positions        !!!!!!!!!

    //!!!!!!!! Find and set goal positions        !!!!!!!!!
}

//!Destructor
Board::~Board(){

}

//!render
void Board::render(){
    //!!!!!!!! Render the current 2d array        !!!!!!!!!

}

//!movement
void Board::movement(int x, int y){
    //!!!!!!!! Calculate movement, based on event !!!!!!!!!

}
