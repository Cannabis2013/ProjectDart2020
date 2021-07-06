#include "localdartsmodelsservice.h"

using namespace DartsModelsContext;

LocalDartsModelsService *LocalDartsModelsService::createInstance()
{
    return new LocalDartsModelsService();
}

void LocalDartsModelsService::addDartsTournament(const QByteArray& json)
{
    auto model = _dartsTournamentBuilder->createTournament(json);
    auto indexes = _getDartsTournamentDataFromJson->numerics(json,"indexes");
    auto playerModels = _getDartsPlayerData->playerModels(indexes,_dartsPlayersDb);
    _dartsModelManipulator->addPlayerIds(model,_getDataFromPlayerModels->createPlayerIds(playerModels));
    _dartsModelManipulator->addPlayerNames(model,_getDataFromPlayerModels->createPlayerNames(playerModels));
    _tournamentDbManipulator->addDartsTournamentToDb(model,_dartsTournamentDb);
    emit tournamentAssembledAndStored();
}

void LocalDartsModelsService::deleteTournaments(const QByteArray& json)
{
    QVector<int> indexes = _getDartsTournamentDataFromJson->numerics(json,"indexes");
    auto status = _tournamentDbManipulator->removeTournamentsByIndexes(indexes,_dartsTournamentDb);
    emit tournamentsDeletedStatus(status);
}

void LocalDartsModelsService::getOrderedDartsPoints(const QUuid &tournamentId)
{
    auto models = _getInputsFromDb->inputModels(tournamentId,_dartsPointsDb);
    auto orderedDartsPointModels = _sortInputs->sort(models,_sortPointInputsByIndexes);
    auto json = _dartsPointsJsonService->createJson(orderedDartsPointModels);
    emit sendOrderedDartsPoints(json);
}

void LocalDartsModelsService::handleRequestTournaments()
{
    auto json = _createJsonFromDartsTournamentModels->createJson(_dartsTournamentDb->models());
    emit sendTournaments(json);
}

void LocalDartsModelsService::handleRequestGameMode(const int &index)
{
    auto model = _dartsTournamentDb->model(index);
    emit requestAssembleTournament(model->id(),model->gameMode());
}
void LocalDartsModelsService::addDartsPoint(const QByteArray &json)
{
    auto model = DartsPointInput::fromJson(json,DisplayHint,true);
    _dartsPointsDb->add(model);
    auto models = _getInputsFromDb->inputModels(model->tournamentId(),_dartsPointsDb);
    _dbManipulatorService->removeModelsByHint(models,HiddenHint,_dartsPointsDb);
    auto alteredModel = _addPlayerNameToDartsInputModel->service(model,model->playerName());
    emit pointAddedToDataContext(alteredModel->toJson());
}

void LocalDartsModelsService::resetDartsPointTournament(const QUuid &tournamentId)
{
    /*
     * - Remove models associated to the tournament
     * - Reset tournament winner
     */
    auto dartsTournamentModels = _dartsPointsDb->models();
    auto dartsTournamentModel = _getTournament->tournament(tournamentId,_dartsTournamentDb);
    _dbManipulatorService->removeModelsByTournamentId(dartsTournamentModels,tournamentId,_dartsPointsDb);
    _dartsModelManipulator->setWinnerId(dartsTournamentModel,QUuid());
    emit tournamentResetSuccess();
}

void LocalDartsModelsService::resetDartsScoreTournament(const QUuid &tournamentId)
{
    auto dartsTournamentModel = _getTournament->tournament(tournamentId,_dartsTournamentDb);
    auto dartsTournamentModels = _getInputsFromDb->inputModels(tournamentId,_dartsScoresDb);
    _dbManipulatorService->removeModelsByTournamentId(dartsTournamentModels,tournamentId,_dartsScoresDb);
    _dartsModelManipulator->setWinnerId(dartsTournamentModel,QUuid());
    emit tournamentResetSuccess();
}

