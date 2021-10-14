#include "PlayerModelsContext/playermodelscontext.h"

void PlayerModelsContext::createPlayer(const QByteArray &json)
{
    auto playerModel = playerBuilder()->createPlayer(json);
    try {
        dbContext()->add(playerModel);
        dbContext()->saveChanges(jsonBuilder());
    }  catch (...) {
        emit playerAddedError("");
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

QFuture<IPlayerModelsContext::Models> PlayerModelsContext::playerModels(const QByteArray &json) const
{
    return QtConcurrent::run([=]()
    {
        auto indexes = getIndexesFromJson(json);
        auto models = getPlayerModelsFromDb()->models(indexes,dbContext());
        return models;

    });
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




