#include "localmodelsservice.h"

LocalModelsService::~LocalModelsService()
{
    delete _dartsModelsService;
    delete _playerModelsService;
}

LocalModelsService *LocalModelsService::createInstance()
{
    return new LocalModelsService();
}

void LocalModelsService::addDartsTournament(const QByteArray& json)
{
    auto model = _assembleDartsTournamentFromJson->service(json);
    auto indexes = _getPlayerIndexesFromJson->service(json);
    auto playerIds = _playerModelsService->assemblePlayerIds(indexes);
    auto newModel = _assignPlayerIdsToDartsTournament->service(model,playerIds);
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
    QVector<int> indexes = _getDeleteTournamentIndexesFromJson->service(json);
    auto status = _dartsModelsService->removeTournamentsByIndexes(indexes);
    emit tournamentsDeletedStatus(status);
}

void LocalModelsService::getOrderedDartsPoints(const QUuid &tournamentId)
{
    auto orderedDartsPointModels = _dartsModelsService->getDartsPointModelsOrdedByIndexes(tournamentId);
    auto json = _assembleJsonOrderedDartsPointModels->service(orderedDartsPointModels,_playerModelsService);
    emit sendDartsSingleAttemptPoints(json);
}

void LocalModelsService::handleRequestTournaments()
{
    auto json = _assembleJsonDartsTournamentModels->service(_dartsModelsService,_playerModelsService);
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
    auto model = _assembleDartsPointModelFromJson->service(json);
    _dartsModelsService->addDartsPoint(model);
    auto alteredJson = _addPlayerNameToJsonPointModel->service(json,_playerModelsService);
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
    auto json = _assembleJSonFromDartsTournamentModel->service(model);
    emit sendTournamentFtpDetails(json);
}

void LocalModelsService::createPlayer(const QByteArray &json)
{
    auto playerModel = _assemblePlayerModelFromJson->service(json);
    _playerModelsService->addPlayerModelToDb(playerModel);
    emit createPlayerResponse(true);
}

void LocalModelsService::deletePlayerFromIndex(const QByteArray &json)
{
    auto index = _getDeletePlayerIndexFromJson->service(json);
    auto status = _playerModelsService->deletePlayer(index);
    emit playersDeletedStatus(status);
}

