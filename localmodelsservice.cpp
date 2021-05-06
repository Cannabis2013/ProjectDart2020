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
    _dartsModelsService->addDartsTournamentToDb(model);
    auto indexes = _getPlayerIndexesFromJson->service(json);
    auto playersIds = _playerModelsService->assemblePlayerIds(indexes);
    _dartsModelsService->tournamentAssignPlayers(model->id(),playersIds);
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
    QVector<int> indexes;
    auto obj = QJsonDocument::fromJson(json).object();
    auto arr = obj.value("Indexes").toArray();
    for (auto jsonValue : arr) {
        auto index = jsonValue.toInt();
        indexes << index;
    }
    auto status = _dartsModelsService->removeTournamentsByIndexes(indexes);
    emit tournamentsDeletedStatus(status);
}

void LocalModelsService::getOrderedDartsPoints(const QUuid &tournamentId)
{
    auto orderedDartsPointModels = _dartsModelsService->getDartsPointModelsOrdedByIndexes(tournamentId);
    auto json = _assembleJsonOrderedDartsPointModels->service(orderedDartsPointModels,_playerModelsService);
    emit sendFtpMultiScores(json);
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
    auto model = _dartsModelsService->assembleDartsInputPointFromJson(json);
    _dartsModelsService->addDartsPoint(model);
    auto playerName = _playerModelsService->playerNameFromId(model->playerId());
    emit scoreAddedToDataContext(json);
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
    QJsonObject obj;
    obj["tournamentId"] = tournamentId.toString(QUuid::WithoutBraces);
    obj["gameMode"] = _dartsModelsService->tournamentGameMode(tournamentId);
    obj["attempts"] = _dartsModelsService->tournamentAttempts(tournamentId);
    obj["keyPoint"] = _dartsModelsService->tournamentKeyPoint(tournamentId);
    obj["terminalKeyCode"] = _dartsModelsService->tournamentTerminalKeyCode(tournamentId);
    obj["inputHint"] = _dartsModelsService->tournamentInputMode(tournamentId);
    auto winnerId = _dartsModelsService->tournamentWinnerId(tournamentId);
    obj["winnerId"] = winnerId.toString(QUuid::WithoutBraces);
    auto json = QJsonDocument(obj).toJson();
    emit sendTournamentFtpDetails(json);
}

void LocalModelsService::createPlayer(const QByteArray &json)
{
    auto playerModel = _playerModelsService->createPlayerFromJson(json);
    _playerModelsService->addPlayerModelToDb(playerModel);
    emit createPlayerResponse(true);
}

void LocalModelsService::deletePlayerFromIndex(const QByteArray &json)
{
    auto jsonObject = QJsonDocument::fromJson(json).object();
    auto index = jsonObject.value("index").toInt();
    auto status = _playerModelsService->deletePlayer(index);
    emit playersDeletedStatus(status);
}

