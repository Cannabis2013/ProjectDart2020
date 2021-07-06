#include "createplayersfromjson.h"

QVector<const DartsModelsContext::IPlayerModel*> CreatePlayersFromJson::create(const QByteArray &json) const
{
    auto arr = createArray(json);
    QVector<const DartsModelsContext::IPlayerModel*> playerModels;
    for (auto i = arr.begin();i != arr.end();i++) {
        auto JSONValue = *i;
        auto jsonObject = JSONValue.toObject();
        auto stringID = jsonObject.value("Id").toString();
        auto playerId = QUuid::fromString(stringID);
        auto playerName = jsonObject.value("UserName").toString();
        auto mail = jsonObject.value("Mail").toString();
        auto model = DartsModelsContext::PlayerModel::createInstance()
                ->setId(playerId)
                ->setUserName(playerName)
                ->setEmail(mail);
        playerModels.append(model);
    }
    return playerModels;
}

QJsonArray CreatePlayersFromJson::createArray(const QByteArray &json) const
{
    auto document = QJsonDocument::fromJson(json);
    auto arr = document.array();
    return arr;
}