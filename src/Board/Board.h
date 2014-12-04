#ifndef BOARD_H
#define BOARD_H
#include "../main.h"
//#include "../game/game.h"



//Variables from game class
struct images
{
    string name; // try to make them caps
    string file;
};

class Board{
public:
    //!Constructor: loads string vector map. Converts to a 2D-Array for matrices tiling.
    //!Finds and sets player location. Finds and sets goal locations.
    Board();

    void createBoard(vector<string>, vector<images>, SDL_Renderer*);

    //!Destructor
    ~Board();

    //Creates 2-dimensional char array matrices with passed vector of strings
    void createMatrices(vector<string>);
    void setImages(vector<images>&);

    //Loads texture from string path and returns the texture
    SDL_Texture* loadTexture(string);

    //!Renders game board, based on 2d array map, within camera bounds.
    SDL_Renderer* render();

    //!Movement functions: Run these according to event handler input for game movement controls.
    //Note: These functions will automatically check for walls and other movement-blocking factors.
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    //Functions used within above movement functions to perform player/star movement and mapArray adjustment
    void moveFloor(MatricesLocation&);
    void moveGoal(MatricesLocation&);
    void moveStar(MatricesLocation&, MatricesLocation&);

    //!Checks for win-condition, returning true if game is won.
    bool checkForWinCondition();

private:
    //! Preset dimensions
    const int BOARD_WIDTH = 1500; //per pixel - Total of 30 tiles wide
    const int BOARD_HEIGHT = 1530; //per pixel - Total of 18 tiles high
    const int TILE_WIDTH = 50; //per pixel
    const int TILE_HEIGHT = 85; //per pixel
    const int CAMERA_WIDTH = 12; //per tile
    const int CAMERA_HEIGHT = 7; //per tile
    const int CAMERA_BOUNDS_WIDTH = 600; //per pixel
    const int CAMERA_BOUNDS_HEIGHT = 595; //per pixel

    //! Non-preset dimensions
    int mapHeight;
    int mapWidth;

    //! The matrices to be used for the map
    char** mapArray;

    //! Renderer that will be passed when object is created
    SDL_Renderer* gRenderer;

    //! SDL_Texture that will be used with loadTexture function
    SDL_Texture* newTexture;

    //! MatricesLocations variables
    MatricesLocation player; //Keep track of player position in matrices
    vector<MatricesLocation> goals; //Keep track of goal locations in matrices

    //! Score tracking variables
    bool winCondition;

    //! Functions
    vector<images> imageDatabase;
    int searchImages(string);
};

#endif // BOARD_H
