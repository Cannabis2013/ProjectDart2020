#include "PlayerModelsContext/playerscontext.h"

AbstractPlayersContext::Player *PlayersContext::playerModel(const QUuid &id) const
{
    return getPlayers()->player(id,dbContext());
}

void PlayersContext::createPlayer(const QByteArray &json)
{
    auto playerModel = playerBuilder()->createPlayer(json);
    auto future = dbContext()->add(playerModel)->saveChanges(jsonBuilder());
    Runnable::runLater([=]{
        if(future.result())
            emit playerAddedSucces();
    },future);
}

void PlayersContext::deletePlayersFromIndexes(const QVector<int> &indexes)
{
    dbContext()->remove(indexes)->saveChanges(jsonBuilder());
    emit playersDeletedStatus(true);
}

void PlayersContext::handleRequestPlayersDetails()
{
    auto playerModels = dbContext()->models();
    auto json = jsonBuilder()->toJson(playerModels);
    emit sendPlayers(json);
}

AbstractPlayersContext::Players PlayersContext::playerModels(const QVector<int> &indexes) const
{
    auto models = getPlayers()->players(indexes,dbContext());
    return models;
}

AbstractPlayersContext::Players PlayersContext::playerModels(const QVector<QUuid> &ids) const
{
    auto models = getPlayers()->players(ids,dbContext());
    return models;
}
