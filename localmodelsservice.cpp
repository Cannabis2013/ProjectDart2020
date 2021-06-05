#include "localmodelsservice.h"

using namespace DartsModelsContext;

LocalModelsService *LocalModelsService::createInstance()
{
    return new LocalModelsService();
}

void LocalModelsService::addDartsTournament(const QByteArray& json)
{
    auto model = _dartsTournamentBuilder->buildDartsTournamentModelByJson(json);
    auto indexes = _playerModelsJsonService->getPlayerIndexesByJson(json);
    auto playerIds = _playerModelsService->assemblePlayerIds(indexes);
    auto newModel = _dartsModelsService->assignPlayerIdsToDartsTournament(model,playerIds);
    _dartsModelsService->addDartsTournamentToDb(newModel);
    emit tournamentAssembledAndStored();
}

void LocalModelsService::deleteTournaments(const QByteArray& json)
{
    QVector<int> indexes = _dartsJsonService->getDeleteTournamentIndexesFromJson(json);
    auto status = _dartsModelsService->removeTournamentsByIndexes(indexes);
    emit tournamentsDeletedStatus(status);
}

void LocalModelsService::getOrderedDartsPoints(const QUuid &tournamentId)
{
    auto models = _getInputModelsService->inputModelsByTournamentId(tournamentId,_dartsPointInputDb);
    auto orderedDartsPointModels = _inputModelsSortService->service(models,_sortPointInputsByIndexes);
    auto json = _dartsPointsJsonService->assembleJsonOrderedDartsPointModels(orderedDartsPointModels,_playerModelsService);
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
    auto model = DartsPointInput::fromJson(json,DisplayHint,true);
    _dartsPointInputDb->addModel(model);
    auto models = _getInputModelsService->inputModelsByTournamentId(model->tournamentId(),_dartsPointInputDb);
    _dbManipulatorService->removeModelsByHint(models,HiddenHint,_dartsPointInputDb);
    auto playerName = _playerModelsService->playerNameById(model->playerId());
    auto alteredModel = _addPlayerNameToDartsInputModel->service(model,playerName);
    emit pointAddedToDataContext(alteredModel->toJson());
}

void LocalModelsService::resetDartsPointTournament(const QUuid &tournamentId)
{
    /*
     * - Remove models associated to the tournament
     * - Reset tournament winner
     */
    auto models = _dartsPointInputDb->models();
    _dbManipulatorService->removeModelsByTournamentId(models,tournamentId,_dartsPointInputDb);
    _dartsModelsService->tournamentSetWinnerId(tournamentId,QUuid());
    emit tournamentResetSuccess();
}

void LocalModelsService::resetDartsScoreTournament(const QUuid &tournamentId)
{
    auto models = _getInputModelsService->inputModelsByTournamentId(tournamentId,_dartsScoreInputDb);
    _dbManipulatorService->removeModelsByTournamentId(models,tournamentId,_dartsScoreInputDb);
    _dartsModelsService->tournamentSetWinnerId(tournamentId,QUuid());
    emit tournamentResetSuccess();
}

void LocalModelsService::setDartsTournamentWinner(const QByteArray& json)
{
    auto winnerId = _playerModelsJsonService->getWinnerIdByJson(json);
    auto tournamentId = _dartsJsonService->getTournamentIdByJson(json);
    _dartsModelsService->tournamentSetWinnerId(tournamentId,winnerId);
    auto winnerName = _playerModelsService->playerNameById(winnerId);
    auto responseJson = _playerModelsJsonService->assembleJsonByPlayerIdAndName(winnerId,winnerName);
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
    auto playerModel = _playerModelsJsonService->assemblePlayerModelFromJson(json);
    _playerModelsService->addPlayerModelToDb(playerModel);
    emit createPlayerResponse(true);
}

