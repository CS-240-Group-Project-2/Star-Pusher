#ifndef EVENTHANDLER_H_INCLUDED
#define EVENTHANDLER_H_INCLUDED

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

#endif // EVENTHANDLER_H_INCLUDED
