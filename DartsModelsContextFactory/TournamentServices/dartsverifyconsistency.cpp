#include "dartsverifyconsistency.h"
#include "InputModelsSLAs/idartsinput.h"
#include "TournamentModelsSLAs/idartstournament.h"
#include "SLAs/dmcservices.h"
#include "ContextSLA/absplactx.h"

DartsVerifyConsistency::DartsVerifyConsistency(DMCServices *services):_services(services){}

bool DartsVerifyConsistency::verify(const QUuid &tournamentID) const
{
    auto playerContext = _services->playersContext();
    auto tournament = getTournament(tournamentID);
    auto pConsistent = verifyTournamentPlayers(tournament,playerContext);
    auto inputs = getInputs(tournamentID);
    auto iConsistent = verifyInputsPlayers(inputs,playerContext);
    return pConsistent && iConsistent;
}

DartsVerifyConsistency::Model *DartsVerifyConsistency::getTournament(const QUuid &tournamentID) const
{
    auto tournaments = _services->tournamentServices()->dartsDbCtx()->models();
    auto tournament = _services->tournamentServices()->getTournament()->get(tournamentID,tournaments);
    return tournament;
}

DartsVerifyConsistency::Models DartsVerifyConsistency::getInputs(const QUuid &tournamentID) const
{
    auto inputServices = _services->inputServices();
    auto inputsDbService = inputServices->inputsDb();
    auto inputModels = inputsDbService->models();
    auto inputs = inputServices->getInputsFromDb()->get(tournamentID,inputModels);
    return inputs;
}

bool DartsVerifyConsistency::verifyTournamentPlayers(Model *tournament, AbsPlaCtx *playerContext) const
{
    auto playerIds = dynamic_cast<IDartsTournament*>(tournament)->playerIds();
    auto playerNames = dynamic_cast<IDartsTournament*>(tournament)->playerNames();
    auto pIdConsistent = verifyPlayerIDs(playerIds,playerContext);
    auto pNmConsistent = verifyPlayerNames(playerNames,playerContext);
    return pIdConsistent && pNmConsistent;
}

bool DartsVerifyConsistency::verifyPlayerIDs(const QVector<QUuid> &playerIds, const AbsPlaCtx *playersContext) const
{
    for (const auto &playerId : playerIds) {
        auto player = playersContext->player(playerId);
        if(player == QByteArray()) return false;
    }
    return true;
}

bool DartsVerifyConsistency::verifyPlayerNames(const QVector<QString> &playerNames, const AbsPlaCtx *playersContext) const
{
    for (const auto &playerName : playerNames) {
        auto player = playersContext->player(playerName);
        if(player == QByteArray()) return false;
    }
    return true;
}

bool DartsVerifyConsistency::verifyInputsPlayers(const Models &models, const AbsPlaCtx *playersContext) const
{
    for (const auto &model : models) {
        auto input = dynamic_cast<IDartsInput*>(model);
        auto playerId = input->playerId();
        auto player = playersContext->player(playerId);
        if(player == QByteArray()) return false;
    }
    return true;
}
