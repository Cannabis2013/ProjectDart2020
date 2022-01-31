#ifndef DARTSSETWINNER_H
#define DARTSSETWINNER_H
#include "TournamentsSLAs/IDartsSetWinner.h"

class DartsServices;
class DartsPlayerServices;
class DartsPlayer;
class IDartsTournament;
class DMCServices;
template<typename T>
class IModel;
class QUuid;
class DartsSetWinner : public IDartsSetWinner<IModel<QUuid>>
{
public:;
    DartsSetWinner(DMCServices *services);
    void setWinner(const QUuid &tournamentId, const QString &name) const override;
private:
    IDartsTournament *getTournament(const QUuid &tournamentId) const;
    DartsPlayer getPlayer(const QString &name) const;
    DMCServices *_services;
    DartsServices *_tnmServices;
    DartsPlayerServices *_plaServices;
};

#endif // DARTSSETWINNER_H
