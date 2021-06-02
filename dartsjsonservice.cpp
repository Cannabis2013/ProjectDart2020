#include "dartsjsonservice.h"

DartsJsonService *DartsJsonService::createInstance()
{
    return new DartsJsonService;
}

const IDartsTournament *DartsJsonService::assembleDartsTournamentFromJson(const QByteArray& json) const
{
    auto model = _assembleDartsTournamentFromJson->service(json);
    return model;
}

QVector<int> DartsJsonService::getPlayerIndexesByJson(const QByteArray& json) const
{
    auto indexes = _getPlayerIndexesFromJson->service(json);
    return indexes;
}

QByteArray DartsJsonService::assembleJsonDartsPointIndexes(const IDartsPointIndexes *indexes) const
{
    auto json = _assembleJsonDartsPointIndexes->service(indexes);
    return json;
}

QByteArray DartsJsonService::assembleJsonDartsScoreIndexes(const IDartsScoreIndexes *indexes) const
{
    auto json = _assembleJsonByDartsScoreIndexes->service(indexes);
    return json;
}

QByteArray DartsJsonService::assembleJsonFromPlayerNamesAndIds(const QVector<QUuid> &playerIds, const QVector<QString> &playerNames) const
{
    auto json =  _assembleJsonFromPlayerNamesAndIds->service(playerIds,playerNames);
    return json;
}

QByteArray DartsJsonService::assembleJsonFromTournamentDartsPoints(const QUuid &tournamentId, const IDartsPointModelsService *dartsModelsService) const
{
    auto json = _assembleJsonFromTournamentDartsPoints->service(tournamentId,dartsModelsService);
    return json;
}

QJsonArray DartsJsonService::jsonArrayFromDartsScores(const QUuid &tournamentId, const IDartsScoreModelsService *dartsModelsService) const
{
    auto jsonArray = _jsonArrayFromDartsScores->service(tournamentId,dartsModelsService);
    return jsonArray;
}

QByteArray DartsJsonService::assembleJsonOrderedDartsPointModels(const QVector<const IDartsInput *> &pointModels,
                                                                 const IPlayerModelsService *playerModelsService) const
{
    auto json = _assembleJsonOrderedDartsPointModels->service(pointModels,playerModelsService);
    return json;
}

QByteArray DartsJsonService::addPlayerNamesToDartsTournamentJson(const QByteArray &json, const QVector<QString>& names) const
{
    auto newJson = _addPlayerNamesToTournamentJson->service(json,names);
    return newJson;
}

QByteArray DartsJsonService::addWinnerNameToDartsTournamentJson(const QByteArray &json,
                                                                const QString &name) const
{
    auto newJson = _addWinnerNameToDartsTournamentJson->service(json,name);
    return newJson;
}

QByteArray DartsJsonService::assembleJsonDartsTournamentModels(const IDartsModelsService *dartsModelsService, const IPlayerModelsService *iplayerModelsService) const
{
    auto json = _assembleJsonDartsTournamentModels->service(dartsModelsService,iplayerModelsService);
    return json;
}

QByteArray DartsJsonService::assembleJsonByPlayerIdAndName(const QUuid &playerId, const QString &playerName) const
{
    auto json = _assembleJsonFromPlayerIdAndName->service(playerId,playerName);
    return json;
}

QByteArray DartsJsonService::assembleJsonFromDartsTournamentModel(const IDartsTournament *model) const
{
    auto json = _assembleJSonFromDartsTournamentModel->service(model);
    return json;
}

QVector<int> DartsJsonService::getDeleteTournamentIndexesFromJson(const QByteArray &json) const
{
    auto indexes = _getDeleteTournamentIndexesFromJson->service(json);
    return indexes;
}

int DartsJsonService::getDeletePlayerIndexFromJson(const QByteArray &json) const
{
    auto index = _getDeletePlayerIndexFromJson->service(json);
    return index;
}

