#ifndef DARTSSETWINNER_H
#define DARTSSETWINNER_H
#include "TournamentsSLAs/IDartsSetWinner.h"
;
class DartsPlayer;
class IDartsTournament;
template<typename T>
class IModel;
class QUuid;
class DartsSetWinner : public IDartsSetWinner<IModel<QUuid>>
{
public:;
    void setWinner(const QUuid &tournamentId, const QString &name, DartsModelsServices *services) const override;
private:
    IDartsTournament *getTournament(const QUuid &tournamentId, DartsModelsServices *services) const;
    DartsPlayer getPlayer(const QString &name, DartsModelsServices *services) const;
};

#endif // DARTSSETWINNER_H
