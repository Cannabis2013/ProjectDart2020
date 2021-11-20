#ifndef DARTSTOURNAMENTREPAIR_H
#define DARTSTOURNAMENTREPAIR_H
#include "DartTournamentsContext/DTCModelsSLAs/itournament.h"
#include "PlayerModelsContext/DbSLAs/iplayermodel.h"
#include "DartsModelsContext/TournamentsSLAs/itournamentrepair.h"
#include "DartsModelsContext/InputModelsSLAs/iplayerinput.h"
class DartsTournamentRepair : public ITournamentRepair
{
public:
    virtual bool repair(IModel<QUuid> *tournamentModel, const QVector<IModel<QUuid>*> &inputModels, AbstractPlaCtx *playersContext) const override
    {
        auto tournament = dynamic_cast<ITournament*>(tournamentModel);
        auto r = repairTournamentPlayers(tournament,playersContext);
        r = repairInputs(inputModels,playersContext);
        return r;
    }
private:
    bool repairTournamentPlayers(ITournament *tournament, AbstractPlaCtx *playersContext) const
    {
        auto names = tournament->playerNames();
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
    bool repairInputs(const QVector<IModel<QUuid>*> &inputModels, AbstractPlaCtx *playersContext) const
    {
        for (auto &model : inputModels) {
            auto dartsInput = dynamic_cast<IPlayerInput*>(model);
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
