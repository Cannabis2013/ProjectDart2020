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
    auto model = _dartsModelsService->getDartsTournamentById(tournamentId);
    auto json = _assembleJSonFromDartsTournamentModel->service(model);
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

LocalModelsService* LocalModelsService::setAssembleJSonFromTournamentDartsPoints(IBinaryService<const QUuid &, const IDartsModelsService *, QByteArray> *JsonArrayFromDartsPoints)
{
    _assembleJSonFromTournamentDartsPoints = JsonArrayFromDartsPoints;
    return this;
}

LocalModelsService* LocalModelsService::setGetPlayerIndexesFromJson(IUnaryService<const QByteArray &, QVector<int> > *getPlayerIndexesFromJson)
{
    _getPlayerIndexesFromJson = getPlayerIndexesFromJson;
    return this;
}

LocalModelsService* LocalModelsService::setPlayerModelsService(IPlayerModelsService<IPlayerModel<QUuid,QString>> *playerModelsContext)
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
    auto json = _assembleJSonFromTournamentDartsPoints->service(tournamentId,_dartsModelsService);
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

LocalModelsService *LocalModelsService::setAssembleDartsPointModelFromJson(IUnaryService<const QByteArray &, const IDartsPointInput<QUuid> *> *assembleDartsPointModelFromJson)
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

LocalModelsService *LocalModelsService::setAssembleJSonFromDartsTournamentModel(IUnaryService<const IDartsTournament<QUuid, QString> *, QByteArray> *assembleJSonFromDartsTournamentModel)
{
    _assembleJSonFromDartsTournamentModel = assembleJSonFromDartsTournamentModel;
    return this;
}

LocalModelsService* LocalModelsService::setAssembleJsonFromPlayerIdAndName(IBinaryService<const QUuid &, const QString &, QByteArray> *assembleJsonFromPlayerIdAndName)
{
    _assembleJsonFromPlayerIdAndName = assembleJsonFromPlayerIdAndName;
    return this;
}
