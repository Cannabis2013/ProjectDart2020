#include "localmodelsservice.h"

using namespace DartsModelsContext;

LocalModelsService *LocalModelsService::createInstance()
{
    return new LocalModelsService();
}

void LocalModelsService::addDartsTournament(const QByteArray& json)
{
    auto model = _dartsTournamentBuilder->createTournament(json);
    auto indexes = _getDartsTournamentDataFromJson->numerics(json,"indexes");
    auto playerModels = _getDartsPlayerDataFromDb->playerModels(indexes,_dartsPlayerDb);
    _dartsModelManipulator->addPlayerIds(model,_getDataFromPlayerModels->createPlayerIds(playerModels));
    _dartsModelManipulator->addPlayerNames(model,_getDataFromPlayerModels->createPlayerNames(playerModels));
    _tournamentDbManipulator->addDartsTournamentToDb(model,_dartsTournamentDb);
    emit tournamentAssembledAndStored();
}

void LocalModelsService::deleteTournaments(const QByteArray& json)
{
    QVector<int> indexes = _getDartsTournamentDataFromJson->numerics(json,"indexes");
    auto status = _tournamentDbManipulator->removeTournamentsByIndexes(indexes,_dartsTournamentDb);
    emit tournamentsDeletedStatus(status);
}

void LocalModelsService::getOrderedDartsPoints(const QUuid &tournamentId)
{
    auto models = _getInputModelsService->inputModelsByTournamentId(tournamentId,_dartsPointInputDb);
    auto orderedDartsPointModels = _inputModelsSortService->service(models,_sortPointInputsByIndexes);
    auto json = _dartsPointsJsonService->createJson(orderedDartsPointModels);
    emit sendOrderedDartsPoints(json);
}

void LocalModelsService::handleRequestTournaments()
{
    auto json = _createJsonFromDartsTournamentModels->createJson(_dartsTournamentDb->models());
    emit sendTournaments(json);
}

void LocalModelsService::handleRequestGameMode(const int &index)
{
    auto model = _dartsTournamentDb->model(index);
    emit requestAssembleTournament(model->id(),model->gameMode());
}
void LocalModelsService::addDartsPoint(const QByteArray &json)
{
    auto model = DartsPointInput::fromJson(json,DisplayHint,true);
    _dartsPointInputDb->add(model);
    auto models = _getInputModelsService->inputModelsByTournamentId(model->tournamentId(),_dartsPointInputDb);
    _dbManipulatorService->removeModelsByHint(models,HiddenHint,_dartsPointInputDb);
    auto alteredModel = _addPlayerNameToDartsInputModel->service(model,model->playerName());
    emit pointAddedToDataContext(alteredModel->toJson());
}

void LocalModelsService::resetDartsPointTournament(const QUuid &tournamentId)
{
    /*
     * - Remove models associated to the tournament
     * - Reset tournament winner
     */
    auto dartsTournamentModels = _dartsPointInputDb->models();
    auto dartsTournamentModel = _getDartsTournamentByDb->tournament(tournamentId,_dartsTournamentDb);
    _dbManipulatorService->removeModelsByTournamentId(dartsTournamentModels,tournamentId,_dartsPointInputDb);
    _dartsModelManipulator->setWinnerId(dartsTournamentModel,QUuid());
    emit tournamentResetSuccess();
}

void LocalModelsService::resetDartsScoreTournament(const QUuid &tournamentId)
{
    auto dartsTournamentModel = _getDartsTournamentByDb->tournament(tournamentId,_dartsTournamentDb);
    auto dartsTournamentModels = _getInputModelsService->inputModelsByTournamentId(tournamentId,_dartsScoreInputDb);
    _dbManipulatorService->removeModelsByTournamentId(dartsTournamentModels,tournamentId,_dartsScoreInputDb);
    _dartsModelManipulator->setWinnerId(dartsTournamentModel,QUuid());
    emit tournamentResetSuccess();
}

void LocalModelsService::setDartsTournamentWinner(const QByteArray& json)
{
    auto winnerId = _getDartsTournamentDataFromJson->id(json,"winnerId");
    auto tournamentId = _getDartsTournamentDataFromJson->id(json,"tournamentId");
    auto dartsTournamentModel = _getDartsTournamentByDb->tournament(tournamentId,_dartsTournamentDb);
    _dartsModelManipulator->setWinnerId(dartsTournamentModel,winnerId);
    auto playerModel =_getDartsPlayerDataFromDb->playerModel(winnerId,_dartsPlayerDb);
    auto responseJson = _dartsPlayerJsonBuilder->createJson(winnerId,playerModel->playerName());
    emit setDartsTournamentWinnerSucces(responseJson);
}

