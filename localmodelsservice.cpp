#include "localmodelsservice.h"

LocalModelsService *LocalModelsService::createInstance()
{
    return new LocalModelsService();
}

void LocalModelsService::addDartsTournament(const QByteArray& json)
{
    auto model = DartsTournament::fromJson(json);
    auto indexes = _dartsJsonService->getPlayerIndexesFromJson(json);
    auto playerIds = _playerModelsService->assemblePlayerIds(indexes);
    auto newModel = _dartsJsonService->assignPlayerIdsToDartsTournament(model,playerIds);
    _dartsModelsService->addDartsTournamentToDb(newModel);
    emit tournamentAssembledAndStored(true);
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
    auto json = _dartsJsonService->assembleJsonDartsTournamentModels(_dartsModelsService,
                                                                     _playerModelsService);
    emit sendTournaments(json);
}

void LocalModelsService::handleRequestGameMode(const int &index)
{
    auto model = _dartsModelsService->dartsTournamentByIndex(index);;
    emit requestAssembleTournament(model->id(),model->gameMode());
}
void LocalModelsService::addDartsPoint(const QByteArray &json)
{
    auto model = DartsPointInput::createInstance(json,true);
    _dartsModelsService->addDartsPoint(model);
    _dartsModelsService->removeHiddenPoints(model->tournamentId());
    auto playerName = _playerModelsService->playerNameById(model->playerId());
    auto alteredModel = _addPlayerNameToDartsInputModel->service(model,playerName);
    emit pointAddedToDataContext(alteredModel->toJson());
}

void LocalModelsService::resetDartsPointTournament(const QUuid &tournament)
{
    /*
     * - Remove models associated to the tournament
     * - Reset tournament winner
     */
    _dartsModelsService->removePointsByTournamentId(tournament);
    _dartsModelsService->tournamentSetWinnerId(tournament,QUuid());
    emit tournamentResetSuccess();
}

void LocalModelsService::resetDartsScoreTournament(const QUuid &tournamentId)
{
    _dartsModelsService->removeScoresByTournamentId(tournamentId);
    _dartsModelsService->tournamentSetWinnerId(tournamentId,QUuid());
    emit tournamentResetSuccess();
}

void LocalModelsService::setDartsTournamentWinner(const QByteArray& json)
{
    auto winnerId = _dartsJsonService->getWinnerIdByJson(json);
    auto tournamentId = _dartsJsonService->getTournamentIdByJson(json);
    _dartsModelsService->tournamentSetWinnerId(tournamentId,winnerId);
    auto winnerName = _playerModelsService->playerNameById(winnerId);
    auto responseJson = _dartsJsonService->assembleJsonByPlayerIdAndName(winnerId,winnerName);
    emit setDartsTournamentWinnerSucces(responseJson);
}

void LocalModelsService::assembleDartsKeyValues(const QUuid &tournamentId)
{
    auto model = _dartsModelsService->dartsTournamentModelById(tournamentId);
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
        auto playerName = _playerModelsService->playerNameById(playerId);
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
    auto indexes = _dartsModelsService->dartsPointIndexes(tournament);
    auto json = _dartsJsonService->assembleJsonDartsPointIndexes(indexes);
    emit sendDartsPointIndexesAsJson(json);
}

void LocalModelsService::assembleDartsTournamentDataFromId(const QUuid &tournamentId)
{
    auto dartsTournamentModel = _dartsModelsService->dartsTournamentModelById(tournamentId);
    auto names = _playerModelsService->assemblePlayerNamesFromIds(dartsTournamentModel->assignedPlayerIdentities());
    auto json = dartsTournamentModel->toJson();
    json = _dartsJsonService->addPlayerNamesToDartsTournamentJson(json,names);
    auto winnerName = _playerModelsService->playerNameById(dartsTournamentModel->winnerId());
    json = _dartsJsonService->addWinnerNameToDartsTournamentJson(json,winnerName);
    emit sendTournamentMeta(json);
}


void LocalModelsService::hideDartsPoint(const QUuid& tournamentId,
                                            const QUuid& playerId,
                                            const int &roundIndex,
                                            const int& attemptIndex)
{
    auto pointModel = _dartsModelsService->setDartsPointHint(tournamentId,
                                                             playerId,
                                                             roundIndex,
                                                             attemptIndex,
                                                             ModelDisplayHint::HiddenHint);
    emit hideDartsPointSuccess(pointModel->toJson());
}

