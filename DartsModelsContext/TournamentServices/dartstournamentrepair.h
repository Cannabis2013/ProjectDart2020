#ifndef DARTSTOURNAMENTREPAIR_H
#define DARTSTOURNAMENTREPAIR_H
#include "DartTournamentsContext/DTCModelsSLAs/itournament.h"
#include "PlayerModelsContext/DbSLAs/iplayermodel.h"
#include "DartsModelsContext/TournamentsSLAs/itournamentrepair.h"
#include "DartsModelsContext/InputModelsSLAs/iplayerinput.h"
class DartsTournamentRepair : public ITournamentRepair
{
public:
    virtual bool repair(AbstractDartsTournament *tournament, const QVector<AbstractDartsInput*> &inputs, AbstractPlayersContext *playersContext) const override
    {
        auto r = repairTournamentPlayers(tournament,playersContext);
        r = repairInputs(inputs,playersContext);
        return r;
    }
private:
    bool repairTournamentPlayers(ITournament *tournament, AbstractPlayersContext *playersContext) const
    {
        auto names = tournament->playerNames();
        auto players = playersContext->players(names);
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
    bool repairInputs(const QVector<AbstractDartsInput*> &inputs, AbstractPlayersContext *playersContext) const
    {
        for (auto &input : inputs) {
            auto playerId = input->playerId();
            auto playerName = input->playerName();
            IPlayerModel *playerModel = dynamic_cast<IPlayerModel*>(playersContext->player(playerId));
            if(playerModel != nullptr)
                continue;
            playerModel = dynamic_cast<IPlayerModel*>(playersContext->player(playerName));
            if(playerModel == nullptr)
                return false;
            input->setPlayerId(playerModel->id());
            input->setPlayerName(playerModel->name());
        }
        return true;
    }
};
#endif // DARTSTOURNAMENTREPAIR_H