void LocalModelsService::deletePlayerFromIndex(const QByteArray &json)
{
    auto index = _playerModelsJsonService->getDeletePlayerIndexFromJson(json);
    auto status = _playerModelsService->deletePlayer(index);
    emit playersDeletedStatus(status);
}

void LocalModelsService::deletePlayersFromIndexes(const QByteArray &json)
{
    QVector<int> indexes = _playerModelsJsonService->getPlayerIndexesByJson(json);
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


void LocalModelsService::assembleDartsPointIndexes(const QUuid &tournamentId)
{
    auto dartsTournamentModel = _dartsModelsService->dartsTournamentModelById(tournamentId);
    auto assignedPlayers = dartsTournamentModel->assignedPlayerIdentities();
    auto models = _getInputModelsService->inputModelsByTournamentId(tournamentId,_dartsPointInputDb);
    auto allModelsCount = _inputModelsScountervice->countInputModelsByTournamentId(tournamentId,_dartsPointInputDb);
    auto indexes = _dartsPointInputService->dartsPointIndexes(models,allModelsCount,assignedPlayers.count());
    auto json = _dartsPointsJsonService->assembleJsonDartsPointIndexes(indexes);
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
    auto playerName = _playerModelsService->playerNameById(playerId);
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
    auto playerName = _playerModelsService->playerNameById(playerId);
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
    auto playerName = _playerModelsService->playerNameById(playerId);
    _addPlayerNameToDartsInputModel->service(dartsScoreModel,playerName);
    emit revealDartsScoreSuccess(dartsScoreModel->toJson());
}

void LocalModelsService::addDartsScore(const QByteArray &json)
{
    auto model = DartsScoreInput::fromJson(json,ModelDisplayHint::DisplayHint,true);
    _dartsScoreInputDb->addModel(model);
    auto models = _getInputModelsService->inputModelsByTournamentId(model->tournamentId(),_dartsScoreInputDb);
    _dbManipulatorService->removeModelsByHint(models,HiddenHint,_dartsScoreInputDb);
    auto playerName = _playerModelsService->playerNameById(model->playerId());
    auto alteredModel = _addPlayerNameToDartsInputModel->service(model,playerName);
    emit scoreAddedToDataContext(alteredModel->toJson());
}


void LocalModelsService::assembleAssignedPlayerEntities(const QUuid& tournamentId)
{
    auto model = _dartsModelsService->dartsTournamentModelById(tournamentId);
    auto playerNames = _playerModelsService->assemblePlayerNamesFromIds(model->assignedPlayerIdentities());
    auto json = _playerModelsJsonService->assembleJsonFromPlayerNamesAndIds(model->assignedPlayerIdentities(),playerNames);
    emit sendAssignedPlayerIdsAndNamesAsJson(json);
}

void LocalModelsService::assembleDartsTournamentWinnerIdAndName(const QUuid& tournamentId)
{
    auto model = _dartsModelsService->dartsTournamentModelById(tournamentId);
    auto winnerName = _playerModelsService->playerNameById(model->winnerId());
    auto json = _playerModelsJsonService->assembleJsonByPlayerIdAndName(model->winnerId(),winnerName);
    emit sendDartsTournamentWinnerIdAndName(json);
}

LocalModelsService *LocalModelsService::setDartsPointsJsonService(PointModelsJsonService *newDartsPointsJsonService)
{
    _dartsPointsJsonService = newDartsPointsJsonService;
    return this;
}

LocalModelsService *LocalModelsService::setPlayerModelsJsonService(PlayerModelsJsonService *newPlayerModelsJsonService)
{
    _playerModelsJsonService = newPlayerModelsJsonService;
    return this;
}

LocalModelsService *LocalModelsService::setDartsScoresJsonService(ScoreModelsJsonService *newDartsScoresJsonService)
{
    _dartsScoresJsonService = newDartsScoresJsonService;
    return this;
}

LocalModelsService *LocalModelsService::setPointModelsJsonService(PointModelsJsonService *newPointModelsJsonService)
{
    _dartsPointsJsonService = newPointModelsJsonService;
    return this;
}

LocalModelsService *LocalModelsService::setInputModelsScountervice(InputModelsCountService *newInputModelsScountervice)
{
    _inputModelsScountervice = newInputModelsScountervice;
    return this;
}

LocalModelsService *LocalModelsService::setSortPointInputsByIndexes(Predicate *newSortPointInputsByIndexes)
{
    _sortPointInputsByIndexes = newSortPointInputsByIndexes;
    return this;
}

LocalModelsService *LocalModelsService::setInputModelsSortService(SortDartsInputsByPredicateService *newSortInputModelsService)
{
    _inputModelsSortService = newSortInputModelsService;
    return this;
}

LocalModelsService *LocalModelsService::setGetInputModelsService(GetInputModelsService *newGetInputModelsService)
{
    _getInputModelsService = newGetInputModelsService;
    return this;
}

LocalModelsService *LocalModelsService::setDbManipulatorService(DbServiceManipulator *newDbManipulatorService)
{
    _dbManipulatorService = newDbManipulatorService;
    return this;
}

LocalModelsService* LocalModelsService::setDartsScoreInputDb(IDartsScoreDb *newDartsScoreInputDb)
{
    _dartsScoreInputDb = newDartsScoreInputDb;
    return this;
}

LocalModelsService *LocalModelsService::setDartsPointInputDb(IDartsPointDb *newDartsPointInputDb)
{
    _dartsPointInputDb = newDartsPointInputDb;
    return this;
}

LocalModelsService *LocalModelsService::setDartsPointInputService(IDartsPointModelsService<IDartsPointDb> *newDartsPointInputService)
{
    _dartsPointInputService = newDartsPointInputService;
    return this;
}

LocalModelsService *LocalModelsService::setDartsScoreInputModelsService(DartsScoreModelsService *service)
{
    _dartsScoreInputService = service;
    return this;
}

LocalModelsService *LocalModelsService::setDartsTournamentBuilder(DartsTournamentBuilder *newDartsTournamentBuilder)
{
    _dartsTournamentBuilder = newDartsTournamentBuilder;
    return this;
}

LocalModelsService *LocalModelsService::setAddPlayerNameToDartsInputModel(IBinaryService<const IModel<QUuid,QByteArray>*,
                       const QString &,
                       const IModel<QUuid,QByteArray>*> *service)
{
    _addPlayerNameToDartsInputModel = service;
    return this;
}

LocalModelsService *LocalModelsService::setDartsJsonService(IDartsJsonService *dartsJsonService)
{
    _dartsJsonService = dartsJsonService;
    return this;
}

void LocalModelsService::assembleAssignedPlayerPoints(const QUuid& tournamentId)
{
    auto models = _getInputModelsService->inputModelsByTournamentId(tournamentId,_dartsPointInputDb);
    auto json = _dartsPointsJsonService->assembleJsonFromTournamentDartsPoints(models);
    emit sendTournamentDartsPointsAsJson(json);
}


void LocalModelsService::assembleAssignedPlayerScores(const QUuid &tournamentId)
{
    auto models = _getInputModelsService->inputModelsByHint(tournamentId,DisplayHint,_dartsScoreInputDb);
    auto json = _dartsScoresJsonService->assembleJsonFromDartsMultiAttemptScores(models);
    emit sendTournamentDartsScoresAsJson(json);
}


void LocalModelsService::assembleDartsScoreIndexes(const QUuid &tournament)
{
    auto dartsTournament =_dartsModelsService->dartsTournamentModelById(tournament);
    auto playersCount = dartsTournament->assignedPlayerIdentities().count();
    auto indexes = _dartsScoreInputService->dartsScoreIndexes(tournament,playersCount,_dartsScoreInputDb);
    auto json = _dartsScoresJsonService->assembleJsonDartsScoreIndexes(indexes);
    emit sendDartsScoreIndexesAsJson(json);
}
