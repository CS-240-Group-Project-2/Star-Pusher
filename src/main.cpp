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
        else{
            //cout << event.getKey() << endl;
            //cout << event.getType() << endl;
            switch(event.getKey()){

            case ('w'):
            case ('W'):
                cout << "test" << endl;
                game.newBoard.moveUp();
                game.update();
                break;
            }
        }
    }
	return 0;
}
