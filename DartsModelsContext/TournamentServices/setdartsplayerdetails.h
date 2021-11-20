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
        tournamentModel->setPlayerIds(createPlayerIds(playerModels));
        tournamentModel->setPlayerNames(createPlayerNames(playerModels));
    }
private:
    QVector<QUuid> createPlayerIds(const QVector<IModel<QUuid>*> &models) const
    {
        QVector<QUuid> playerIds;
        for (const auto &model : models)
        {
            auto playerModel = dynamic_cast<IPlayerModel*>(model);
            playerIds << playerModel->name();
        }
        return playerIds;
    }
    QVector<QString> createPlayerNames(const QVector<IModel<QUuid>*> &models) const
    {
        QVector<QString> playerNames;
        for (const auto &model : models)
        {
            auto playerModel = dynamic_cast<IPlayerModel*>(model);
            playerNames << playerModel->name();
        }
        return playerNames;
    }
};
#endif // DARTSMODELMANIPULATOR_H