const IDartsInput *DartsJsonService::assembleDartsPointModelFromJson(const QByteArray &json) const
{
    auto model = _assembleDartsPointModelFromJson->service(json);
    return model;
}

const IPlayerModel *DartsJsonService::assemblePlayerModelFromJson(const QByteArray &json) const
{
    auto model = _assemblePlayerModelFromJson->service(json);
    return model;
}

DartsJsonService* DartsJsonService::setAssignPlayerIdsToDartsTournament(IBinaryService<const IDartsTournament *, const QVector<QUuid> &, const IDartsTournament *> *assignPlayerIdsToDartsTournament)
{
    _assignPlayerIdsToDartsTournament = assignPlayerIdsToDartsTournament;
    return this;
}

DartsJsonService* DartsJsonService::setAssemblePlayerModelFromJson(IUnaryService<const QByteArray &, const IPlayerModel *> *assemblePlayerModelFromJson)
{
    _assemblePlayerModelFromJson = assemblePlayerModelFromJson;
    return this;
}

DartsJsonService* DartsJsonService::setAssembleDartsPointModelFromJson(IUnaryService<const QByteArray &, const IDartsInput *> *assembleDartsPointModelFromJson)
{
    _assembleDartsPointModelFromJson = assembleDartsPointModelFromJson;
    return this;
}

DartsJsonService* DartsJsonService::setGetDeletePlayerIndexFromJson(IUnaryService<const QByteArray &, int> *getDeletePlayerIndexFromJson)
{
    _getDeletePlayerIndexFromJson = getDeletePlayerIndexFromJson;
    return this;
}

DartsJsonService* DartsJsonService::setGetDeleteTournamentIndexesFromJson(IUnaryService<const QByteArray &, QVector<int> > *getDeleteTournamentIndexesFromJson)
{
    _getDeleteTournamentIndexesFromJson = getDeleteTournamentIndexesFromJson;
    return this;
}

DartsJsonService* DartsJsonService::setAssembleJSonFromDartsTournamentModel(IUnaryService<const IDartsTournament *, QByteArray> *assembleJSonFromDartsTournamentModel)
{
    _assembleJSonFromDartsTournamentModel = assembleJSonFromDartsTournamentModel;
    return this;
}

DartsJsonService* DartsJsonService::setAssembleJsonFromPlayerIdAndName(IBinaryService<const QUuid &, const QString &, QByteArray> *assembleJsonFromPlayerIdAndName)
{
    _assembleJsonFromPlayerIdAndName = assembleJsonFromPlayerIdAndName;
    return this;
}

DartsJsonService* DartsJsonService::setAssembleJsonDartsTournamentModels(IBinaryService<const IDartsModelsService *, const IPlayerModelsService *, const QByteArray> *assembleJsonDartsTournamentModels)
{
    _assembleJsonDartsTournamentModels = assembleJsonDartsTournamentModels;
    return this;
}

DartsJsonService* DartsJsonService::setAddPlayerNamesToTournamentJson(IBinaryService<const QByteArray&, const QVector<QString>&, QByteArray> *assembleJsonDartsTournamentModel)
{
    _addPlayerNamesToTournamentJson = assembleJsonDartsTournamentModel;
    return this;
}

DartsJsonService* DartsJsonService::setAssembleJsonOrderedDartsPointModels(IBinaryService<const QVector<const IDartsInput *> &, const IPlayerModelsService *, const QByteArray> *assembleJsonOrderedDartsPointModels)
{
    _assembleJsonOrderedDartsPointModels = assembleJsonOrderedDartsPointModels;
    return this;
}

DartsJsonService* DartsJsonService::setJsonArrayFromDartsScores(IBinaryService<const QUuid &, const IDartsScoreModelsService *, QJsonArray> *jsonArrayFromDartsScores)
{
    _jsonArrayFromDartsScores = jsonArrayFromDartsScores;
    return this;
}

