#include "playermodelsjsonextractor.h"

PlayerModelsJsonExtractor *PlayerModelsJsonExtractor::createInstance()
{
    return new PlayerModelsJsonExtractor;
}

QVector<const DartsModelsContext::IPlayerModel *> PlayerModelsJsonExtractor::service(const QJsonArray &arr)
{
    QVector<const DartsModelsContext::IPlayerModel*> playerModels;
    for (auto i = arr.begin();i != arr.end();i++) {
        auto JSONValue = *i;
        auto stringID = JSONValue["Id"].toString();
        auto playerId = QUuid::fromString(stringID);
        auto playerName = JSONValue["UserName"].toString();
        auto mail = JSONValue["Mail"].toString();
        auto model = DartsModelsContext::PlayerModel::createInstance()
                ->setId(playerId)
                ->setUserName(playerName)
                ->setEmail(mail);
        playerModels.append(model);
    }
    return playerModels;
}