void LocalModelsService::deletePlayersFromIndexes(const QByteArray &json)
{
    auto jsonArray = QJsonDocument::fromJson(json).array();
    QVector<int> indexes;
    for (auto i = jsonArray.constBegin(); i != jsonArray.constEnd(); ++i) {
        auto index = (*i).toInt();
        indexes << index;
    }
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

void LocalModelsService::setAssembleJSonFromTournamentDartsPoints(IBinaryService<const QUuid &, const IDartsModelsService *, QByteArray> *JsonArrayFromDartsPoints)
{
    _assembleJSonFromTournamentDartsPoints = JsonArrayFromDartsPoints;
}

void LocalModelsService::setGetPlayerIndexesFromJson(IUnaryService<const QByteArray &, QVector<int> > *getPlayerIndexesFromJson)
{
    _getPlayerIndexesFromJson = getPlayerIndexesFromJson;
}

void LocalModelsService::setPlayerModelsService(IPlayerModelsService<IPlayerModel<QUuid,QString>> *playerModelsContext)
{
    _playerModelsService = playerModelsContext;
}

void LocalModelsService::setDartsModelsService(IDartsModelsService *dartsModelsService)
{
    _dartsModelsService = dartsModelsService;
}

LocalModelsService* LocalModelsService::setAssembleDartsTournamentFromJson(IUnaryService<const QByteArray &,
                                                                           const IDartsTournament<QUuid, QString> *> *assembleDartsTournamentFromJson)
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

void LocalModelsService::assembleDartsIndexesAndScores(const QUuid &tournament)
{
    /*
    auto indexes = _dartsModelsService->dartsIndexes(tournament);
    QJsonObject obj;
    obj["indexes"] = _assembleJsonDartsIndexes->service(indexes);
    auto playerIds = _dartsModelsService->tournamentAssignedPlayers(tournament);
    auto playerNames = _playerModelsService->assemblePlayerNamesFromIds(playerIds);
    obj["playerEntities"] = _JsonArrayPlayerNamesAndIds->service(playerIds,playerNames);
    obj["scoreEntities"] = _JsonArrayFromDartsScores->service(tournament,_dartsModelsService);
    emit sendDartsIndexesAndScoreValues(QJsonDocument(obj).toJson());
    */
}

void LocalModelsService::assembleDartsTournamentDataFromId(const QUuid &tournamentId)
{
    auto dartsTournamentModel = _dartsModelsService->getDartsTournamentById(tournamentId);
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
                                                                             const IPlayerModelsService<IPlayerModel<QUuid,QString>> *,
                                                                             const QByteArray> *assembleJsonDartsTournamentModels)
{
    _assembleJsonDartsTournamentModels = assembleJsonDartsTournamentModels;
    return this;
}

LocalModelsService* LocalModelsService::setAssembleJsonFromDartsTournamentModel(
        IBinaryService<const IDartsTournament<QUuid, QString> *,
        const IPlayerModelsService<IPlayerModel<QUuid,QString>> *,
        const QByteArray> *assembleJsonFromDartsTournamentModel)
{
    _assembleJsonDartsTournamentModel = assembleJsonFromDartsTournamentModel;
    return this;
}

LocalModelsService* LocalModelsService::setAssembleJsonFromOrderedDartsPointModels(
        IBinaryService<const QVector<const IDartsPointInput<QUuid>*>&,
        const IPlayerModelsService<IPlayerModel<QUuid,QString>> *,
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
    QJsonObject obj;
    auto json = _assembleJSonFromTournamentDartsPoints->service(tournamentId,_dartsModelsService);
    emit sendTournamentDartsPointsAsJson(json);
}

void LocalModelsService::setAssembleJsonFromPlayerNamesAndIds(IBinaryService<const QVector<QUuid> &, const QVector<QString> &, QByteArray> *assembleJsonFromPlayerNamesAndIds)
{
    _assembleJsonFromPlayerNamesAndIds = assembleJsonFromPlayerNamesAndIds;
}

void LocalModelsService::setAssembleJsonDartsIndexes(IUnaryService<const IDartsPointIndexes *, QByteArray> *assembleJsonDartsIndexes)
{
    _assembleJsonDartsIndexes = assembleJsonDartsIndexes;
}

void LocalModelsService::assembleDartsTournamentWinnerIdAndName(const QUuid& tournamentId)
{
    auto winnerId = _dartsModelsService->tournamentWinnerId(tournamentId);
    auto winnerName = _playerModelsService->playerNameFromId(winnerId);
    auto json = _assembleJsonFromPlayerIdAndName->service(winnerId,winnerName);
    emit sendDartsTournamentWinnerIdAndName(json);
}

LocalModelsService* LocalModelsService::setAssembleJsonFromPlayerIdAndName(IBinaryService<const QUuid &, const QString &, QByteArray> *assembleJsonFromPlayerIdAndName)
{
    _assembleJsonFromPlayerIdAndName = assembleJsonFromPlayerIdAndName;
    return this;
}
