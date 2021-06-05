#include "playermodelsjsonservice.h"

using namespace DartsModelsContext;

PlayerModelsJsonService *PlayerModelsJsonService::createInstance()
{
    return new PlayerModelsJsonService;
}

QVector<int> PlayerModelsJsonService::getPlayerIndexesByJson(const JsonFormat &json) const
{
    auto indexes = _getPlayerIndexesFromJson->service(json);
    return indexes;
}

PlayerModelsJsonService::JsonFormat PlayerModelsJsonService::assembleJsonFromPlayerNamesAndIds(const QVector<IdFormat> &playerIds, const QVector<StringFormat> &playerNames) const
{
    auto json =  _assembleJsonFromPlayerNamesAndIds->service(playerIds,playerNames);
    return json;
}

PlayerModelsJsonService::JsonFormat PlayerModelsJsonService::assembleJsonByPlayerIdAndName(const IdFormat &playerId, const QString &playerName) const
{
    auto json = _assembleJsonFromPlayerIdAndName->service(playerId,playerName);
    return json;
}

int PlayerModelsJsonService::getDeletePlayerIndexFromJson(const JsonFormat &json) const
{
    auto index = _getDeletePlayerIndexFromJson->service(json);
    return index;
}

const PlayerModelsJsonService::PlayerInterface *PlayerModelsJsonService::assemblePlayerModelFromJson(const JsonFormat &json) const
{
    auto model = _assemblePlayerModelFromJson->service(json);
    return model;
}

PlayerModelsJsonService::IdFormat PlayerModelsJsonService::getWinnerIdByJson(const JsonFormat &json) const
{
    auto winnerId = _getWinnerIdByJson->service(json);
    return winnerId;
}

PlayerModelsJsonService *PlayerModelsJsonService::setGetPlayerIndexesFromJson(IUnaryService<const QByteArray &, QVector<int> > *newGetPlayerIndexesFromJson)
{
    _getPlayerIndexesFromJson = newGetPlayerIndexesFromJson;
    return this;
}

PlayerModelsJsonService *PlayerModelsJsonService::setAssembleJsonFromPlayerNamesAndIds(IBinaryService<const QVector<QUuid> &, const QVector<QString> &, QByteArray> *newAssembleJsonFromPlayerNamesAndIds)
{
    _assembleJsonFromPlayerNamesAndIds = newAssembleJsonFromPlayerNamesAndIds;
    return this;
}

PlayerModelsJsonService *PlayerModelsJsonService::setAssembleJsonFromPlayerIdAndName(IBinaryService<const QUuid &, const QString &, QByteArray> *newAssembleJsonFromPlayerIdAndName)
{
    _assembleJsonFromPlayerIdAndName = newAssembleJsonFromPlayerIdAndName;
    return this;
}

PlayerModelsJsonService *PlayerModelsJsonService::setGetDeletePlayerIndexFromJson(IUnaryService<const QByteArray &, int> *newGetDeletePlayerIndexFromJson)
{
    _getDeletePlayerIndexFromJson = newGetDeletePlayerIndexFromJson;
    return this;
}

PlayerModelsJsonService *PlayerModelsJsonService::setAssemblePlayerModelFromJson(IUnaryService<const QByteArray &, const IPlayerModel *> *newAssemblePlayerModelFromJson)
{
    _assemblePlayerModelFromJson = newAssemblePlayerModelFromJson;
    return this;
}

PlayerModelsJsonService *PlayerModelsJsonService::setGetWinnerIdByJson(IUnaryService<const QByteArray &, QUuid> *newGetWinnerIdByJson)
{
    _getWinnerIdByJson = newGetWinnerIdByJson;
    return this;
}