void LocalModelsService::deletePlayersFromIndexes(const QByteArray &json)
{
    QVector<int> indexes = _getPlayerIndexesFromJson->service(json);
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

LocalModelsService* LocalModelsService::setAssembleJsonFromTournamentDartsPoints(IBinaryService<const QUuid &, const IDartsModelsService *, QByteArray> *JsonArrayFromDartsPoints)
{
    _assembleJsonFromTournamentDartsPoints = JsonArrayFromDartsPoints;
    return this;
}

LocalModelsService* LocalModelsService::setGetPlayerIndexesFromJson(IUnaryService<const QByteArray &, QVector<int> > *getPlayerIndexesFromJson)
{
    _getPlayerIndexesFromJson = getPlayerIndexesFromJson;
    return this;
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

LocalModelsService* LocalModelsService::setAssembleDartsTournamentFromJson(IUnaryService<const QByteArray &,
                                                                           const IDartsTournament *> *assembleDartsTournamentFromJson)
{
    _assembleDartsTournamentFromJson = assembleDartsTournamentFromJson;
    return this;
}

void LocalModelsService::assembleDartsPointIndexes(const QUuid &tournament)
{
    auto indexes = _dartsModelsService->dartsIndexes(tournament);
    auto json = _assembleJsonDartsIndexes->service(indexes);
    emit sendDartsPointIndexesAsJson(json);
}

void LocalModelsService::assembleDartsTournamentDataFromId(const QUuid &tournamentId)
{
    auto dartsTournamentModel = _dartsModelsService->getDartsTournamentModelById(tournamentId);
    auto json = _assembleJsonDartsTournamentModel->service(dartsTournamentModel,_playerModelsService);
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
    _dartsModelsService->setDartsPointHint(pointId,ModelDisplayHint::HiddenHint);
    // Implement json response
    emit dartsPointHiddenSucces(QByteArray());
}

void LocalModelsService::revealPoint(const QUuid &tournamentId, const QUuid &playerId, const int &roundIndex, const int &attemptIndex)
{
    QUuid pointId = _dartsModelsService->getDartsPointId(tournamentId,
                                                         playerId,
                                                         roundIndex,
                                                         attemptIndex);
    _dartsModelsService->setDartsPointHint(pointId,ModelDisplayHint::DisplayHint);
    // Implement json response
    emit dartsPointRevealedSucces(QByteArray());
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
    emit dartsScoreHiddenSucces(QByteArray());
}

void LocalModelsService::revealScore(const QUuid& tournamentId, const QUuid& playerId, const int& roundIndex)
{
    auto scoreID = _dartsModelsService->getDartsScoreId(tournamentId,
                                                        playerId,
                                                        roundIndex);
    _dartsModelsService->setDartsScoreHint(scoreID,ModelDisplayHint::DisplayHint);
    // Implement json response
    emit dartsScoreRevealedSucces(QByteArray());
}

LocalModelsService* LocalModelsService::setAssembleJsonDartsTournamentModels(IBinaryService<const IDartsModelsService *,
                                                                             const IPlayerModelsService *,
                                                                             const QByteArray> *assembleJsonDartsTournamentModels)
{
    _assembleJsonDartsTournamentModels = assembleJsonDartsTournamentModels;
    return this;
}

LocalModelsService* LocalModelsService::setAssembleJsonFromDartsTournamentModel(
        IBinaryService<const IDartsTournament *,
        const IPlayerModelsService *,
        const QByteArray> *assembleJsonFromDartsTournamentModel)
{
    _assembleJsonDartsTournamentModel = assembleJsonFromDartsTournamentModel;
    return this;
}

LocalModelsService* LocalModelsService::setAssembleJsonFromOrderedDartsPointModels(
        IBinaryService<const QVector<const IDartsPointInput<QUuid>*>&,
        const IPlayerModelsService *,
        const QByteArray> *assembleJsonFromOrderedDartsPointModels)
{
    _assembleJsonOrderedDartsPointModels = assembleJsonFromOrderedDartsPointModels;
    return this;
}


void LocalModelsService::addDartsScore(const QByteArray &json)
{
    // TODO: Implement
}


void LocalModelsService::assembleAssignedPlayerEntities(const QUuid& tournamentId)
{
    auto playerIds = _dartsModelsService->tournamentAssignedPlayers(tournamentId);
    auto playerNames = _playerModelsService->assemblePlayerNamesFromIds(playerIds);
    auto json = _assembleJsonFromPlayerNamesAndIds->service(playerIds,playerNames);
    emit sendAssignedPlayerIdsAndNamesAsJson(json);
}

void LocalModelsService::assembleAssignedPlayerPoints(const QUuid& tournamentId)
{
    auto json = _assembleJsonFromTournamentDartsPoints->service(tournamentId,_dartsModelsService);
    emit sendTournamentDartsPointsAsJson(json);
}

LocalModelsService* LocalModelsService::setAssembleJsonFromPlayerNamesAndIds(IBinaryService<const QVector<QUuid> &, const QVector<QString> &, QByteArray> *assembleJsonFromPlayerNamesAndIds)
{
    _assembleJsonFromPlayerNamesAndIds = assembleJsonFromPlayerNamesAndIds;
    return this;
}

LocalModelsService* LocalModelsService::setAssembleJsonDartsIndexes(IUnaryService<const IDartsPointIndexes *, QByteArray> *assembleJsonDartsIndexes)
{
    _assembleJsonDartsIndexes = assembleJsonDartsIndexes;
    return this;
}

void LocalModelsService::assembleDartsTournamentWinnerIdAndName(const QUuid& tournamentId)
{
    auto winnerId = _dartsModelsService->tournamentWinnerId(tournamentId);
    auto winnerName = _playerModelsService->playerNameFromId(winnerId);
    auto json = _assembleJsonFromPlayerIdAndName->service(winnerId,winnerName);
    emit sendDartsTournamentWinnerIdAndName(json);
}

LocalModelsService *LocalModelsService::setAddPlayerNameToJsonPointModel(IBinaryService<const QByteArray &, const IPlayerModelsService *, QByteArray> *addPlayerNameToJsonPointModel)
{
    _addPlayerNameToJsonPointModel = addPlayerNameToJsonPointModel;
    return this;
}

LocalModelsService *LocalModelsService::setAssignPlayerIdsToDartsTournament(AssignPlayerIdsService *assignPlayerIdsToDartsTournament)
{
    _assignPlayerIdsToDartsTournament = assignPlayerIdsToDartsTournament;
    return this;
}

LocalModelsService *LocalModelsService::setAssemblePlayerModelFromJson(
        AssemblePlayerModelService *assemblePlayerModelFromJson)
{
    _assemblePlayerModelFromJson = assemblePlayerModelFromJson;
    return this;
}

LocalModelsService *LocalModelsService::setAssembleDartsPointModelFromJson(AssembleDartsPointService *assembleDartsPointModelFromJson)
{
    _assembleDartsPointModelFromJson = assembleDartsPointModelFromJson;
    return this;
}

LocalModelsService *LocalModelsService::setGetDeletePlayerIndexFromJson(IUnaryService<const QByteArray &, int> *getDeletePlayerIndexFromJson)
{
    _getDeletePlayerIndexFromJson = getDeletePlayerIndexFromJson;
    return this;
}

LocalModelsService *LocalModelsService::setGetTournamentIndexesFromJson(IUnaryService<const QByteArray &, QVector<int> > *getTournamentIndexesFromJson)
{
    _getDeleteTournamentIndexesFromJson = getTournamentIndexesFromJson;
    return this;
}

LocalModelsService *LocalModelsService::setAssembleJSonBasicTournamentValues(IUnaryService<const IDartsTournament *, QByteArray> *assembleJSonFromDartsTournamentModel)
{
    _assembleJSonFromDartsTournamentModel = assembleJSonFromDartsTournamentModel;
    return this;
}

LocalModelsService* LocalModelsService::setAssembleJsonFromPlayerIdAndName(IBinaryService<const QUuid &, const QString &, QByteArray> *assembleJsonFromPlayerIdAndName)
{
    _assembleJsonFromPlayerIdAndName = assembleJsonFromPlayerIdAndName;
    return this;
}
