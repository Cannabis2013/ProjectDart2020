#include "dartsjsonservice.h"

using namespace DartsModelsContext;

DartsJsonService *DartsJsonService::createInstance()
{
    return new DartsJsonService;
}

const IDartsTournament *DartsJsonService::assembleDartsTournamentFromJson(const QByteArray& json) const
{
    auto model = _assembleDartsTournamentFromJson->service(json);
    return model;
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

QByteArray DartsJsonService::assembleJsonByDartsTournamentModel(const IDartsTournament *model) const
{
    auto json = _assembleJsonFromDartsTournamentModel->service(model);
    return json;
}

QVector<int> DartsJsonService::getDeleteTournamentIndexesFromJson(const QByteArray &json) const
{
    auto indexes = _getDeleteTournamentIndexesFromJson->service(json);
    return indexes;
}

DartsJsonService* DartsJsonService::setAssignPlayerIdsToDartsTournament(IBinaryService<const IDartsTournament *, const QVector<QUuid> &, const IDartsTournament *> *assignPlayerIdsToDartsTournament)
{
    _assignPlayerIdsToDartsTournament = assignPlayerIdsToDartsTournament;
    return this;
}

DartsJsonService* DartsJsonService::setGetDeleteTournamentIndexesFromJson(IUnaryService<const QByteArray &, QVector<int> > *getDeleteTournamentIndexesFromJson)
{
    _getDeleteTournamentIndexesFromJson = getDeleteTournamentIndexesFromJson;
    return this;
}

DartsJsonService* DartsJsonService::setAssembleJSonFromDartsTournamentModel(IUnaryService<const IDartsTournament *, QByteArray> *assembleJSonFromDartsTournamentModel)
{
    _assembleJsonFromDartsTournamentModel = assembleJSonFromDartsTournamentModel;
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

DartsJsonService* DartsJsonService::setAssembleDartsTournamentFromJson(IUnaryService<const QByteArray &, const IDartsTournament *> *assembleDartsTournamentFromJson)
{
    _assembleDartsTournamentFromJson = assembleDartsTournamentFromJson;
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

QUuid DartsJsonService::getTournamentIdByJson(const QByteArray& json) const
{
    auto tournamentId = _getTournamentIdByJson->service(json);
    return tournamentId;
}
