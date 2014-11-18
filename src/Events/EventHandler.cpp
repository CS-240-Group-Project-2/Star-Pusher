#include "EventHandler.h"

EventHandler::EventHandler()
{
}

EventHandler::~EventHandler()
{
}

EventContainer EventHandler::handleAll()
{
    if(SDL_PollEvent(&this->sdlEvent) != 0)
    {
        switch(this->sdlEvent.type)
        {
        case SDL_QUIT:
            this->handleQuit();
            break;
        case SDL_KEYDOWN:
            this->handleKeys();
            break;
        case SDL_KEYUP:
            this->handleKeys();
            break;
        default:
            break;
        }
    }
    return this->container;
}

bool EventHandler::handleKeys()
{
    // we have the event variable to play with
    this->container.type = this->sdlEvent.type;
    this->container.key = this->sdlEvent.key.keysym.sym;
    printf( "%c was released\n", this->container.key);
    return true;
}

bool EventHandler::handleQuit()
{
    this->container.type = this->sdlEvent.type;
    this->container.key = '~';
    return true;
}
