#ifndef DARTSMODELMANIPULATOR_H
#define DARTSMODELMANIPULATOR_H

#include "idartsmodelmanipulator.h"

class DartsModelManipulator : public IDartsModelManipulator
{
public:
    virtual void addPlayerIds(const ITournament *tournament,
                              const QVector<QUuid> &playerIds,
                              IDartsTournamentDb *dbService = nullptr) const override
    {
        auto nonConstTournament = const_cast<ITournament*>(tournament);
        nonConstTournament->setAssignedPlayerIdentities(playerIds);
        persistInDb(dbService);
    }
    virtual void addPlayerNames(const ITournament *tournament,
                                const QVector<QString> &playerNames,
                                IDartsTournamentDb *dbService = nullptr) const override
    {
        auto nonConstTournament = const_cast<ITournament*>(tournament);
        nonConstTournament->setAssignedPlayerNames(playerNames);
        persistInDb(dbService);
    }
    virtual void setWinnerId(const ITournament *tournament,
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
