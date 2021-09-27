#ifndef ISCORE_H
#define ISCORE_H

#include "ModelsContext/MCModelsSLAs/imodel.h"
#include <quuid.h>

class IPlayerInput : public IModel<QUuid>
{
public:
    virtual int hint() const = 0;
    virtual IPlayerInput* setHint(const int &hint) = 0;
    virtual QUuid playerId() const = 0;
    virtual IPlayerInput* setPlayerId(const QUuid &id) = 0;
    virtual QString playerName() const = 0;
    virtual IPlayerInput* setPlayerName(const QString&) = 0;
    virtual QUuid tournamentId() const = 0;
    virtual IPlayerInput* setTournamentId(const QUuid&) = 0;
};


#endif // ISCORE_H