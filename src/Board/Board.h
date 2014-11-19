#ifndef BOARD_H
#define BOARD_H
#include "../main.h"

class Board{
public:
    //Constructor: loads string vector map. Converts to a 2D-Array for matrices calculations.
    //Finds and sets playerPositionX and playerPositionY. Finds and sets goal locations.
    Board(vector<string>); //!!!!!! Fill in passed variable with string vector !!!!!!!!!!!!!!
    //Destructor
    ~Board();
    //Renders game board, based on 2d array map, within camera bounds.
    void render();
    //Takes X and Y coordinates, and performs movement and rendering of game board.
    void movement(int xMove, int yMove);
    //Checks for win-condition, checking star tiles against goal tiles
    void checkForWinCondition();


private:
    const int BOARD_WIDTH = 1500; //per pixel
    const int BOARD_HEIGHT = 1530; //per pixel
    const int TILE_WIDTH = 50; //per pixel
    const int TILE_HEIGHT = 85; //per pixel
    const int CAMERA_WIDTH = 12; //per tile
    const int CAMERA_HEIGHT = 7; //per tile
    MatricesLocation player; //Keep track of player position in matrices
    vector<MatricesLocation> goal; //Keep track of goal locations in matrices
    vector<MatricesLocation> star; //Keep track of star locations in matrices

};

#endif // BOARD_H
