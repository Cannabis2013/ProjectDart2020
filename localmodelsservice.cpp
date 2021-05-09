#include "localmodelsservice.h"

LocalModelsService *LocalModelsService::createInstance()
{
    return new LocalModelsService();
}

void LocalModelsService::addDartsTournament(const QByteArray& json)
{
    auto model = _dartsJsonService->assembleDartsTournamentFromJson(json);
    auto indexes = _dartsJsonService->getPlayerIndexesFromJson(json);
    auto playerIds = _playerModelsService->assemblePlayerIds(indexes);
    auto newModel = _dartsJsonService->assignPlayerIdsToDartsTournament(model,playerIds);
    _dartsModelsService->addDartsTournamentToDb(newModel);
    emit tournamentAssembledAndStored(true);
}

void LocalModelsService::assignPlayersToTournament(const QUuid &tournament,
                                                             const QList<QUuid> &playersID)
{
    for (auto playerID : playersID)
        _dartsModelsService->tournamentAssignPlayer(tournament,playerID);
}

void LocalModelsService::deleteTournaments(const QByteArray& json)
{
    QVector<int> indexes = _dartsJsonService->getDeleteTournamentIndexesFromJson(json);
    auto status = _dartsModelsService->removeTournamentsByIndexes(indexes);
    emit tournamentsDeletedStatus(status);
}

void LocalModelsService::getOrderedDartsPoints(const QUuid &tournamentId)
{
    auto orderedDartsPointModels = _dartsModelsService->getDartsPointModelsOrdedByIndexes(tournamentId);
    auto json = _dartsJsonService->assembleJsonOrderedDartsPointModels(orderedDartsPointModels,_playerModelsService);
    emit sendDartsSingleAttemptPoints(json);
}

void LocalModelsService::handleRequestTournaments()
{
    auto json = _dartsJsonService->assembleJsonDartsTournamentModels(_dartsModelsService,_playerModelsService);
    emit sendTournaments(json);
}

void LocalModelsService::handleRequestGameMode(const int &index)
{
    QUuid tournamentId;
    try {
        tournamentId = _dartsModelsService->tournamentIdFromIndex(index);
    }  catch (const char *msg) {
        return;
    }
    auto gameMode = _dartsModelsService->tournamentGameMode(tournamentId);
    emit requestAssembleTournament(tournamentId,gameMode);
}
void LocalModelsService::addDartsPoint(const QByteArray &json)
{
    auto model = _dartsJsonService->assembleDartsPointModelFromJson(json);
    _dartsModelsService->addDartsPoint(model);
    auto alteredJson = _dartsJsonService->addPlayerNameToJsonPointModel(json,_playerModelsService);
    emit scoreAddedToDataContext(alteredJson);
}

void LocalModelsService::resetTournament(const QUuid &tournament)
{
    /*
     * - Remove models associated to the tournament
     * - Reset tournament winner
     */
    _dartsModelsService->removePointsByTournamentId(tournament);
    _dartsModelsService->tournamentSetWinnerId(tournament,QUuid());
    emit tournamentResetSuccess();
}

void LocalModelsService::assembleDartsKeyValues(const QUuid &tournamentId)
{
    auto model = _dartsModelsService->getDartsTournamentModelById(tournamentId);
    auto json = _dartsJsonService->assembleJsonFromDartsTournamentModel(model);
    emit sendTournamentFtpDetails(json);
}

void LocalModelsService::createPlayer(const QByteArray &json)
{
    auto playerModel = _dartsJsonService->assemblePlayerModelFromJson(json);
    _playerModelsService->addPlayerModelToDb(playerModel);
    emit createPlayerResponse(true);
}

void LocalModelsService::deletePlayerFromIndex(const QByteArray &json)
{
    auto index = _dartsJsonService->getDeletePlayerIndexFromJson(json);
    auto status = _playerModelsService->deletePlayer(index);
    emit playersDeletedStatus(status);
}

void LocalModelsService::deletePlayersFromIndexes(const QByteArray &json)
{
    QVector<int> indexes = _dartsJsonService->getPlayerIndexesFromJson(json);
    auto status = _playerModelsService->deletePlayersByIndexes(indexes);
    emit playersDeletedStatus(status);
}

void LocalModelsService::handleRequestPlayersDetails()
{
    auto count = _playerModelsService->playersCount();
    QVariantList list;
    for (int i = 0; i < count; ++i) {
        auto playerId = _playerModelsService->playerIdFromIndex(i);
        auto playerName = _playerModelsService->playerNameFromId(playerId);
        auto mail = _playerModelsService->playerMailFromId(playerId);
        list += {playerName,mail};
    }
    emit sendPlayers(list);
}

