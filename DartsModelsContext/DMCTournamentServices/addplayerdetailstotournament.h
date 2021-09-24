#ifndef ADDPLAYERDETAILSTOTOURNAMENT_H
#define ADDPLAYERDETAILSTOTOURNAMENT_H

#include "DartsModelsContext/DMCTournamentSLAs/iaddplayerdetailstotournament.h"

class AddPlayerDetailsToTournament : public IAddPlayerDetailsToTournament
{
public:
    virtual void add(const IModel<QUuid> *model,
                     const QVector<QUuid> &playerIds,
                     IModelsDbContext *dbService = nullptr) const override
    {
        auto tournamentModel = dynamic_cast<const ITournament*>(model);
        auto nonConstTournament = const_cast<ITournament*>(tournamentModel);
        nonConstTournament->setAssignedPlayerIdentities(playerIds);
        persistInDb(dbService);
    }
    virtual void add(const IModel<QUuid> *model,
                     const QVector<QString> &playerNames,
                     IModelsDbContext *dbService = nullptr) const override
    {
        auto tournamentModel = dynamic_cast<const ITournament*>(model);
        auto nonConstTournament = const_cast<ITournament*>(tournamentModel);
        nonConstTournament->setAssignedPlayerNames(playerNames);
        persistInDb(dbService);
    }
    virtual void add(const IModel<QUuid> *model,
                     const QUuid &winnerId, const QString &winnerName,
                     IModelsDbContext *dbService = nullptr) const override
    {
        auto tournamentModel = dynamic_cast<const ITournament*>(model);
        auto nonConstTournament = const_cast<ITournament*>(tournamentModel);
        nonConstTournament->setWinnerId(winnerId);
        nonConstTournament->setWinnerName(winnerName);
        persistInDb(dbService);
    }

    virtual void add(const IModel<QUuid> *model,
                     const QVector<const IModel<QUuid>*> &playerModels,
                     IModelsDbContext *dbService) const override
    {
        auto tournamentModel = dynamic_cast<const ITournament*>(model);
        auto nonConstTournament = const_cast<ITournament*>(tournamentModel);
        nonConstTournament->setAssignedPlayerIdentities(getPlayerIdsFromModels(playerModels));
        nonConstTournament->setAssignedPlayerNames(getPlayerNamesFromModels(playerModels));
        dbService->saveState();
    }
private:
    void persistInDb(IModelsDbContext *dbService) const
    {
        if(dbService != nullptr)
            dbService->saveState();
    }
    QVector<QUuid> getPlayerIdsFromModels(const QVector<const IModel<QUuid>*> &models) const
    {
        QVector<QUuid> playerIds;
        for (const auto &model : models)
        {
            auto playerModel = dynamic_cast<const PlayersContext::IPlayerModel*>(model);
            playerIds << playerModel->id();
        }
        return playerIds;
    }
    QVector<QString> getPlayerNamesFromModels(const QVector<const IModel<QUuid>*> &models) const
    {
        QVector<QString> playerNames;
        for (const auto &model : models)
        {
            auto playerModel = dynamic_cast<const PlayersContext::IPlayerModel*>(model);
            playerNames << playerModel->playerName();
        }
        return playerNames;
    }
};

#endif // DARTSMODELMANIPULATOR_H
