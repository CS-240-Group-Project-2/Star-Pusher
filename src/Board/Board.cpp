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
    //Delete and clear mapArray
    for(int h = 0; h < mapHeight; ++h){
        delete [] mapArray[h];
    }
    delete [] mapArray;
    mapArray = 0;
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
    //Initialize mapArray matrices, according to mapHeight/mapWidth. In this format: mapArray[mapHeight][mapWidth]
    //! **** DELETE mapArray IN DESTRUCTOR ****
    mapArray = new char*[mapHeight];
    for(int h = 0; h < mapHeight; ++h){
        mapArray[h] = new char[mapWidth];
    }

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
    //Initialize SDL_Rect used to keep track of tile rendering
    SDL_Rect renderRect;
    renderRect.h = TILE_HEIGHT;
    renderRect.w = TILE_WIDTH;
    renderRect.x = 0;
    renderRect.y = 0;

    //Find starting 0,0 x,y position of camera to be rendered
    int cameraX = 0;
    int cameraY = 0;
    //Camera will be within bounds of whole map - no adjustment necessary
    if(player.x >= 5 && player.x <= 23 && player.y >= 3 && player.y <= 14){
        cameraX = player.x - 5;
        cameraY = player.y - 3;
    }
    //Otherwise, adjust camera to not go out of bounds of map
    else if(player.x < 5){
        cameraX = 0;
    }
    else if(player.x > 23){
        cameraX = 29;
    }
    else if(player.y < 3){
        cameraY = 0;
    }
    else if(player.y > 14){
        cameraY = 17;
    }

    //Set starting position to renderRect
    renderRect.x = cameraX;
    renderRect.y = cameraY;

    //Clear screen
    SDL_RenderClear(gRenderer);

    //Render matrices to screen
    for(int i = cameraY; i <= 7; ++i){
        for(int j = cameraX; j <= 12; ++j){
            //!rendering template: SDL_RenderCopy( gRenderer, gTexture, sourceRect, destinationRect );

            //Determine which textures we're needing to print
            //! CONTINUE HERE! <------------------------------------------------------------------------------------------------------------

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