void LocalModelsService::revealPoint(const QUuid &tournamentId, const QUuid &playerId, const int &roundIndex, const int &attemptIndex)
{
    auto model = _dartsModelsService->setDartsPointHint(tournamentId,
                                                        playerId,
                                                        roundIndex,
                                                        attemptIndex,
                                                        ModelDisplayHint::DisplayHint);
    auto playerName = _playerModelsService->playerNameById(playerId);
    auto playerInputModel = _addPlayerNameToDartsInputModel->service(model,playerName);
    emit revealDartsPointSuccess(playerInputModel->toJson());
}

void LocalModelsService::hideDartsScore(const QUuid& tournamentId,
                                        const QUuid& playerId,
                                        const int& roundIndex)
{
    auto model =_dartsModelsService->setDartsScoreHint(tournamentId,
                                                              playerId,
                                                              roundIndex,
                                                              ModelDisplayHint::HiddenHint);
    auto playerName = _playerModelsService->playerNameById(playerId);
    auto playerInputModel = _addPlayerNameToDartsInputModel->service(model,playerName);
    emit hideDartsScoreSuccess(playerInputModel->toJson());
}

void LocalModelsService::revealScore(const QUuid& tournamentId, const QUuid& playerId, const int& roundIndex)
{
    auto alteredModel = _dartsModelsService->setDartsScoreHint(tournamentId,
                                                               playerId,
                                                               roundIndex,
                                                               ModelDisplayHint::DisplayHint);
    auto playerName = _playerModelsService->playerNameById(playerId);
    auto playerInputModel = _addPlayerNameToDartsInputModel->service(alteredModel,playerName);
    emit revealDartsScoreSuccess(playerInputModel->toJson());
}

void LocalModelsService::addDartsScore(const QByteArray &json)
{
    auto model = DartsScoreInput::createInstance(json);
    _dartsModelsService->addDartsScore(model);
    _dartsModelsService->removeHiddenScores(model->tournamentId());
    auto playerName = _playerModelsService->playerNameById(model->playerId());
    auto alteredModel = _addPlayerNameToDartsInputModel->service(model,playerName);
    emit scoreAddedToDataContext(alteredModel->toJson());
}


void LocalModelsService::assembleAssignedPlayerEntities(const QUuid& tournamentId)
{
    auto model = _dartsModelsService->dartsTournamentModelById(tournamentId);
    auto playerNames = _playerModelsService->assemblePlayerNamesFromIds(model->assignedPlayerIdentities());
    auto json = _dartsJsonService->assembleJsonFromPlayerNamesAndIds(model->assignedPlayerIdentities(),playerNames);
    emit sendAssignedPlayerIdsAndNamesAsJson(json);
}

void LocalModelsService::assembleDartsTournamentWinnerIdAndName(const QUuid& tournamentId)
{
    auto model = _dartsModelsService->dartsTournamentModelById(tournamentId);
    auto winnerName = _playerModelsService->playerNameById(model->winnerId());
    auto json = _dartsJsonService->assembleJsonByPlayerIdAndName(model->winnerId(),winnerName);
    emit sendDartsTournamentWinnerIdAndName(json);
}

LocalModelsService *LocalModelsService::setAddPlayerNameToDartsInputModel(
        IBinaryService<const IPlayerInput*,
                       const QString &,
                       const IPlayerInput*> *newAddPlayerNameToScoreModel)
{
    _addPlayerNameToDartsInputModel = newAddPlayerNameToScoreModel;
    return this;
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


void LocalModelsService::assembleAssignedPlayerScores(const QUuid &tournamentId)
{
    auto models = _dartsModelsService->dartsScoreModelsByTournamentIdAndHint(tournamentId,ModelDisplayHint::DisplayHint);
    auto json = _dartsJsonService->assembleJsonFromDartsMultiAttemptScores(models);
    emit sendTournamentDartsScoresAsJson(json);
}


void LocalModelsService::assembleDartsScoreIndexes(const QUuid &tournament)
{
    auto indexes = _dartsModelsService->dartsScoreIndexes(tournament);
    auto json = _dartsJsonService->assembleJsonDartsScoreIndexes(indexes);
    emit sendDartsScoreIndexesAsJson(json);
}
