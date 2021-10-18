#ifndef IDCPLAYERAPPROVAL_H
#define IDCPLAYERAPPROVAL_H
#include <quuid.h>
#include <qvector.h>
#include "DartsController/DCPlayerServices/dcplayer.h"
class IDCPlayerApproval
{
public:
    struct PlayerObject
    {
        QUuid playerId;
        bool in = false;
    };
    virtual void appendPlayerId(const QVector<DCPlayer> &playerIds) = 0;
    virtual bool isAllowedEntrance(const QUuid &playerId) = 0;
    virtual void playerIsIn(const QUuid &playerId) = 0;
    virtual void reset() = 0;
};
#endif // IDCPLAYERAPPROVAL_H
