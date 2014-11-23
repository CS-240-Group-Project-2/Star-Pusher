#include "Board.h"

//!Constructor
Board::Board(vector<string> newMap, vector<images> imageDatabase){
    //Setup array height and width of map loaded into new Board object.
    int mapHeight = newMap.size();
    int mapWidth = 0;
    for(int i = 0; i < newMap.size() - 1; ++i){
        if(newMap[i].length() > mapWidth){
            mapWidth = newMap[i].length();
        }
    }
    //Create mapArray matrices, according to mapHeight/mapWidth, from newMap vector.
    char mapArray[mapHeight][mapWidth];
    MatricesLocation newStar;
    MatricesLocation newGoal;
    for(int i = 0; i < mapHeight - 1; ++i){
        for(int j = 0; j < mapWidth - 1; ++j){
            //!!!!! Might need to assess strings that are less than mapWidth? !!!!!!
            mapArray[i][j] = {newMap[i].at(j)};
            //Find player position
            if(mapArray[i][j] == '@'){
                player.x = j;
                player.y = i;
            }
            //Find star positions
            if(mapArray[i][j] == '$'){
                newStar.x = j;
                newStar.y = i;
                stars.push_back(newStar);
            }
            //Find goal positions
            if(mapArray[i][j] == '.'){
                newGoal.x = j;
                newGoal.y = i;
                goals.push_back(newGoal);
            }
        }
    }
    //Set score keeping variables
    goalsTotal = goals.size();
    goalsRemaining = goals.size();
    winCondition = false;
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

//!checkForWinCondition
bool Board::checkForWinCondition(){

}
