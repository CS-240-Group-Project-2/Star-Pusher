// custom includes
#include "main.h"
#include "Game/game.h"

int main( int argc, char* args[] )
{
    Game game;
    game.init();
    game.createBoard();
    bool loop = true;
    EventContainer event;
    game.update();
    while(loop)
    {
        event = game.event();
        if(event.getType() == SDL_QUIT){
            loop = false;
        }
        else if(event.getType() == SDLK_w){
            cout << "test!" << endl;
            game.newBoard.moveUp();
            game.update();
        }

    }
	return 0;
}