LocalModelsService* LocalModelsService::setPlayerModelsService(IPlayerModelsService *playerModelsContext)
{
    _playerModelsService = playerModelsContext;
    return this;
}

LocalModelsService* LocalModelsService::setDartsModelsService(IDartsModelsService *dartsModelsService)
{
    _dartsModelsService = dartsModelsService;
    return this;
}


void LocalModelsService::assembleDartsPointIndexes(const QUuid &tournament)
{
    auto indexes = _dartsModelsService->dartsIndexes(tournament);
    auto json = _dartsJsonService->assembleJsonDartsIndexes(indexes);
    emit sendDartsPointIndexesAsJson(json);
}

void LocalModelsService::assembleDartsTournamentDataFromId(const QUuid &tournamentId)
{
    auto dartsTournamentModel = _dartsModelsService->getDartsTournamentModelById(tournamentId);
    auto json = _dartsJsonService->assembleJsonDartsTournamentModel(dartsTournamentModel,_playerModelsService);
    emit sendTournamentMeta(json);
}


void LocalModelsService::hideDartsPoint(const QUuid& tournamentId,
                                            const QUuid& playerId,
                                            const int &roundIndex,
                                            const int& attemptIndex)
{
    QUuid pointId = _dartsModelsService->getDartsPointId(tournamentId,
                                                         playerId,
                                                         roundIndex,
                                                         attemptIndex);
    auto pointModel = _dartsModelsService->setDartsPointHint(pointId,ModelDisplayHint::HiddenHint);
    auto json = _dartsJsonService->assembleJsonFromDartsPointModel(pointModel);
    emit hideDartsPointSuccess(json);
}

void LocalModelsService::revealPoint(const QUuid &tournamentId, const QUuid &playerId, const int &roundIndex, const int &attemptIndex)
{
    QUuid pointId = _dartsModelsService->getDartsPointId(tournamentId,
                                                         playerId,
                                                         roundIndex,
                                                         attemptIndex);
    auto model = _dartsModelsService->setDartsPointHint(pointId,ModelDisplayHint::DisplayHint);
    auto json = _dartsJsonService->assembleJsonFromDartsPointModel(model);
    // Implement json response
    emit revealDartsPointSuccess(json);
}

void LocalModelsService::hideDartsScore(const QUuid& tournamentId,
                                        const QUuid& playerId,
                                        const int& roundIndex)
{
    auto scoreID = _dartsModelsService->getDartsScoreId(tournamentId,
                                                        playerId,
                                                        roundIndex);
    _dartsModelsService->setDartsScoreHint(scoreID,ModelDisplayHint::HiddenHint);
    // Implement json response
    emit hideDartsScoreSuccess(QByteArray());
}

void LocalModelsService::revealScore(const QUuid& tournamentId, const QUuid& playerId, const int& roundIndex)
{
    auto scoreID = _dartsModelsService->getDartsScoreId(tournamentId,
                                                        playerId,
                                                        roundIndex);
    _dartsModelsService->setDartsScoreHint(scoreID,ModelDisplayHint::DisplayHint);
    // Implement json response
    emit revealDartsScoreSuccess(QByteArray());
}


void LocalModelsService::addDartsScore(const QByteArray &json)
{
    // TODO: Implement
}


void LocalModelsService::assembleAssignedPlayerEntities(const QUuid& tournamentId)
{
    auto playerIds = _dartsModelsService->tournamentAssignedPlayers(tournamentId);
    auto playerNames = _playerModelsService->assemblePlayerNamesFromIds(playerIds);
    auto json = _dartsJsonService->assembleJsonFromPlayerNamesAndIds(playerIds,playerNames);
    emit sendAssignedPlayerIdsAndNamesAsJson(json);
}

void LocalModelsService::assembleDartsTournamentWinnerIdAndName(const QUuid& tournamentId)
{
    auto winnerId = _dartsModelsService->tournamentWinnerId(tournamentId);
    auto winnerName = _playerModelsService->playerNameFromId(winnerId);
    auto json = _dartsJsonService->assembleJsonFromPlayerIdAndName(winnerId,winnerName);
    emit sendDartsTournamentWinnerIdAndName(json);
}

LocalModelsService *LocalModelsService::setDartsJsonService(IDartsJsonService *dartsJsonService)
{
    _dartsJsonService = dartsJsonService;
    return this;
}

void LocalModelsService::assembleAssignedPlayerPoints(const QUuid& tournamentId)
{
    auto json = _dartsJsonService->assembleJsonFromTournamentDartsPoints(tournamentId,_dartsModelsService);
    emit sendTournamentDartsPointsAsJson(json);
}
