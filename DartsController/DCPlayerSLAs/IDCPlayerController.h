#ifndef IDCPLAYERCONTROLLER_H
#define IDCPLAYERCONTROLLER_H
#include <quuid.h>
#include <qvector.h>
#include "DartsController/DCPlayerServices/dcplayer.h"
class IDCPlayerController
{
public:
    struct PlayerObject
    {
        QUuid playerId;
        bool in = false;
    };
    virtual void appendPlayerId(const QVector<DCPlayer> &playerIds) = 0;
    virtual bool isIn(const QUuid &playerId) const = 0;
    virtual bool updatePlayerStatus(const QUuid &playerId, const bool &status) = 0;
    virtual int count() const = 0;
    virtual void reset() = 0;
};
#endif // IDCPLAYERCONTROLLER_H
