#ifndef CORE_H_INCLUDED
#define CORE_H_INCLUDED
#define nullptr 0

#include "../main.h"

struct images
{
    string name; // try to make them caps
    string file;
};

// this class will handle SDL2 stuff
class Core
{
public:
    Core();
    bool init();
    bool loadMedia();
    bool update();
    ~Core();
private:
    //Screen dimension constants
    static const int SCREEN_WIDTH = 640;
    static const int SCREEN_HEIGHT = 480;

    //SDL Info
    SDL_Window* gWindow;
    SDL_Surface* gScreenSurface;
    SDL_Surface* gHelloWorld;
    SDL_Event event;

    // others
    bool setupSuccess;
    vector<images> imageDatabase;

    // functions
    bool file_exists(string);
    int searchImages(string);
};

#endif // CORE_H_INCLUDED
