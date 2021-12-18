#ifndef DARTSTOURNAMENTREPAIR_H
#define DARTSTOURNAMENTREPAIR_H
#include <qvector.h>
#include "InputModelsSLAs/abstractdartsinput.h"
#include "TournamentsSLAs/itournamentrepair.h"
#include "InputModelsSLAs/iplayerinput.h"
#include "TournamentModelsSLAs/idartstournament.h"
#include "ContextSLA/absplactx.h"
class DartsTournamentRepair : public ITournamentRepair
{
public:
    virtual bool repair(IDartsTournament *tournament, const QVector<AbstractDartsInput*> &inputs, AbsPlaCtx *playersContext) const override
    {
        auto r = repairTournamentPlayers(tournament,playersContext);
        r = repairInputs(inputs,playersContext)? true : r;
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
        for (const auto &model : players) {
            auto player = dynamic_cast<IPlayer*>(model);
            pIds << player->id();
            pNames << player->name();
        }
        tournament->setPlayerIds(pIds);
        tournament->setPlayerNames(pNames);
        return true;
    }
    bool repairInputs(const QVector<AbstractDartsInput*> &inputs, AbsPlaCtx *playersContext) const
    {
        for (auto &input : inputs) {
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
