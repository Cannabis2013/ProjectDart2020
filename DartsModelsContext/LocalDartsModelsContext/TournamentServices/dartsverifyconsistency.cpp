#include "dartsverifyconsistency.h"

#include <DartsModelsContext/Contracts/dartsmodelsservices.h>

#include <DartsModelsContext/Contracts/Tournament/idartstournament.h>

#include <DartsModelsContext/Contracts/Input/idartsinput.h>

bool DartsVerifyConsistency::verify(const QUuid &tournamentID, const DartsModelsServices *services) const
{
        auto playerContext = services->playersContext();
        auto tournament = getTournament(tournamentID,services);
        auto pConsistent = verifyTournamentPlayers(tournament,playerContext);
        auto inputs = getInputs(tournamentID, services);
        auto iConsistent = verifyInputsPlayers(inputs,playerContext);
        return pConsistent && iConsistent;
}

DartsVerifyConsistency::Model *DartsVerifyConsistency::getTournament(const QUuid &tournamentID, const DartsModelsServices *services) const
{
        auto tournaments = services->tournamentServices()->dbContext()->models();
        auto tournament = services->tournamentServices()->getTournament()->get(tournamentID,tournaments);
        return tournament;
}

DartsVerifyConsistency::Models DartsVerifyConsistency::getInputs(const QUuid &tournamentID, const DartsModelsServices *services) const
{
        auto inputServices = services->inputServices();
        auto inputsDbService = inputServices->dbContext();
        auto inputModels = inputsDbService->models();
        auto inputs = inputServices->getInputsFromDb()->get(tournamentID,inputModels);
        return inputs;
}

bool DartsVerifyConsistency::verifyTournamentPlayers(Model *tournament, AbstractPlayerContext *playerContext) const
{
        auto playerIds = dynamic_cast<IDartsTournament*>(tournament)->playerIds();
        auto playerNames = dynamic_cast<IDartsTournament*>(tournament)->playerNames();
        auto pIdConsistent = verifyPlayerIDs(playerIds,playerContext);
        auto pNmConsistent = verifyPlayerNames(playerNames,playerContext);
        return pIdConsistent && pNmConsistent;
}

bool DartsVerifyConsistency::verifyPlayerIDs(const QVector<QUuid> &playerIds, const AbstractPlayerContext *playersContext) const
{
    for (const auto &playerId : playerIds) {
        auto player = playersContext->player(playerId);
        if(player == QByteArray()) return false;
    }
    return true;
}

bool DartsVerifyConsistency::verifyPlayerNames(const QVector<QString> &playerNames, const AbstractPlayerContext *playersContext) const
{
    for (const auto &playerName : playerNames) {
        auto player = playersContext->player(playerName);
        if(player == QByteArray()) return false;
    }
    return true;
}

bool DartsVerifyConsistency::verifyInputsPlayers(const Models &models, const AbstractPlayerContext *playersContext) const
{
    for (const auto &model : models) {
        auto input = dynamic_cast<IDartsInput*>(model);
        auto playerId = input->playerId();
        auto player = playersContext->player(playerId);
        if(player == QByteArray()) return false;
    }
    return true;
}
