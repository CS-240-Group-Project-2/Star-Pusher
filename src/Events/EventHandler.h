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
    int getType()
    {
        return this->type;
    }
    char getKey()
    {
        return this->key;
    }
    bool setType(int type)
    {
        this->type = type;
        return true;
    }
    bool setKey(char key)
    {
        this->key = key;
        return true;
    }
    int type;
    char key;
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