void LocalModelsService::assembleDartsKeyValues(const QUuid &tournamentId)
{
    auto model = _getDartsTournamentByDb->tournament(tournamentId,_dartsTournamentDb);
    auto json = _createJsonFromDartsTournamentModels->createJson(model);
    auto hint = _getDataFromDartsTournament->inputHint(model);
    emit sendDartsDetails(json,hint);
}

void LocalModelsService::createPlayer(const QByteArray &json)
{
    auto playerModel = _playerModelBuilder->createPlayerModel(json);
    _dartsPlayerDb->add(playerModel);
    emit createPlayerResponse(true);
}

void LocalModelsService::deletePlayerFromIndex(const QByteArray &json)
{
    auto index = _getDartsTournamentDataFromJson->numeric(json,"index");
    auto status = _playerDbManipulator->remove(index,_dartsPlayerDb);
    emit playersDeletedStatus(status);
}

void LocalModelsService::deletePlayersFromIndexes(const QByteArray &json)
{
    QVector<int> indexes = _getDartsTournamentDataFromJson->numerics(json,"indexes");
    auto status = _playerDbManipulator->remove(indexes,_dartsPlayerDb);
    emit playersDeletedStatus(status);
}

void LocalModelsService::handleRequestPlayersDetails()
{
    auto playerModels = _dartsPlayerDb->models();
    auto json = _dartsPlayerJsonBuilder->createJson(playerModels);
    emit sendPlayers(json);
}

void LocalModelsService::assembleDartsPointIndexes(const QUuid &tournamentId)
{
    auto dartsTournamentModel = _getDartsTournamentByDb->tournament(tournamentId,_dartsTournamentDb);
    auto assignedPlayers = dartsTournamentModel->assignedPlayerIdentities();
    auto models = _getInputModelsService->inputModelsByTournamentId(tournamentId,_dartsPointInputDb);
    auto allModelsCount = _inputModelsScountervice->countInputModelsByTournamentId(tournamentId,_dartsPointInputDb);
    auto indexes = _dartsPointInputService->dartsPointIndexes(models,allModelsCount,assignedPlayers.count());
    auto json = _dartsPointsJsonService->createJson(indexes);
    emit sendDartsPointIndexesAsJson(json);
}

void LocalModelsService::assembleDartsTournamentDataFromId(const QUuid &tournamentId)
{
    auto dartsTournamentModel = _getDartsTournamentByDb->tournament(tournamentId,_dartsTournamentDb);
    auto names = _getDartsPlayerDataFromDb->playerNames(dartsTournamentModel->assignedPlayerIdentities(),_dartsPlayerDb);
    auto json = dartsTournamentModel->toJson();
    json = _dartsJsonManipulator->addPlayerNamesToDartsTournamentJson(json,names);
    auto winnerName = _getDartsPlayerDataFromDb->playerName(dartsTournamentModel->winnerId(),_dartsPlayerDb);
    json = _dartsJsonManipulator->addWinnerNameToDartsTournamentJson(json,winnerName);
    emit sendTournamentMeta(json);
}


void LocalModelsService::hideDartsPoint(const QUuid& tournamentId,
                                        const QUuid& playerId,
                                        const int &roundIndex,
                                        const int& attemptIndex)
{

    auto model = _dartsPointInputService->dartsPointModel(tournamentId,playerId,roundIndex,attemptIndex,_dartsPointInputDb);
    _dartsPointInputService->setDartsPointHint(model,HiddenHint,_dartsPointInputDb);
    emit hideDartsPointSuccess(model->toJson());
}

void LocalModelsService::revealPoint(const QUuid &tournamentId,
                                     const QUuid &playerId,
                                     const int &roundIndex,
                                     const int &attemptIndex)
{
    auto model = _dartsPointInputService->dartsPointModel(tournamentId,playerId,roundIndex,attemptIndex,_dartsPointInputDb);
    _dartsPointInputService->setDartsPointHint(model,DisplayHint,_dartsPointInputDb);
    auto playerName = _getDartsPlayerDataFromDb->playerName(playerId,_dartsPlayerDb);
    _addPlayerNameToDartsInputModel->service(model,playerName);
    emit revealDartsPointSuccess(model->toJson());
}