DartsJsonService* DartsJsonService::setAssembleJsonFromTournamentDartsPoints(IBinaryService<const QUuid&, const IDartsPointModelsService*, QByteArray> *service)
{
    _assembleJsonFromTournamentDartsPoints = service;
    return this;
}

DartsJsonService* DartsJsonService::setAssembleJsonFromPlayerNamesAndIds(IBinaryService<const QVector<QUuid> &, const QVector<QString> &, QByteArray> *assembleJsonFromPlayerNamesAndIds)
{
    _assembleJsonFromPlayerNamesAndIds = assembleJsonFromPlayerNamesAndIds;
    return this;
}

DartsJsonService* DartsJsonService::setAssembleJsonDartsPointIndexes(IUnaryService<const IDartsPointIndexes *, QByteArray> *assembleJsonDartsIndexes)
{
    _assembleJsonDartsPointIndexes = assembleJsonDartsIndexes;
    return this;
}

DartsJsonService* DartsJsonService::setGetPlayerIndexesFromJson(IUnaryService<const QByteArray &, QVector<int> > *getPlayerIndexesFromJson)
{
    _getPlayerIndexesFromJson = getPlayerIndexesFromJson;
    return this;
}

DartsJsonService* DartsJsonService::setAssembleDartsTournamentFromJson(IUnaryService<const QByteArray &, const IDartsTournament *> *assembleDartsTournamentFromJson)
{
    _assembleDartsTournamentFromJson = assembleDartsTournamentFromJson;
    return this;
}

DartsJsonService *DartsJsonService::setAssembleJsonFromDartsMultiAttemptScores(IUnaryService<const QVector<const IDartsInput*>&,QByteArray> *assembleJsonFromDartsMultiAttemptScores)
{
    _assembleJsonFromDartsMultiAttemptScores = assembleJsonFromDartsMultiAttemptScores;
    return this;
}

DartsJsonService *DartsJsonService::setAssembleJsonByDartsScoreIndexes(IUnaryService<const IDartsScoreIndexes *, QByteArray> *assembleJsonByDartsScoreIndexes)
{
    _assembleJsonByDartsScoreIndexes = assembleJsonByDartsScoreIndexes;
    return this;
}

DartsJsonService *DartsJsonService::setGetPlayerNameById(IBinaryService<const QUuid &, const IPlayerModelsService *, QString> *getPlayerNameById)
{
    _getPlayerNameById = getPlayerNameById;
    return this;
}

DartsJsonService *DartsJsonService::setGetWinnerIdByJson(IUnaryService<const QByteArray &, QUuid> *getWinnerIdByJson)
{
    _getWinnerIdByJson = getWinnerIdByJson;
    return this;
}

DartsJsonService *DartsJsonService::setGetTournamentIdByJson(IUnaryService<const QByteArray &, QUuid> *getTournamentIdByJson)
{
    _getTournamentIdByJson = getTournamentIdByJson;
    return this;
}

DartsJsonService *DartsJsonService::setAddWinnerNameToDartsTournamentJson(IBinaryService<const QByteArray &, const QString &, QByteArray> *newAddWinnerNameToDartsTournamentJson)
{
    _addWinnerNameToDartsTournamentJson = newAddWinnerNameToDartsTournamentJson;
    return this;
}

QByteArray DartsJsonService::assembleJsonFromDartsMultiAttemptScores(const QVector<const IDartsInput *> &models) const
{
    auto json = _assembleJsonFromDartsMultiAttemptScores->service(models);
    return json;
}

QUuid DartsJsonService::getWinnerIdByJson(const QByteArray& json) const
{
    auto winnerId = _getWinnerIdByJson->service(json);
    return winnerId;
}

QUuid DartsJsonService::getTournamentIdByJson(const QByteArray& json) const
{
    auto tournamentId = _getTournamentIdByJson->service(json);
    return tournamentId;
}