void LocalDartsModelsService::setDartsTournamentWinner(const QByteArray& json)
{
    auto winnerId = _getDartsTournamentDataFromJson->id(json,"winnerId");
    auto tournamentId = _getDartsTournamentDataFromJson->id(json,"tournamentId");
    auto dartsTournamentModel = _getTournament->tournament(tournamentId,_dartsTournamentDb);
    _dartsModelManipulator->setWinnerId(dartsTournamentModel,winnerId);
    auto playerModel =_getDartsPlayerData->playerModel(winnerId,_dartsPlayersDb);
    auto responseJson = _dartsPlayerJsonBuilder->createJson(winnerId,playerModel->playerName());
    emit setDartsTournamentWinnerSucces(responseJson);
}

void LocalDartsModelsService::createDartsKeyValues(const QUuid &tournamentId)
{
    auto model = _getTournament->tournament(tournamentId,_dartsTournamentDb);
    auto json = _createJsonFromDartsTournamentModels->createJson(model);
    auto hint = _getDataFromDartsTournament->inputHint(model);
    emit sendDartsDetails(json,hint);
}

void LocalDartsModelsService::createPlayer(const QByteArray &json)
{
    auto playerModel = _playerModelBuilder->createPlayerModel(json);
    _dartsPlayersDb->add(playerModel);
    emit createPlayerResponse(true);
}

void LocalDartsModelsService::deletePlayerFromIndex(const QByteArray &json)
{
    auto index = _getDartsTournamentDataFromJson->numeric(json,"index");
    auto status = _playerDbManipulator->remove(index,_dartsPlayersDb);
    emit playersDeletedStatus(status);
}

void LocalDartsModelsService::deletePlayersFromIndexes(const QByteArray &json)
{
    QVector<int> indexes = _getDartsTournamentDataFromJson->numerics(json,"indexes");
    auto status = _playerDbManipulator->remove(indexes,_dartsPlayersDb);
    emit playersDeletedStatus(status);
}

void LocalDartsModelsService::handleRequestPlayersDetails()
{
    auto playerModels = _dartsPlayersDb->models();
    auto json = _dartsPlayerJsonBuilder->createJson(playerModels);
    emit sendPlayers(json);
}

void LocalDartsModelsService::createDartsPointIndexes(const QUuid &tournamentId)
{
    auto tournamentModel = _getTournament->tournament(tournamentId,_dartsTournamentDb);
    auto indexes = _createIndexesFromPointModels->createIndexes(tournamentModel,_getInputsFromDb,_sortInputs,
                                                                _countInputs,_dartsPointsDb);
    auto json = _createJsonFromPointIndexes->createJson(indexes);
    emit sendDartsPointIndexesAsJson(json);
}

void LocalDartsModelsService::createDartsTournamentDataFromId(const QUuid &tournamentId)
{
    auto dartsTournamentModel = _getTournament->tournament(tournamentId,_dartsTournamentDb);
    auto names = _getDartsPlayerData->playerNames(dartsTournamentModel->assignedPlayerIds(),_dartsPlayersDb);
    auto winnerName = _getDartsPlayerData->playerName(dartsTournamentModel->winnerId(),_dartsPlayersDb);
    auto json = dartsTournamentModel->toJson();
    json = _addToDartsTournament->addPlayerNames(json,names);
    json = _addToDartsTournament->addWinnerName(json,winnerName);
    emit sendTournamentMeta(json);
}


void LocalDartsModelsService::hideDartsPoint(const QUuid& tournamentId,
                                        const QUuid& playerId,
                                        const int &roundIndex,
                                        const int& attemptIndex)
{

    auto model = _getPointFromDb->get(tournamentId,playerId,roundIndex,
                                                attemptIndex,_dartsPointsDb);
    _dartsPointInputService->setDartsPointHint(model,HiddenHint,_dartsPointsDb);
    emit hideDartsPointSuccess(model->toJson());
}

void LocalDartsModelsService::revealPoint(const QUuid &tournamentId,
                                     const QUuid &playerId,
                                     const int &roundIndex,
                                     const int &attemptIndex)
{
    auto model = _getPointFromDb->get(tournamentId,playerId,roundIndex,attemptIndex,_dartsPointsDb);
    _dartsPointInputService->setDartsPointHint(model,DisplayHint,_dartsPointsDb);
    auto playerName = _getDartsPlayerData->playerName(playerId,_dartsPlayersDb);
    _addPlayerNameToDartsInputModel->service(model,playerName);
    emit revealDartsPointSuccess(model->toJson());
}

