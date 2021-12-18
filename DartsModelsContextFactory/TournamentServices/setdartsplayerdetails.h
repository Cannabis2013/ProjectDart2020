#ifndef SETDARTSPLAYERDETAILS_H
#define SETDARTSPLAYERDETAILS_H
#include <qvector.h>
#include <quuid.h>
#include "DbSLAs/iplayer.h"
#include "TournamentsSLAs/isettournamentplayerdetails.h"
#include "TournamentModelsSLAs/idartstournament.h"
class SetDartsPlayerDetails : public ISetTournamentPlayerDetails
{
public:
    virtual void setDetails(IModel<QUuid> *model, const QVector<IPlayer*> &playerModels) const override
    {
        auto tournamentModel = dynamic_cast<IDartsTournament*>(model);
        tournamentModel->setPlayerIds(createPlayerIds(playerModels));
        tournamentModel->setPlayerNames(createPlayerNames(playerModels));
    }
private:
    QVector<QUuid> createPlayerIds(const QVector<IPlayer*> &players) const
    {
        QVector<QUuid> playerIds;
        for (const auto &player : players)
            playerIds << player->id();
        return playerIds;
    }
    QVector<QString> createPlayerNames(const QVector<IPlayer*> &players) const
    {
        QVector<QString> playerNames;
        for (const auto &player : players)
            playerNames << player->name();
        return playerNames;
    }
};
#endif // DARTSMODELMANIPULATOR_H
