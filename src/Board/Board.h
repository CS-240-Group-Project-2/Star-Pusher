#ifndef BOARD_H
#define BOARD_H
#include "../main.h"

class Board{
public:
    //Variables from game class
    struct images
    {
        string name; // try to make them caps
        string file;
    };
    //Constructor: loads string vector map. Converts to a 2D-Array for matrices calculations.
    //Finds and sets player location. Finds and sets goal and star locations.
    Board(vector<string>, vector<images>, SDL_Renderer*);

    //Destructor
    ~Board();

    //Creates 2-dimensional char array matrices with passed vector of strings
    void createMatrices(vector<string>);

    //Loads texture from string path and returns the texture
    SDL_Texture* loadTexture(string);

    //Renders game board, based on 2d array map, within camera bounds.
    void render();

    //Takes X and Y coordinates, and performs movement and rendering of game board.
    void movement(int xMove, int yMove); //!!!!! May not use this -> may opt for seperate movement functions !!!!!

    //!!!! May opt to use these: !!!!!!
    //Movement functions: Run these according to event handler input for game movement controls.
    //Note: These functions will automatically check for walls and other movement-blocking factors.
    SDL_Surface moveUp();
    SDL_Surface moveDown();
    SDL_Surface moveLeft();
    SDL_Surface moveRight();

    //Checks for win-condition, returning true if game is won.
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

    //! The matrices to be used for the map
    char** mapArray;

    //! Non-preset dimensions
    int mapHeight;
    int mapWidth;


    //! Renderer that will be passed when object is created
    SDL_Renderer* gRenderer;

    //! MatricesLocations variables
    MatricesLocation player; //Keep track of player position in matrices
    vector<MatricesLocation> goals; //Keep track of goal locations in matrices
    vector<MatricesLocation> stars; //Keep track of star locations in matrices

    //! Score tracking variables
    bool winCondition;
    int goalsTotal;
    int goalsRemaining;

    //! Functions
    vector<images> imageDatabase;
    int searchImages(string);
};

#endif // BOARD_H