void LocalDartsModelsService::hideDartsScore(const QUuid& tournamentId,
                                        const QUuid& playerId,
                                        const int& roundIndex)
{
    auto dartsScoreModel = _getScoreFromDb->get(tournamentId,playerId,roundIndex,_dartsScoresDb);
    _dartsScoreInputService->setDartsScoreHint(dartsScoreModel,ModelDisplayHint::HiddenHint,_dartsScoresDb);
    auto playerName = _getDartsPlayerData->playerName(playerId,_dartsPlayersDb);
    _addPlayerNameToDartsInputModel->service(dartsScoreModel,playerName);
    emit hideDartsScoreSuccess(dartsScoreModel->toJson());
}

void LocalDartsModelsService::revealScore(const QUuid& tournamentId,
                                     const QUuid& playerId,
                                     const int& roundIndex)
{
    auto dartsScoreModel = _getScoreFromDb->get(tournamentId,
                                                                      playerId,
                                                                      roundIndex,
                                                                      _dartsScoresDb);
    _dartsScoreInputService->setDartsScoreHint(dartsScoreModel,DisplayHint,_dartsScoresDb);
    auto playerName = _getDartsPlayerData->playerName(playerId,_dartsPlayersDb);
    _addPlayerNameToDartsInputModel->service(dartsScoreModel,playerName);
    emit revealDartsScoreSuccess(dartsScoreModel->toJson());
}

void LocalDartsModelsService::addDartsScore(const QByteArray &json)
{
    auto model = DartsScoreInput::fromJson(json,ModelDisplayHint::DisplayHint,true);
    _dartsScoresDb->add(model);
    auto models = _getInputsFromDb->inputModels(model->tournamentId(),_dartsScoresDb);
    _dbManipulatorService->removeModelsByHint(models,HiddenHint,_dartsScoresDb);
    auto playerName = _getDartsPlayerData->playerName(model->playerId(),_dartsPlayersDb);
    auto alteredModel = _addPlayerNameToDartsInputModel->service(model,playerName);
    emit scoreAddedToDataContext(alteredModel->toJson());
}


void LocalDartsModelsService::createAssignedPlayerEntities(const QUuid& tournamentId)
{
    auto model = _getTournament->tournament(tournamentId,_dartsTournamentDb);
    auto playerNames = _getDartsPlayerData->playerNames(model->assignedPlayerIds(),_dartsPlayersDb);
    auto json = _dartsPlayerJsonBuilder->createJson(model->assignedPlayerIds(),playerNames);
    emit sendAssignedPlayerIdsAndNamesAsJson(json);
}

void LocalDartsModelsService::createDartsTournamentWinnerIdAndName(const QUuid& tournamentId)
{
    auto dartsTournamentModel = _getTournament->tournament(tournamentId,_dartsTournamentDb);
    auto winnerName = _getDartsPlayerData->playerName(dartsTournamentModel->winnerId(),_dartsPlayersDb);
    auto json = _dartsPlayerJsonBuilder->createJson(dartsTournamentModel->winnerId(),winnerName);
    emit sendDartsTournamentWinnerIdAndName(json);
}

void LocalDartsModelsService::createAssignedPlayerPoints(const QUuid& tournamentId)
{
    auto models = _getInputsFromDb->inputModels(tournamentId,_dartsPointsDb);
    auto json = _dartsPointsJsonService->createJson(models);

    emit sendTournamentDartsPointsAsJson(json);
}


void LocalDartsModelsService::createAssignedPlayerScores(const QUuid &tournamentId)
{
    auto models = _getInputsFromDb->inputModels(tournamentId,DisplayHint,_dartsScoresDb);
    auto json = _createJsonFromScoreModels->createJson(models);
    emit sendTournamentDartsScoresAsJson(json);
}


void LocalDartsModelsService::createDartsScoreIndexes(const QUuid &tournamentId)
{
    auto tournamentModel = _getTournament->tournament(tournamentId,_dartsTournamentDb);
    auto indexes = _createIndexesFromScoreModels->createIndexes(tournamentModel,_getInputsFromDb,_sortInputs,_countInputs,_dartsScoresDb);
    auto json = _createJsonfromScoreIndexes->createJson(indexes);
    emit sendDartsScoreIndexesAsJson(json);
}
