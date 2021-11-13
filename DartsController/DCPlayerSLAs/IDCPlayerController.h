#ifndef IDCPLAYERCONTROLLER_H
#define IDCPLAYERCONTROLLER_H
#include <quuid.h>
#include <qvector.h>
#include "PlayerModelsContext/DbSLAs/iplayermodel.h"
class IDCPlayerController
{
public:
    struct PlayerObject
    {
        QUuid playerId;
        bool in = false;
    };
    typedef IModel<QUuid> Player;
    typedef QVector<Player*> Players;
    virtual void set(const Players &playerIds) = 0;
    virtual bool status(const QUuid &playerId) const = 0;
    virtual bool updateStatus(const QUuid &playerId, const bool &status) = 0;
    virtual int count() const = 0;
    virtual void reset() = 0;
};
#endif // IDCPLAYERCONTROLLER_H
