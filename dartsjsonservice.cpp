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

QVector<int> DartsJsonService::getPlayerIndexesFromJson(const QByteArray& json) const
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

QByteArray DartsJsonService::assembleJsonFromTournamentDartsPoints(const QUuid &tournamentId, const IDartsModelsService *dartsModelsService) const
{
    auto json = _assembleJsonFromTournamentDartsPoints->service(tournamentId,dartsModelsService);
    return json;
}

QJsonArray DartsJsonService::jsonArrayFromDartsScores(const QUuid &tournamentId, const IDartsModelsService *dartsModelsService) const
{
    auto jsonArray = _jsonArrayFromDartsScores->service(tournamentId,dartsModelsService);
    return jsonArray;
}

QByteArray DartsJsonService::assembleJsonOrderedDartsPointModels(const QVector<const IDartsPointInput *> &pointModels, const IPlayerModelsService *playerModelsService) const
{
    auto json = _assembleJsonOrderedDartsPointModels->service(pointModels,playerModelsService);
    return json;
}

QByteArray DartsJsonService::assembleJsonDartsTournamentModel(const IDartsTournament *model, const IPlayerModelsService *playerModelsService) const
{
    auto json = _assembleJsonDartsTournamentModel->service(model,playerModelsService);
    return json;
}

QByteArray DartsJsonService::assembleJsonDartsTournamentModels(const IDartsModelsService *dartsModelsService, const IPlayerModelsService *iplayerModelsService) const
{
    auto json = _assembleJsonDartsTournamentModels->service(dartsModelsService,iplayerModelsService);
    return json;
}

QByteArray DartsJsonService::assembleJsonFromPlayerIdAndName(const QUuid &playerId, const QString &playerName) const
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

const IDartsPointInput *DartsJsonService::assembleDartsPointModelFromJson(const QByteArray &json) const
{
    auto model = _assembleDartsPointModelFromJson->service(json);
    return model;
}

const IPlayerModel *DartsJsonService::assemblePlayerModelFromJson(const QByteArray &json) const
{
    auto model = _assemblePlayerModelFromJson->service(json);
    return model;
}

const IDartsTournament *DartsJsonService::assignPlayerIdsToDartsTournament(const IDartsTournament *model, const QVector<QUuid> &playerIds) const
{
    auto tournamentModel = _assignPlayerIdsToDartsTournament->service(model,playerIds);
    return tournamentModel;
}

QByteArray DartsJsonService::addPlayerNameToJsonInputModel(const QByteArray &json, const IPlayerModelsService *playerModelsService) const
{
    auto newJson = _addPlayerNameToJsonInputModel->service(json,playerModelsService);
    return newJson;
}

DartsJsonService* DartsJsonService::setAddPlayerNameToJsonPointModel(IBinaryService<const QByteArray &, const IPlayerModelsService *, QByteArray> *addPlayerNameToJsonPointModel)
{
    _addPlayerNameToJsonInputModel = addPlayerNameToJsonPointModel;
    return this;
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

DartsJsonService* DartsJsonService::setAssembleDartsPointModelFromJson(IUnaryService<const QByteArray &, const IDartsPointInput *> *assembleDartsPointModelFromJson)
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

DartsJsonService* DartsJsonService::setAssembleJsonDartsTournamentModel(IBinaryService<const IDartsTournament *, const IPlayerModelsService *, QByteArray> *assembleJsonDartsTournamentModel)
{
    _assembleJsonDartsTournamentModel = assembleJsonDartsTournamentModel;
    return this;
}

DartsJsonService* DartsJsonService::setAssembleJsonOrderedDartsPointModels(IBinaryService<const QVector<const IDartsPointInput *> &, const IPlayerModelsService *, const QByteArray> *assembleJsonOrderedDartsPointModels)
{
    _assembleJsonOrderedDartsPointModels = assembleJsonOrderedDartsPointModels;
    return this;
}

DartsJsonService* DartsJsonService::setJsonArrayFromDartsScores(IBinaryService<const QUuid &, const IDartsModelsService *, QJsonArray> *jsonArrayFromDartsScores)
{
    _jsonArrayFromDartsScores = jsonArrayFromDartsScores;
    return this;
}

DartsJsonService* DartsJsonService::setAssembleJsonFromTournamentDartsPoints(IBinaryService<const QUuid &, const IDartsModelsService *, QByteArray> *assembleJsonFromTournamentDartsPoints)
{
    _assembleJsonFromTournamentDartsPoints = assembleJsonFromTournamentDartsPoints;
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


QByteArray DartsJsonService::assembleJsonFromDartsPointModel(const IDartsPointInput* model) const
{
    auto json = _assembleJsonFromDartsPointModel->service(model);
    return json;
}

const IDartsScoreInput *DartsJsonService::assembleDartsScoreModelFromJson(const QByteArray& json) const
{
    auto model = _assembleDartsScoreFromJson->service(json);
    return model;
}

DartsJsonService *DartsJsonService::setAssembleJsonFromDartsPointModel(IUnaryService<const IDartsPointInput *, QByteArray> *assembleJsonFromDartsPointModel)
{
    _assembleJsonFromDartsPointModel = assembleJsonFromDartsPointModel;
    return this;
}

DartsJsonService *DartsJsonService::setAssembleDartsScoreFromJson(IUnaryService<const QByteArray &, const IDartsScoreInput *> *assembleDartsScoreFromJson)
{
    _assembleDartsScoreFromJson = assembleDartsScoreFromJson;
    return this;
}

DartsJsonService *DartsJsonService::setAssembleJsonFromDartsScoreModel(IUnaryService<const IDartsScoreInput *, QByteArray> *assembleJsonFromDartsScoreModel)
{
    _assembleJsonFromDartsScoreModel = assembleJsonFromDartsScoreModel;
    return this;
}

DartsJsonService *DartsJsonService::setAssembleJsonFromDartsMultiAttemptScores(IUnaryService<const QVector<const IDartsScoreInput*>&,QByteArray> *assembleJsonFromDartsMultiAttemptScores)
{
    _assembleJsonFromDartsMultiAttemptScores = assembleJsonFromDartsMultiAttemptScores;
    return this;
}

DartsJsonService *DartsJsonService::setAssembleJsonByDartsScoreIndexes(IUnaryService<const IDartsScoreIndexes *, QByteArray> *assembleJsonByDartsScoreIndexes)
{
    _assembleJsonByDartsScoreIndexes = assembleJsonByDartsScoreIndexes;
    return this;
}


QByteArray DartsJsonService::assembleJsonFromDartsScoreModel(const IDartsScoreInput *model) const
{
    auto json = _assembleJsonFromDartsScoreModel->service(model);
    return json;
}


QByteArray DartsJsonService::assembleJsonFromDartsMultiAttemptScores(const QVector<const IDartsScoreInput*>& models) const
{
    auto json = _assembleJsonFromDartsMultiAttemptScores->service(models);
    return json;
}
