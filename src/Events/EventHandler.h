#ifndef EVENTHANDLER_H_INCLUDED
#define EVENTHANDLER_H_INCLUDED

#include "../main.h"
/*
 * Event Handling
 * [ ]
 */

struct EventContainer
{
public:
    int type;
    char key;
    EventContainer()
    {
        this->type = 0;
        this->key  = ' ';
    }
};

class EventHandler
{
public:
    EventHandler();
    ~EventHandler();
    EventContainer handleAll();
    bool handleKeys();
    bool handleQuit();
private:
    EventContainer container;
    SDL_Event sdlEvent;
};

#endif // EVENTHANDLER_H_INCLUDED