void LocalModelsService::hideDartsScore(const QUuid& tournamentId,
                                        const QUuid& playerId,
                                        const int& roundIndex)
{
    auto dartsScoreModel = _dartsScoreInputService->dartsScoreModel(tournamentId,
                                                                 playerId,
                                                                 roundIndex,
                                                                 _dartsScoreInputDb);
    _dartsScoreInputService->setDartsScoreHint(dartsScoreModel,ModelDisplayHint::HiddenHint,_dartsScoreInputDb);
    auto playerName = _getDartsPlayerDataFromDb->playerName(playerId,_dartsPlayerDb);
    _addPlayerNameToDartsInputModel->service(dartsScoreModel,playerName);
    emit hideDartsScoreSuccess(dartsScoreModel->toJson());
}

void LocalModelsService::revealScore(const QUuid& tournamentId,
                                     const QUuid& playerId,
                                     const int& roundIndex)
{
    auto dartsScoreModel = _dartsScoreInputService->dartsScoreModel(tournamentId,
                                                                 playerId,
                                                                 roundIndex,
                                                                 _dartsScoreInputDb);
    _dartsScoreInputService->setDartsScoreHint(dartsScoreModel,DisplayHint,_dartsScoreInputDb);
    auto playerName = _getDartsPlayerDataFromDb->playerName(playerId,_dartsPlayerDb);
    _addPlayerNameToDartsInputModel->service(dartsScoreModel,playerName);
    emit revealDartsScoreSuccess(dartsScoreModel->toJson());
}

void LocalModelsService::addDartsScore(const QByteArray &json)
{
    auto model = DartsScoreInput::fromJson(json,ModelDisplayHint::DisplayHint,true);
    _dartsScoreInputDb->add(model);
    auto models = _getInputModelsService->inputModelsByTournamentId(model->tournamentId(),_dartsScoreInputDb);
    _dbManipulatorService->removeModelsByHint(models,HiddenHint,_dartsScoreInputDb);
    auto playerName = _getDartsPlayerDataFromDb->playerName(model->playerId(),_dartsPlayerDb);
    auto alteredModel = _addPlayerNameToDartsInputModel->service(model,playerName);
    emit scoreAddedToDataContext(alteredModel->toJson());
}


void LocalModelsService::assembleAssignedPlayerEntities(const QUuid& tournamentId)
{
    auto model = _getDartsTournamentByDb->tournament(tournamentId,_dartsTournamentDb);
    auto playerNames = _getDartsPlayerDataFromDb->playerNames(model->assignedPlayerIdentities(),_dartsPlayerDb);
    auto json = _dartsPlayerJsonBuilder->createJson(model->assignedPlayerIdentities(),playerNames);
    emit sendAssignedPlayerIdsAndNamesAsJson(json);
}

void LocalModelsService::assembleDartsTournamentWinnerIdAndName(const QUuid& tournamentId)
{
    auto dartsTournamentModel = _getDartsTournamentByDb->tournament(tournamentId,_dartsTournamentDb);
    auto winnerName = _getDartsPlayerDataFromDb->playerName(dartsTournamentModel->winnerId(),_dartsPlayerDb);
    auto json = _dartsPlayerJsonBuilder->createJson(dartsTournamentModel->winnerId(),winnerName);
    emit sendDartsTournamentWinnerIdAndName(json);
}

void LocalModelsService::assembleAssignedPlayerPoints(const QUuid& tournamentId)
{
    auto models = _getInputModelsService->inputModelsByTournamentId(tournamentId,_dartsPointInputDb);
    auto json = _dartsPointsJsonService->createJson(models);
    emit sendTournamentDartsPointsAsJson(json);
}


void LocalModelsService::assembleAssignedPlayerScores(const QUuid &tournamentId)
{
    auto models = _getInputModelsService->inputModelsByHint(tournamentId,DisplayHint,_dartsScoreInputDb);
    auto json = _dartsScoresJsonService->assembleJsonFromDartsMultiAttemptScores(models);
    emit sendTournamentDartsScoresAsJson(json);
}


void LocalModelsService::assembleDartsScoreIndexes(const QUuid &tournamentId)
{
    auto dartsTournamentModel = _getDartsTournamentByDb->tournament(tournamentId,_dartsTournamentDb);
    auto playersCount = dartsTournamentModel->assignedPlayerIdentities().count();
    auto indexes = _dartsScoreInputService->dartsScoreIndexes(tournamentId,playersCount,_dartsScoreInputDb);
    auto json = _dartsScoresJsonService->assembleJsonDartsScoreIndexes(indexes);
    emit sendDartsScoreIndexesAsJson(json);
}
