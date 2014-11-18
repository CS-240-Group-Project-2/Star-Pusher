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
        if(event.type == SDL_QUIT)
            loop = false;
        game.update();
    }
	return 0;
}
