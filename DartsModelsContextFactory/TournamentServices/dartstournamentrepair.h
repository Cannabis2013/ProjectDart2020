#ifndef DARTSTOURNAMENTREPAIR_H
#define DARTSTOURNAMENTREPAIR_H
#include "TournamentsSLAs/itournamentrepair.h"

#include <qvector.h>

class QString;
class QByteArray;
class TournamentServices;
class IDartsTournament;
template<typename T> class IModel;
class DartsModelsServices;
struct DartsPlayer;

class DartsTournamentRepair : public ITournamentRepair<IModel<QUuid>>
{
public:
    typedef QVector<DartsPlayer> Players;
    bool repair(const QUuid &tournamentID, DartsModelsServices *services) override;
private:
    struct PlayerDetails{
        QVector<QUuid> IDs;
        QVector<QString> names;
    };
    PlayerDetails getPlayerDetails(const Players &players);
    IDartsTournament *getTournament(const QUuid &tournamentID, DartsModelsServices *services);
    Models getInputs(const QUuid &tournamentID, DartsModelsServices *services);
    bool repairTournamentPlayers(IDartsTournament *tournament, DartsModelsServices *services);
    bool repairInputs(const Models &models, DartsModelsServices *services);
    Players toPlayers(const QByteArray &byteArray, DartsModelsServices *services);
    bool persistChanges(DartsModelsServices *services);
};
#endif // DARTSTOURNAMENTREPAIR_H
