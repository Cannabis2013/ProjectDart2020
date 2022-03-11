#ifndef DARTSSETWINNER_H
#define DARTSSETWINNER_H

#include "Routines/IDartsSetWinner.h"

class DartsPlayer;
class IDartsTournament;
template<typename T>
class IModel;
class QUuid;
class DartsSetWinner : public IDartsSetWinner<IModel<QUuid>>
{
public:;
    bool setWinner(const QUuid &tournamentId, const QString &name, DartsModelsServices *services) override;
private:
    IDartsTournament *getTournament(const QUuid &tournamentId, DartsModelsServices *services) const;
    DartsPlayer getPlayer(const QString &name, DartsModelsServices *services) const;
    void updateTournament(IDartsTournament *tournament, const DartsPlayer &player);
    bool persistChanges(DartsModelsServices *services);
};

#endif // DARTSSETWINNER_H
