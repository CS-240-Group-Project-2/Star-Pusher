#include "Board.h"

//!Constructor
Board::Board(vector<string> newMap, vector<images> imageDatabase_Passed, SDL_Renderer* gRenderer_Passed){
    //Create matrices for use in tiling
    createMatrices(newMap);
    //Apply imageDatabase_Passed and gRenderer_Passed to the Board object's imageDatabase and gRenderer
    imageDatabase = imageDatabase_Passed;
    gRenderer = gRenderer_Passed;
    //Set score keeping variables
    goalsTotal = goals.size();
    goalsRemaining = goals.size();
    winCondition = false;
}

//!Destructor
Board::~Board(){

}

//Called from constructor: creates 2-dimensional array matrices for tiling manipulation
void Board::createMatrices(vector<string> newMap){
    //Setup array height and width of map loaded into new Board object.
    mapHeight = newMap.size();
    mapWidth = 0;
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
}

//! loadTexture
SDL_Texture* Board::loadTexture( std::string path )
{
    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
        if( newTexture == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }

        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
    }
    //Return our newly loaded texture.
    return newTexture;
}

//! render
void Board::render(){
    //!!!!!!!! Render the current 2d array        !!!!!!!!!
    //SDL_Rect used to keep track of tile rendering, starting from player position
    SDL_Rect renderRect;
    renderRect.h = TILE_HEIGHT;
    renderRect.w = TILE_WIDTH;
    renderRect.x = player.x;
    renderRect.y = player.y;

    //Clear screen
    SDL_RenderClear(gRenderer);

    //Render matrices to screen
    for(int i = 0; i < CAMERA_HEIGHT - 1; ++i){
        for(int j = 0; j < CAMERA_WIDTH - 1; ++j){
            //!!!!!!!!!!!! continue here !!!!!!!!!!!!!!  <----------------------------------------------
        }
    }
}

//! movement
void Board::movement(int x, int y){
    //!!!!!!!! Calculate movement, based on event !!!!!!!!!

}

//! checkForWinCondition
bool Board::checkForWinCondition(){

}

//! searchImages function from game class used with imageDatabase
int Board::searchImages(string fileName)
{
    if(imageDatabase.size() > 0)
    {
        int record = 0;
        for(int i = 0;i<(int)imageDatabase.size();++i)
        {
            if(imageDatabase[i].name == fileName)
            {
                record = i;
                break;
            }
            cout << imageDatabase[i].name << ":" << fileName << endl;
        }
        return record;
    }
    return -1;
}
