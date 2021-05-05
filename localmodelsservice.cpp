#include "localmodelsservice.h"

LocalModelsService::~LocalModelsService()
{
    delete _dartsModelsService;
    delete _playerModelsService;
}

LocalModelsService *LocalModelsService::createInstance()
{
    auto dbContext = new PlayersJsonDb();
    auto dartsModelsService =
            DartsModelsService::createInstance()
            ->setAssembleDartsTournamentFromJson(new AssembleDartsTournamentModelFromJson)
            ->setGetOrderedDartsPointsModels(new GetOrderedDartsPointsModels);
    auto playerModelsService =
            LocalPlayerModelsContext::createInstance()
            ->setPlayerBuilder(new PlayerModelBuilder())
            ->setModelDBContext(dbContext)
            ->setup();
    auto modelsContext = new LocalModelsService();
    modelsContext->setDartsModelsService(dartsModelsService);
    modelsContext->setPlayerModelsService(playerModelsService);
    modelsContext->setAssembleJsonObjectFromTournamentIndexes(new AssembleJsonDartsIndexes);
    modelsContext->setGetPlayerIndexesFromJson(new AssemblePlayerIndexesFromJson);
    modelsContext->setJsonArrayFromPlayerNamesAndIds(new JsonArrayFromPlayerNamesAndIds);
    modelsContext->setJsonArrayFromDartsPoints(new JsonArrayFromDartsPoints());
    modelsContext->setAssembleJsonFromOrderedDartsPointModels(new AssembleJsonFromOrderedDartsPointModels);
    modelsContext->setAssembleDartsTournamentFromJson(new AssembleDartsTournamentModelFromJson);
    return modelsContext;
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
    auto json = _assembleJsonFromOrderedDartsPointModels->service(orderedDartsPointModels,_playerModelsService);
    emit sendFtpMultiScores(json);
}

void LocalModelsService::handleRequestTournaments()
{
    QVariantList tournaments;
    auto count = _dartsModelsService->tournamentsCount();
    for (int i = 0; i < count; ++i) {
        auto id = _dartsModelsService->tournamentIdFromIndex(i);
        auto title = _dartsModelsService->tournamentTitle(id);
        auto gameMode = _dartsModelsService->tournamentGameMode(id);
        auto playersCount = _dartsModelsService->tournamentAssignedPlayers(id).count();
        auto winnerId = _dartsModelsService->tournamentWinner(id);
        auto winnerName = _playerModelsService->playerNameFromId(winnerId);
        tournaments += {id,title,gameMode,winnerName,playersCount};
    }
    emit sendTournaments(tournaments);
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
    auto winnerId = _dartsModelsService->tournamentWinner(tournamentId);
    obj["winnerId"] = winnerId.toString(QUuid::WithoutBraces);
    auto json = QJsonDocument(obj).toJson();
    emit sendTournamentFtpDetails(json);
}

void LocalModelsService::createPlayer(const QByteArray &json)
{
    auto document = QJsonDocument::fromJson(json);
    auto jsonObject = document.object();
    auto name = jsonObject.value("playerName").toString();
    auto mail = jsonObject.value("playerMail").toString();
    try {
        _playerModelsService->playerIdFromName(name);
    }  catch (const char *msg) {
        auto id = _playerModelsService->createPlayer(name,mail);
        auto status = id != QUuid() ? true :
                                      false;
        // Notify front-end
        emit createPlayerResponse(status);
        return;
    }
    emit createPlayerResponse(false);
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

void LocalModelsService::setJsonArrayFromDartsPoints(IBinaryService<const QUuid &, const IDartsModelsService *, QJsonArray> *JsonArrayFromDartsPoints)
{
    _JsonArrayFromDartsPoints = JsonArrayFromDartsPoints;
}

void LocalModelsService::setJsonArrayFromPlayerNamesAndIds(IBinaryService<const QVector<QUuid> &, const QVector<QString> &, QJsonArray> *JsonObjectFromPlayerNamesAndIds)
{
    _JsonArrayFromPlayerNamesAndIds = JsonObjectFromPlayerNamesAndIds;
}

void LocalModelsService::setAssembleJsonObjectFromTournamentIndexes(IUnaryService<const QVector<int> &, QJsonObject> *assembleJsonObjectFromTournamentIndexes)
{
    _assembleJsonDartsIndexes = assembleJsonObjectFromTournamentIndexes;
}

void LocalModelsService::setGetPlayerIndexesFromJson(IUnaryService<const QByteArray &, QVector<int> > *getPlayerIndexesFromJson)
{
    _getPlayerIndexesFromJson = getPlayerIndexesFromJson;
}

void LocalModelsService::setPlayerModelsService(IPlayerModelsService *playerModelsContext)
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

void LocalModelsService::assembleDartsIndexesAndPoints(const QUuid &tournament)
{
    auto indexes = _dartsModelsService->dartsIndexes(tournament);
    QJsonObject obj;
    obj["indexes"] = _assembleJsonDartsIndexes->service(indexes);
    auto playerIds = _dartsModelsService->tournamentAssignedPlayers(tournament);
    auto playerNames = _playerModelsService->assemblePlayerNamesFromIds(playerIds);
    obj["playerEntities"] = _JsonArrayFromPlayerNamesAndIds->service(playerIds,playerNames);
    obj["scoreEntities"] = _JsonArrayFromDartsPoints->service(tournament,_dartsModelsService);
    emit sendDartsIndexesAndPointValues(QJsonDocument(obj).toJson());
}

void LocalModelsService::assembleDartsIndexesAndScores(const QUuid &tournament)
{
    auto indexes = _dartsModelsService->dartsIndexes(tournament);
    QJsonObject obj;
    obj["indexes"] = _assembleJsonDartsIndexes->service(indexes);
    auto playerIds = _dartsModelsService->tournamentAssignedPlayers(tournament);
    auto playerNames = _playerModelsService->assemblePlayerNamesFromIds(playerIds);
    obj["playerEntities"] = _JsonArrayFromPlayerNamesAndIds->service(playerIds,playerNames);
    obj["scoreEntities"] = _JsonArrayFromDartsScores->service(tournament,_dartsModelsService);
    emit sendDartsIndexesAndScoreValues(QJsonDocument(obj).toJson());
}

void LocalModelsService::assembleDartsTournamentDataFromId(const QUuid &tournamentId)
{
    auto dartsTournamentModel = _dartsModelsService->getDartsTournamentById(tournamentId);
    auto json = _assembleJsonFromDartsTournamentModel->service(dartsTournamentModel,_playerModelsService);
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

LocalModelsService* LocalModelsService::setAssembleJsonFromDartsTournamentModel(IBinaryService<const IDartsTournament<QUuid, QString> *, const IPlayerModelsService *, const QByteArray> *assembleJsonFromDartsTournamentModel)
{
    _assembleJsonFromDartsTournamentModel = assembleJsonFromDartsTournamentModel;
    return this;
}

LocalModelsService* LocalModelsService::setAssembleJsonFromOrderedDartsPointModels(IBinaryService<const QVector<const IDartsPointInput<QUuid>*>&, const IPlayerModelsService *, const QByteArray> *assembleJsonFromOrderedDartsPointModels)
{
    _assembleJsonFromOrderedDartsPointModels = assembleJsonFromOrderedDartsPointModels;
    return this;
}


void LocalModelsService::addDartsScore(const QByteArray &json)
{

}
