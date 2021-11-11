#include "PlayerModelsContext/playermodelscontext.h"

void PlayerModelsContext::createPlayer(const QByteArray &json)
{
    auto playerModel = playerBuilder()->createPlayer(json);
    try {
        dbContext()->add(playerModel)->saveChanges(jsonBuilder());
    }  catch (const char *msg) {
        emit playerAddedError("Error persisting player. Err msg: " + QString::fromStdString(msg));
        return;
    }
    emit playerAddedSucces();
}

void PlayerModelsContext::deletePlayersFromIndexes(const QVector<int> &indexes)
{
    dbContext()->remove(indexes)->saveChanges(jsonBuilder());
    emit playersDeletedStatus(true);
}

void PlayerModelsContext::handleRequestPlayersDetails()
{
    auto playerModels = dbContext()->models();
    auto json = jsonBuilder()->toJson(playerModels);
    emit sendPlayers(json);
}

AbstractPlayersContext::Models PlayerModelsContext::playerModels(const QByteArray &json) const
{
    auto indexes = getIndexesFromJson(json);
    auto models = getPlayerModelsFromDb()->models(indexes,dbContext());
    return models;
}

QVector<int> PlayerModelsContext::getIndexesFromJson(const QByteArray &json) const
{
    QVector<int> indexes;
    auto obj = QJsonDocument::fromJson(json).object();
    auto arr = obj.value("playerIndexes").toArray();
    for (const auto &jsonValue : arr)
        indexes << jsonValue.toInt();
    return indexes;
}




