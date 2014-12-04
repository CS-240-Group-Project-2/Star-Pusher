#include "Board.h"

//!Constructor
Board::Board(vector<string> newMap, vector<images> imageDatabase_Passed, SDL_Renderer* gRenderer_Passed){
    //Create matrices for use in tiling
    createMatrices(newMap);
    //Apply imageDatabase_Passed and gRenderer_Passed to the Board object's imageDatabase and gRenderer
    imageDatabase = imageDatabase_Passed;
    gRenderer = gRenderer_Passed;
    //Set score keeping variables
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
    //Delete and clear gRenderer
    SDL_DestroyRenderer(gRenderer);
    gRenderer = NULL;
    //Delete and clear newTexture
    SDL_DestroyTexture(newTexture);
    newTexture = NULL;
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
            if(mapArray[i][j] == '@' || mapArray[i][j] == '+'){
                player.x = j;
                player.y = i;
            }
            //Find goal positions
            if(mapArray[i][j] == '.' || mapArray[i][j] == '*'){
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
    newTexture = NULL;

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
SDL_Renderer* Board::render(){
    //Initialize SDL_Rect used to keep track of tile rendering
    SDL_Rect renderRect;
    renderRect.h = TILE_HEIGHT;
    renderRect.w = TILE_WIDTH;
    renderRect.x = 0;
    renderRect.y = 0;

    //Find starting 0,0 x,y position of camera to be rendered
    int cameraX = 0;
    int cameraY = 0;
    //If camera will be within bounds of whole map - no adjustment necessary
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

    //Set starting position of camera to renderRect
    renderRect.x = (cameraX * 50);
    renderRect.y = (cameraY * 85);

    //Clear screen
    SDL_RenderClear(gRenderer);

    //Render matrices to screen
    for(int i = cameraY; i <= (cameraY + 7); ++i){
        for(int j = cameraX; j <= (cameraX + 12); ++j){
            /*
            ;   Rendering template: SDL_RenderCopy( gRenderer, gTexture, sourceRect, destinationRect );
            ;
            ;   Texture format from matrices is as follows:
            ;   @ - The starting position of the player.
            ;   $ - The starting position for a pushable star.
            ;   . - A goal where a star needs to be pushed.
            ;   + - Player & goal
            ;   * - Star & goal
            ;  (space) - an empty open space.
            ;   # - A wall.
            */
            //!Determine which texture we're going to print for the current matrices tile
            if(mapArray[i][j] == '@'){ //Player
                SDL_RenderCopy(gRenderer, loadTexture(imageDatabase[searchImages("FLOOR")].file), NULL, &renderRect);
                SDL_RenderCopy(gRenderer, loadTexture(imageDatabase[searchImages("CHARBOY")].file), NULL, &renderRect);
            }
            else if(mapArray[i][j] == '$'){ //Pushable Star
                SDL_RenderCopy(gRenderer, loadTexture(imageDatabase[searchImages("FLOOR")].file), NULL, &renderRect);
                SDL_RenderCopy(gRenderer, loadTexture(imageDatabase[searchImages("STAR")].file), NULL, &renderRect);
            }
            else if(mapArray[i][j] == '.'){ //A goal
                SDL_RenderCopy(gRenderer, loadTexture(imageDatabase[searchImages("FLOOR")].file), NULL, &renderRect);
                SDL_RenderCopy(gRenderer, loadTexture(imageDatabase[searchImages("GOAL")].file), NULL, &renderRect);
            }
            else if(mapArray[i][j] == '+'){ //Player & goal
                SDL_RenderCopy(gRenderer, loadTexture(imageDatabase[searchImages("FLOOR")].file), NULL, &renderRect);
                SDL_RenderCopy(gRenderer, loadTexture(imageDatabase[searchImages("GOAL")].file), NULL, &renderRect);
                SDL_RenderCopy(gRenderer, loadTexture(imageDatabase[searchImages("CHARBOY")].file), NULL, &renderRect);
            }
            else if(mapArray[i][j] == '*'){ //Star & goal
                SDL_RenderCopy(gRenderer, loadTexture(imageDatabase[searchImages("FLOOR")].file), NULL, &renderRect);
                SDL_RenderCopy(gRenderer, loadTexture(imageDatabase[searchImages("GOAL_COMPLETED")].file), NULL, &renderRect);
                SDL_RenderCopy(gRenderer, loadTexture(imageDatabase[searchImages("STAR")].file), NULL, &renderRect);
            }
            else if(mapArray[i][j] == ' '){ //Floor
                SDL_RenderCopy(gRenderer, loadTexture(imageDatabase[searchImages("FLOOR")].file), NULL, &renderRect);
            }
            else if(mapArray[i][j] == '#'){ //Wall
                SDL_RenderCopy(gRenderer, loadTexture(imageDatabase[searchImages("WALL")].file), NULL, &renderRect);
            }
            //!Increment renderRect to move to next position to print to on screen
            //If we've reached the end of the row, reset renderRect X & increment the Y value to go to new row in matrices
            if(j == 12){
                renderRect.x = (cameraX * 50);
                renderRect.y = (renderRect.y + 85);
            }
            //Otherwise, increment X value to move to next column in matrices
            else{
                renderRect.x = (renderRect.x + 50);
            }
        }
    }
    return gRenderer;
}

//! Movement functions: check if movement is possible, and adjust mapArray and player position accordingly
void Board::moveUp(){
    if(mapArray[player.y - 1][player.x] == ' '){        //! Floor tile - free to move
        MatricesLocation tempLocation;                  // Set MatricesLocation for next tile
        tempLocation.y = player.y - 1;
        tempLocation.x = player.x;
        moveFloor(tempLocation);                        // Adjust mapArray and player position
    }
    else if(mapArray[player.y - 1][player.x] == '.'){   //! Goal tile - free to move
        MatricesLocation tempLocation;                  // Set MatricesLocation for next tile
        tempLocation.y = player.y - 1;
        tempLocation.x = player.x;
        moveFloor(tempLocation);                        // Adjust mapArray and player position
    }
    else if(mapArray[player.y - 1][player.x] == '$'){   //! Star tile - move if next tile is a movable position
        MatricesLocation tempLocation1, tempLocation2;  // Set MatricesLocation for next tiles
        tempLocation1.y = player.y - 1;
        tempLocation1.x = player.x;
        tempLocation2.y = player.y - 2;
        tempLocation2.x = player.x;
        moveStar(tempLocation1, tempLocation2);         //Adjust mapArray & player position (if possible)
    }
}

void Board::moveDown(){
    if(mapArray[player.y + 1][player.x] == ' '){        //! Floor tile - free to move
        MatricesLocation tempLocation;                  // Set MatricesLocation for next tile
        tempLocation.y = player.y + 1;
        tempLocation.x = player.x;
        moveFloor(tempLocation);                        // Adjust mapArray and player position
    }
    else if(mapArray[player.y + 1][player.x] == '.'){   //! Goal tile - free to move
        MatricesLocation tempLocation;                  // Set MatricesLocation for next tile
        tempLocation.y = player.y + 1;
        tempLocation.x = player.x;
        moveFloor(tempLocation);                        // Adjust mapArray and player position
    }
    else if(mapArray[player.y + 1][player.x] == '$'){   //! Star tile - move if next tile is a movable position
        MatricesLocation tempLocation1, tempLocation2;  // Set MatricesLocation for next tiles
        tempLocation1.y = player.y + 1;
        tempLocation1.x = player.x;
        tempLocation2.y = player.y + 2;
        tempLocation2.x = player.x;
        moveStar(tempLocation1, tempLocation2);         //Adjust mapArray & player position (if possible)
    }
}

void Board::moveLeft(){
    if(mapArray[player.y][player.x - 1] == ' '){        //! Floor tile - free to move
        MatricesLocation tempLocation;                  // Set MatricesLocation for next tile
        tempLocation.y = player.y;
        tempLocation.x = player.x - 1;
        moveFloor(tempLocation);                        // Adjust mapArray and player position
    }
    else if(mapArray[player.y][player.x - 1] == '.'){   //! Goal tile - free to move
        MatricesLocation tempLocation;                  // Set MatricesLocation for next tile
        tempLocation.y = player.y;
        tempLocation.x = player.x - 1;
        moveFloor(tempLocation);                        // Adjust mapArray and player position
    }
    else if(mapArray[player.y][player.x - 1] == '$'){   //! Star tile - move if next tile is a movable position
        MatricesLocation tempLocation1, tempLocation2;  // Set MatricesLocation for next tiles
        tempLocation1.y = player.y;
        tempLocation1.x = player.x - 1;
        tempLocation2.y = player.y;
        tempLocation2.x = player.x - 2;
        moveStar(tempLocation1, tempLocation2);         //Adjust mapArray & player position (if possible)
    }
}

void Board::moveRight(){
    if(mapArray[player.y][player.x + 1] == ' '){        //! Floor tile - free to move
        MatricesLocation tempLocation;                  // Set MatricesLocation for next tile
        tempLocation.y = player.y;
        tempLocation.x = player.x + 1;
        moveFloor(tempLocation);                        // Adjust mapArray and player position
    }
    else if(mapArray[player.y][player.x + 1] == '.'){   //! Goal tile - free to move
        MatricesLocation tempLocation;                  // Set MatricesLocation for next tile
        tempLocation.y = player.y;
        tempLocation.x = player.x + 1;
        moveFloor(tempLocation);                        // Adjust mapArray and player position
    }
    else if(mapArray[player.y][player.x + 1] == '$'){   //! Star tile - move if next tile is a movable position
        MatricesLocation tempLocation1, tempLocation2;  // Set MatricesLocation for next tiles
        tempLocation1.y = player.y;
        tempLocation1.x = player.x + 1;
        tempLocation2.y = player.y;
        tempLocation2.x = player.x + 2;
        moveStar(tempLocation1, tempLocation2);         //Adjust mapArray & player position (if possible)
    }
}

//! mapArray checking and adjustment + player movement functions
// Move to floor tile
void Board::moveFloor(MatricesLocation& nextTile){
    if(mapArray[player.y][player.x] == '@'){            //If player was standing on floor
            mapArray[player.y][player.x] = ' ';
            mapArray[nextTile.y][nextTile.x] = '@';
        }
    else if(mapArray[player.y][player.x] == '+'){       //If player was standing on goal
        mapArray[player.y][player.x] = '.';
        mapArray[nextTile.y][nextTile.x] = '@';
    }
    player.y = nextTile.y;                              //Adjust player position
    player.x = nextTile.x;
}

// Move to goal tile
void Board::moveGoal(MatricesLocation& nextTile){
    if(mapArray[player.y][player.x] == '@'){            //If player was standing on floor
            mapArray[player.y][player.x] = ' ';
            mapArray[nextTile.y][nextTile.x] = '+';
    }
    else if(mapArray[player.y][player.x] == '+'){       //If player was standing on goal
        mapArray[player.y][player.x] = '.';
        mapArray[nextTile.y][nextTile.x] = '+';
    }
    player.y = nextTile.y;                              //Adjust player position
    player.x = nextTile.x;
}

// Move star tile, if possible
void Board::moveStar(MatricesLocation& firstTile, MatricesLocation& secondTile){
    if(mapArray[secondTile.y][secondTile.x] == ' '){    //!Floor tile - free to move
        mapArray[secondTile.y][secondTile.x] = '$';     //Push star
        if(mapArray[firstTile.y][firstTile.x] == '$'){  //If star was on floor
            moveFloor(firstTile);                       //Move player
        }
        else{                                           //If star was on goal
            moveGoal(firstTile);                        //Move player
        }
    }
    if(mapArray[secondTile.y][secondTile.x] == '.'){    //!Goal tile - free to move
        mapArray[secondTile.y][secondTile.x] = '*';     //Push star
        if(mapArray[firstTile.y][firstTile.x] == '$'){  //If star was on floor
            moveFloor(firstTile);                       //Move player
        }
        else{                                           //If star was on goal
            moveGoal(firstTile);                        //Move player
        }
    }
}

//! checkForWinCondition
bool Board::checkForWinCondition(){
    for(int i = 0; i < goals.size() - 1; ++i){
        if(mapArray[goals[i].y][goals[i].x] == '.'){    //If an empty goal is found
            winCondition = false;                       //Game has not been won yet, return false
            return winCondition;
        }
    }
    winCondition = true;                                //If no empty goals were found
    return winCondition;                                //Game has been won, return true
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
