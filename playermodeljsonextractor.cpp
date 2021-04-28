#include "playermodeljsonextractor.h"

QVector<const IModel<QUuid> *> PlayerModelJsonExtractor::extractPlayerModelsFromJsonArray(const QJsonArray &arr)
{
    QVector<const IModel<QUuid>*> playerModels;
    for (auto i = arr.begin();i != arr.end();i++) {
        auto JSONValue = *i;
        auto stringID = JSONValue["Id"].toString();
        auto playerId = QUuid::fromString(stringID);
        auto playerName = JSONValue["UserName"].toString();
        auto mail = JSONValue["Mail"].toString();
        auto model = PlayerModel::createInstance()
                ->setId(playerId)
                ->setUserName(playerName)
                ->setEmail(mail);
        playerModels.append(model);
    }
    return playerModels;
}
