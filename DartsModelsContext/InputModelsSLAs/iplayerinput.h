#ifndef ISCORE_H
#define ISCORE_H
#include <DartsModelsContext/ModelSLAs/imodel.h>
class QString;
class QUuid;
class IPlayerInput : public IModel<QUuid>
{
public:
    virtual int hint() const = 0;
    virtual void setHint(const int &hint) = 0;
    virtual QUuid playerId() const = 0;
    virtual void setPlayerId(const QUuid &id) = 0;
    virtual QString playerName() const = 0;
    virtual void setPlayerName(const QString&) = 0;
    virtual QUuid tournamentId() const = 0;
    virtual void setTournamentId(const QUuid&) = 0;
};
#endif // ISCORE_H
