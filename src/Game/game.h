#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#define nullptr 0

#include "../main.h"

struct images
{
    string name; // try to make them caps
    string file;
};

enum STARTUP
{
    SDL = 0,
    MEDIA = 1,
    IMAGE = 2,
    AMOUNT = 3 // this HAS to be last
};

enum SURFACES
{
    SCREEN,
    STRETCHED,
    USABLE,
    OPTIMIZED,
    LOADED,
    SURFACEAMOUNT
};

struct Level
{
public:
    vector<string> map;
};

// this class will handle SDL2 stuff
class Game
{
public:
    Game();
    bool init();
    bool loadMedia(); // can load levels
    bool update();
    EventContainer event();
    SDL_Surface* loadSurface(string);
    ~Game();
private:
    //Screen dimension constants
    static const int SCREEN_WIDTH = 800;
    static const int SCREEN_HEIGHT = 600;

    //SDL Info
    SDL_Window* gWindow;
    SDL_Surface* gScreenSurface;
    SDL_Surface* gStretchedSurface;

    // others
    vector<bool> startupStatus;
    vector<images> imageDatabase;
    vector<SDL_Surface*> surfaceController;
    vector<Level> levelTest;

    // core features
    EventHandler eventHandler;

    // functions
    bool file_exists(string);
    int searchImages(string);
};

#endif // GAME_H_INCLUDED
