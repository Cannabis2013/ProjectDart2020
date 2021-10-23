#ifndef SETDARTSPLAYERDETAILS_H
#define SETDARTSPLAYERDETAILS_H

#include "DartsModelsContext/TournamentsSLAs/isettournamentplayerdetails.h"
#include "PlayerModelsContext/DbSLAs/iplayermodel.h"

class SetDartsPlayerDetails : public ISetTournamentPlayerDetails
{
public:
    virtual void setDetails(IModel<QUuid> *model, const QVector<IModel<QUuid>*> &playerModels) const override
    {
        auto tournamentModel = dynamic_cast<ITournament*>(model);
        tournamentModel->setAssignedPlayerIdentities(getPlayerIdsFromModels(playerModels));
        tournamentModel->setAssignedPlayerNames(getPlayerNamesFromModels(playerModels));
    }
private:
    QVector<QUuid> getPlayerIdsFromModels(const QVector<IModel<QUuid>*> &models) const
    {
        QVector<QUuid> playerIds;
        for (const auto &model : models)
        {
            auto playerModel = dynamic_cast<PlayersContext::IPlayerModel*>(model);
            playerIds << playerModel->id();
        }
        return playerIds;
    }
    QVector<QString> getPlayerNamesFromModels(const QVector<IModel<QUuid>*> &models) const
    {
        QVector<QString> playerNames;
        for (const auto &model : models)
        {
            auto playerModel = dynamic_cast<PlayersContext::IPlayerModel*>(model);
            playerNames << playerModel->playerName();
        }
        return playerNames;
    }
};

#endif // DARTSMODELMANIPULATOR_H
