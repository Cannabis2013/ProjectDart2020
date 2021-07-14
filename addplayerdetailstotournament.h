#ifndef ADDPLAYERDETAILSTOTOURNAMENT_H
#define ADDPLAYERDETAILSTOTOURNAMENT_H

#include "iaddplayerdetailstotournament.h"

class AddPlayerDetailsToTournament : public IAddPlayerDetailsToTournament
{
public:
    virtual void add(const ITournament *tournament,
                              const QVector<QUuid> &playerIds,
                              IDartsTournamentDb *dbService = nullptr) const override
    {
        auto nonConstTournament = const_cast<ITournament*>(tournament);
        nonConstTournament->setAssignedPlayerIdentities(playerIds);
        persistInDb(dbService);
    }
    virtual void add(const ITournament *tournament,
                                const QVector<QString> &playerNames,
                                IDartsTournamentDb *dbService = nullptr) const override
    {
        auto nonConstTournament = const_cast<ITournament*>(tournament);
        nonConstTournament->setAssignedPlayerNames(playerNames);
        persistInDb(dbService);
    }
    virtual void add(const ITournament *tournament,
                             const QUuid &winnerId,
                             IDartsTournamentDb *dbService = nullptr) const override
    {
        auto nonConstModel = const_cast<ITournament*>(tournament);
        nonConstModel->setWinnerId(winnerId);
        persistInDb(dbService);
    }
private:
    void persistInDb(IDartsTournamentDb *dbService) const
    {
        if(dbService != nullptr)
            dbService->saveState();
    }
};

#endif // DARTSMODELMANIPULATOR_H
