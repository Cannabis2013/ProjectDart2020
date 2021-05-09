#include "dartsmodelsjsonservice.h"



DartsModelsJsonService *DartsModelsJsonService::createInstance()
{
    return new DartsModelsJsonService;
}

const IDartsTournament *DartsModelsJsonService::assembleDartsTournamentFromJson(const QByteArray& json) const
{
    auto model = _assembleDartsTournamentFromJson->service(json);
    return model;
}

QVector<int> DartsModelsJsonService::getPlayerIndexesFromJson(const QByteArray& json) const
{
    auto indexes = _getPlayerIndexesFromJson->service(json);
    return indexes;
}

QByteArray DartsModelsJsonService::assembleJsonDartsIndexes(const IDartsPointIndexes *indexes) const
{
    auto json = _assembleJsonDartsIndexes->service(indexes);
    return json;
}

QByteArray DartsModelsJsonService::assembleJsonFromPlayerNamesAndIds(const QVector<QUuid> &playerIds, const QVector<QString> &playerNames) const
{
    auto json =  _assembleJsonFromPlayerNamesAndIds->service(playerIds,playerNames);
    return json;
}

QByteArray DartsModelsJsonService::assembleJsonFromTournamentDartsPoints(const QUuid &tournamentId, const IDartsModelsService *dartsModelsService) const
{
    auto json = _assembleJsonFromTournamentDartsPoints->service(tournamentId,dartsModelsService);
    return json;
}

QJsonArray DartsModelsJsonService::jsonArrayFromDartsScores(const QUuid &tournamentId, const IDartsModelsService *dartsModelsService) const
{
    auto jsonArray = _jsonArrayFromDartsScores->service(tournamentId,dartsModelsService);
    return jsonArray;
}

QByteArray DartsModelsJsonService::assembleJsonOrderedDartsPointModels(const QVector<const IDartsPointInput *> &pointModels, const IPlayerModelsService *playerModelsService) const
{
    auto json = _assembleJsonOrderedDartsPointModels->service(pointModels,playerModelsService);
    return json;
}

QByteArray DartsModelsJsonService::assembleJsonDartsTournamentModel(const IDartsTournament *model, const IPlayerModelsService *playerModelsService) const
{
    auto json = _assembleJsonDartsTournamentModel->service(model,playerModelsService);
    return json;
}

QByteArray DartsModelsJsonService::assembleJsonDartsTournamentModels(const IDartsModelsService *dartsModelsService, const IPlayerModelsService *iplayerModelsService) const
{
    auto json = _assembleJsonDartsTournamentModels->service(dartsModelsService,iplayerModelsService);
    return json;
}

QByteArray DartsModelsJsonService::assembleJsonFromDartsIndexesAndPoints(const IDartsModelsService *dartsModelsService, const IPlayerModelsService *playerModelsService) const
{
    auto json = _assembleJsonFromDartsIndexesAndPoints->service(dartsModelsService,playerModelsService);
    return json;
}

QByteArray DartsModelsJsonService::assembleJsonFromPlayerIdAndName(const QUuid &playerId, const QString &playerName) const
{
    auto json = _assembleJsonFromPlayerIdAndName->service(playerId,playerName);
    return json;
}

QByteArray DartsModelsJsonService::assembleJsonFromDartsTournamentModel(const IDartsTournament *model) const
{
    auto json = _assembleJSonFromDartsTournamentModel->service(model);
    return json;
}

QVector<int> DartsModelsJsonService::getDeleteTournamentIndexesFromJson(const QByteArray &json) const
{
    auto indexes = _getDeleteTournamentIndexesFromJson->service(json);
    return indexes;
}

int DartsModelsJsonService::getDeletePlayerIndexFromJson(const QByteArray &json) const
{
    auto index = _getDeletePlayerIndexFromJson->service(json);
    return index;
}

const IDartsPointInput *DartsModelsJsonService::assembleDartsPointModelFromJson(const QByteArray &json) const
{
    auto model = _assembleDartsPointModelFromJson->service(json);
    return model;
}

const IPlayerModel *DartsModelsJsonService::assemblePlayerModelFromJson(const QByteArray &json) const
{
    auto model = _assemblePlayerModelFromJson->service(json);
    return model;
}

const IDartsTournament *DartsModelsJsonService::assignPlayerIdsToDartsTournament(const IDartsTournament *model, const QVector<QUuid> &playerIds) const
{
    auto tournamentModel = _assignPlayerIdsToDartsTournament->service(model,playerIds);
    return tournamentModel;
}

QByteArray DartsModelsJsonService::addPlayerNameToJsonPointModel(const QByteArray &json, const IPlayerModelsService *playerModelsService) const
{
    auto newJson = _addPlayerNameToJsonPointModel->service(json,playerModelsService);
    return newJson;
}

DartsModelsJsonService* DartsModelsJsonService::setAddPlayerNameToJsonPointModel(IBinaryService<const QByteArray &, const IPlayerModelsService *, QByteArray> *addPlayerNameToJsonPointModel)
{
    _addPlayerNameToJsonPointModel = addPlayerNameToJsonPointModel;
    return this;
}

DartsModelsJsonService* DartsModelsJsonService::setAssignPlayerIdsToDartsTournament(IBinaryService<const IDartsTournament *, const QVector<QUuid> &, const IDartsTournament *> *assignPlayerIdsToDartsTournament)
{
    _assignPlayerIdsToDartsTournament = assignPlayerIdsToDartsTournament;
    return this;
}

DartsModelsJsonService* DartsModelsJsonService::setAssemblePlayerModelFromJson(IUnaryService<const QByteArray &, const IPlayerModel *> *assemblePlayerModelFromJson)
{
    _assemblePlayerModelFromJson = assemblePlayerModelFromJson;
    return this;
}

