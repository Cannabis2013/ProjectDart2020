#ifndef DARTSVERIFYCONSISTENCY_H
#define DARTSVERIFYCONSISTENCY_H
#include "TournamentsSLAs/idartsconsistency.h"
#include "TournamentModelsSLAs/idartstournament.h"
class DartsVerifyConsistency : public IDartsConsistency<IModel<QUuid>>
{
public:
    bool verify(Model *tournament, const Models &inputs, const AbsPlaCtx *playersContext) const override
    {
        auto playerIds = dynamic_cast<IDartsTournament*>(tournament)->playerIds();
        auto playerNames = dynamic_cast<IDartsTournament*>(tournament)->playerNames();
        auto pIdConsistent = verifyPlayers(playerIds,playersContext);
        auto pNmConsistent = verifyPlayers(playerNames,playersContext);
        auto pConsistent = pIdConsistent && pNmConsistent;
        auto iConsistent = verifyInputs(inputs,playersContext);
        return pConsistent && iConsistent;
    }
private:
    bool verifyPlayers(const QVector<QUuid> &playerIds, const AbsPlaCtx *playersContext) const
    {
        for (const auto &playerId : playerIds) {
            auto player = playersContext->player(playerId);
            if(player == nullptr) return false;
        }
        return true;
    }
    bool verifyPlayers(const QVector<QString> &playerNames, const AbsPlaCtx *playersContext) const
    {
        for (const auto &playerName : playerNames) {
            auto player = playersContext->player(playerName);
            if(player == nullptr) return false;
        }
        return true;
    }
    bool verifyInputs(const Models &models, const AbsPlaCtx *playersContext) const
    {
        for (const auto &model : models) {
            auto input = dynamic_cast<IDartsInput*>(model);
            auto playerId = input->playerId();
            auto player = playersContext->player(playerId);
            if(player == nullptr) return false;
        }
        return true;
    }
};
#endif // DARTSVERIFYCONSISTENCY_H
