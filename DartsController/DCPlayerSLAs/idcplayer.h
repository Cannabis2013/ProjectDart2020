#ifndef IDCPLAYER_H
#define IDCPLAYER_H

#include <quuid.h>

namespace DCContext
{
    class IDCPlayer
    {
    public:
        virtual QUuid playerId() const = 0;
        virtual QString playerName() const = 0;
    };
}

#endif
