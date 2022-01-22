#ifndef DARTSTOURNAMENTREPAIR_H
#define DARTSTOURNAMENTREPAIR_H
#include <qvector.h>
#include "DbSLAs/iplayer.h"
#include "InputModelsSLAs/idartsinput.h"
#include "TournamentsSLAs/itournamentrepair.h"
#include "InputModelsSLAs/iplayerinput.h"
#include "TournamentModelsSLAs/idartstournament.h"
#include "ContextSLA/absplactx.h"
class DartsTournamentRepair : public ITournamentRepair<IModel<QUuid>>
{
public:
    virtual bool repair(Model *tournament, const Models &models, AbsPlaCtx *playersContext) const override
    {
        auto r = repairTournamentPlayers(dynamic_cast<IDartsTournament*>(tournament),playersContext);
        r = repairInputs(models,playersContext)? true : r;
        return r;
    }
private:
    bool repairTournamentPlayers(IDartsTournament *tournament, AbsPlaCtx *playersContext) const
    {
        auto names = tournament->playerNames();
        auto players = playersContext->players(names);
        if(players.count() != names.count())
            return false;
        QVector<QUuid> pIds;
        QVector<QString> pNames;
        for (const auto &player : players) {
            pIds << player->id();
            pNames << player->name();
        }
        tournament->setPlayerIds(pIds);
        tournament->setPlayerNames(pNames);
        return true;
    }
    bool repairInputs(const Models &models, AbsPlaCtx *playersContext) const
    {
        for (auto &model : models) {
            auto input = dynamic_cast<IDartsInput*>(model);
            auto playerId = input->playerId();
            auto playerName = input->playerName();
            IPlayer *playerModel = dynamic_cast<IPlayer*>(playersContext->player(playerId));
            if(playerModel != nullptr)
                continue;
            playerModel = dynamic_cast<IPlayer*>(playersContext->player(playerName));
            if(playerModel == nullptr)
                return false;
            input->setPlayerId(playerModel->id());
            input->setPlayerName(playerModel->name());
        }
        return true;
    }
};
#endif // DARTSTOURNAMENTREPAIR_H
