// custom includes
#include "main.h"
#include "Game/game.h"

int main( int argc, char* args[] )
{
    Game game;
    game.init();
    bool loop = true;
    EventContainer event;
    while(loop)
    {
        event = game.event();
        switch(event.type)
        {
        case SDL_QUIT:
            loop = false;
            break;
        case SDL_KEYDOWN:
            printf( "%c was press\n", event.key);
            break;
        case SDL_KEYUP:
            printf( "%c was released\n", event.key);
            break;
        default:
            break;
        }
        game.update();
    }
	return 0;
}