DartsModelsJsonService* DartsModelsJsonService::setAssembleDartsPointModelFromJson(IUnaryService<const QByteArray &, const IDartsPointInput *> *assembleDartsPointModelFromJson)
{
    _assembleDartsPointModelFromJson = assembleDartsPointModelFromJson;
    return this;
}

DartsModelsJsonService* DartsModelsJsonService::setGetDeletePlayerIndexFromJson(IUnaryService<const QByteArray &, int> *getDeletePlayerIndexFromJson)
{
    _getDeletePlayerIndexFromJson = getDeletePlayerIndexFromJson;
    return this;
}

DartsModelsJsonService* DartsModelsJsonService::setGetDeleteTournamentIndexesFromJson(IUnaryService<const QByteArray &, QVector<int> > *getDeleteTournamentIndexesFromJson)
{
    _getDeleteTournamentIndexesFromJson = getDeleteTournamentIndexesFromJson;
    return this;
}

DartsModelsJsonService* DartsModelsJsonService::setAssembleJSonFromDartsTournamentModel(IUnaryService<const IDartsTournament *, QByteArray> *assembleJSonFromDartsTournamentModel)
{
    _assembleJSonFromDartsTournamentModel = assembleJSonFromDartsTournamentModel;
    return this;
}

DartsModelsJsonService* DartsModelsJsonService::setAssembleJsonFromPlayerIdAndName(IBinaryService<const QUuid &, const QString &, QByteArray> *assembleJsonFromPlayerIdAndName)
{
    _assembleJsonFromPlayerIdAndName = assembleJsonFromPlayerIdAndName;
    return this;
}

DartsModelsJsonService* DartsModelsJsonService::setAssembleJsonFromDartsIndexesAndPoints(IBinaryService<const IDartsModelsService *, const IPlayerModelsService *, const QByteArray> *assembleJsonFromDartsIndexesAndPoints)
{
    _assembleJsonFromDartsIndexesAndPoints = assembleJsonFromDartsIndexesAndPoints;
    return this;
}

DartsModelsJsonService* DartsModelsJsonService::setAssembleJsonDartsTournamentModels(IBinaryService<const IDartsModelsService *, const IPlayerModelsService *, const QByteArray> *assembleJsonDartsTournamentModels)
{
    _assembleJsonDartsTournamentModels = assembleJsonDartsTournamentModels;
    return this;
}

DartsModelsJsonService* DartsModelsJsonService::setAssembleJsonDartsTournamentModel(IBinaryService<const IDartsTournament *, const IPlayerModelsService *, QByteArray> *assembleJsonDartsTournamentModel)
{
    _assembleJsonDartsTournamentModel = assembleJsonDartsTournamentModel;
    return this;
}

DartsModelsJsonService* DartsModelsJsonService::setAssembleJsonOrderedDartsPointModels(IBinaryService<const QVector<const IDartsPointInput *> &, const IPlayerModelsService *, const QByteArray> *assembleJsonOrderedDartsPointModels)
{
    _assembleJsonOrderedDartsPointModels = assembleJsonOrderedDartsPointModels;
    return this;
}

DartsModelsJsonService* DartsModelsJsonService::setJsonArrayFromDartsScores(IBinaryService<const QUuid &, const IDartsModelsService *, QJsonArray> *jsonArrayFromDartsScores)
{
    _jsonArrayFromDartsScores = jsonArrayFromDartsScores;
    return this;
}

DartsModelsJsonService* DartsModelsJsonService::setAssembleJsonFromTournamentDartsPoints(IBinaryService<const QUuid &, const IDartsModelsService *, QByteArray> *assembleJsonFromTournamentDartsPoints)
{
    _assembleJsonFromTournamentDartsPoints = assembleJsonFromTournamentDartsPoints;
    return this;
}

DartsModelsJsonService* DartsModelsJsonService::setAssembleJsonFromPlayerNamesAndIds(IBinaryService<const QVector<QUuid> &, const QVector<QString> &, QByteArray> *assembleJsonFromPlayerNamesAndIds)
{
    _assembleJsonFromPlayerNamesAndIds = assembleJsonFromPlayerNamesAndIds;
    return this;
}

DartsModelsJsonService* DartsModelsJsonService::setAssembleJsonDartsIndexes(IUnaryService<const IDartsPointIndexes *, QByteArray> *assembleJsonDartsIndexes)
{
    _assembleJsonDartsIndexes = assembleJsonDartsIndexes;
    return this;
}

DartsModelsJsonService* DartsModelsJsonService::setGetPlayerIndexesFromJson(IUnaryService<const QByteArray &, QVector<int> > *getPlayerIndexesFromJson)
{
    _getPlayerIndexesFromJson = getPlayerIndexesFromJson;
    return this;
}

DartsModelsJsonService* DartsModelsJsonService::setAssembleDartsTournamentFromJson(IUnaryService<const QByteArray &, const IDartsTournament *> *assembleDartsTournamentFromJson)
{
    _assembleDartsTournamentFromJson = assembleDartsTournamentFromJson;
    return this;
}


QByteArray DartsModelsJsonService::assembleJsonFromDartsPointModel(const IDartsPointInput* model) const
{
    auto json = _assembleJsonFromDartsPointModel->service(model);
    return json;
}

DartsModelsJsonService *DartsModelsJsonService::setAssembleJsonFromDartsPointModel(IUnaryService<const IDartsPointInput *, QByteArray> *assembleJsonFromDartsPointModel)
{
    _assembleJsonFromDartsPointModel = assembleJsonFromDartsPointModel;
    return this;
}
