#ifndef DARTSTOURNAMENTREPAIR_H
#define DARTSTOURNAMENTREPAIR_H
#include "TournamentsSLAs/itournamentrepair.h"

class QByteArray;
class DartsPlayerServices;
class DartsInputServices;
class DartsServices;
class IDartsTournament;
template<typename T> class IModel;
class DartsModelsServices;
class AbsPlaCtx;
struct DartsPlayer;
class DartsTournamentRepair : public ITournamentRepair<IModel<QUuid>>
{
public:
    typedef QVector<DartsPlayer> Players;
    DartsTournamentRepair(DartsModelsServices *services);
    bool repair(const QUuid &tournamentID) const override;
private:
    Model *getTournament(const QUuid &tournamentID) const;
    Models getInputs(const QUuid &tournamentID) const;
    bool repairTournamentPlayers(IDartsTournament *tournament) const;
    bool repairInputs(const Models &models) const;
    Players toPlayers(const QByteArray &byteArray) const;
    DartsModelsServices *_services;
    DartsServices *_tnmServices;
    DartsInputServices *_iptServices;
    DartsPlayerServices *_plaServices;
    AbsPlaCtx *_plaCtx;
};
#endif // DARTSTOURNAMENTREPAIR_H
