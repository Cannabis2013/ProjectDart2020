#ifndef CreatePlayersContext_H
#define CreatePlayersContext_H

#include <qobject.h>

class AbstractPlayerContext;

class CreatePlayersContext
{
public:
    static AbstractPlayerContext *localJson();
};
#endif // LOCALPLAYERSCONTEXT_H
