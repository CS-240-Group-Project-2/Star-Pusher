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
    EventContainer newContainer;
    // we have the event variable to play with
    newContainer.setType(this->sdlEvent.type);
    newContainer.setKey(this->sdlEvent.key.keysym.sym);
    printf( "Pressed/Released: %c\n", newContainer.getKey());
    return true;
}

bool EventHandler::handleQuit()
{
    EventContainer newContainer;
    this->container = newContainer;
    this->container.setType(this->sdlEvent.type);
    return true;
}
