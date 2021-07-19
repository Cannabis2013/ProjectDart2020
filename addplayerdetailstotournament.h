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
    virtual void add(const ITournament *tournament, const QVector<const DartsModelsContext::IPlayerModel *> &playerModels, IDartsTournamentDb *dbService) const override
    {
        auto nonConstModel = const_cast<ITournament*>(tournament);
        nonConstModel->setAssignedPlayerIdentities(getPlayerIdsFromModels(playerModels));
        nonConstModel->setAssignedPlayerNames(getPlayerNamesFromModels(playerModels));
        dbService->saveState();
    }
private:
    void persistInDb(IDartsTournamentDb *dbService) const
    {
        if(dbService != nullptr)
            dbService->saveState();
    }
    QVector<QUuid> getPlayerIdsFromModels(const QVector<const DartsModelsContext::IPlayerModel*> &playerModels) const
    {
        QVector<QUuid> playerIds;
        for (const auto &playerModel : playerModels)
            playerIds << playerModel->id();
        return playerIds;
    }
    QVector<QString> getPlayerNamesFromModels(const QVector<const DartsModelsContext::IPlayerModel*> &playerModels) const
    {
        QVector<QString> playerNames;
        for (const auto &playerModel : playerModels)
            playerNames << playerModel->playerName();
        return playerNames;
    }
};

#endif // DARTSMODELMANIPULATOR_H
