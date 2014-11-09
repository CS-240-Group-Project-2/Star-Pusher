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
    SDL,
    MEDIA,
    AMOUNT // this HAS to be last
};

// this class will handle SDL2 stuff
class Game
{
public:
    Game();
    bool init();
    bool loadMedia();
    bool update();
    EventContainer event();
    ~Game();
private:
    //Screen dimension constants
    static const int SCREEN_WIDTH = 640;
    static const int SCREEN_HEIGHT = 480;

    //SDL Info
    SDL_Window* gWindow;
    SDL_Surface* gScreenSurface;
    SDL_Surface* gHelloWorld;
    SDL_Event sdlEvent;

    // others
    vector<bool> startupStatus;
    vector<images> imageDatabase;

    // functions
    bool file_exists(string);
    int searchImages(string);
};

#endif // GAME_H_INCLUDED
