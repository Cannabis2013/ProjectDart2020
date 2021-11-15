#ifndef DARTSTOURNAMENTREPAIR_H
#define DARTSTOURNAMENTREPAIR_H
#include "DartTournamentsContext/DTCModelsSLAs/itournament.h"
#include "DartsModelsContext/InputModelsSLAs/abstractdartsinput.h"
#include "PlayerModelsContext/DbSLAs/iplayermodel.h"
#include "DartsModelsContext/TournamentsSLAs/idartsrepair.h"
class DartsTournamentRepair : public IDartsRepair
{
public:
    virtual bool repair(IModel<QUuid> *tournamentModel, const QVector<IModel<QUuid>*> &inputModels, AbstractPlayersContext *playersContext) const override
    {
        auto tournament = dynamic_cast<ITournament*>(tournamentModel);
        auto playerNames = tournament->playerNames();
        auto r = repairPlayerByNames(tournament,playerNames,playersContext);
        r = repairInputs(inputModels,playersContext);
        return r;
    }
private:
    bool repairPlayerByNames(ITournament *tournament, const QVector<QString> &names, AbstractPlayersContext *playersContext) const
    {
        auto players = playersContext->playerModels(names);
        if(players.count() != names.count())
            return false;
        QVector<QUuid> pIds;
        QVector<QString> pNames;
        for (const auto &model : players) {
            auto player = dynamic_cast<IPlayerModel*>(model);
            pIds << player->id();
            pNames << player->name();
        }
        tournament->setPlayerIds(pIds);
        tournament->setPlayerNames(pNames);
        return true;
    }
    bool repairInputs(const QVector<IModel<QUuid>*> &inputModels, AbstractPlayersContext *playersContext) const
    {
        for (auto &model : inputModels) {
            auto dartsInput = dynamic_cast<AbstractDartsInput*>(model);
            auto playerId = dartsInput->playerId();
            auto playerName = dartsInput->playerName();
            IPlayerModel *playerModel = dynamic_cast<IPlayerModel*>(playersContext->playerModel(playerId));
            if(playerModel != nullptr)
                continue;
            playerModel = dynamic_cast<IPlayerModel*>(playersContext->playerModel(playerName));
            if(playerModel == nullptr)
                return false;
            dartsInput->setPlayerId(playerModel->id());
            dartsInput->setPlayerName(playerModel->name());
        }
        return true;
    }
};
#endif // DARTSTOURNAMENTREPAIR_H
