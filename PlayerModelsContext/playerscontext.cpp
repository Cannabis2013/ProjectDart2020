#include "PlayerModelsContext/playerscontext.h"

AbstractPlayersContext::Player *PlayersContext::playerModel(const QUuid &id) const
{
    return getPlayers()->player(id,dbContext());
}

AbstractPlayersContext::Player *PlayersContext::playerModel(const QString &name) const
{
    return getPlayers()->player(name, dbContext());
}

void PlayersContext::createPlayer(const QByteArray &json)
{
    QtConcurrent::run([=]{
        auto playerModel = playerBuilder()->createPlayer(json);
        dbContext()->add(playerModel);
        auto result = persistDbCtx()->save(dbContext(),jsonBuilder());
        if(result)
            emit playerAdded(true);
    });
}

void PlayersContext::remove(const QVector<int> &indexes)
{
    QtConcurrent::run([=]{
        dbContext()->remove(indexes);
        auto result = persistDbCtx()->save(dbContext(),jsonBuilder());
        if(result)
            emit playersDeleted();
    });
}

QByteArray PlayersContext::playerModels()
{
    auto playerModels = dbContext()->models();
    auto json = jsonBuilder()->create(playerModels);
    return json;
}

AbstractPlayersContext::Players PlayersContext::playerModels(const QVector<int> &indexes) const
{
    return getPlayers()->players(indexes,dbContext());
}

AbstractPlayersContext::Players PlayersContext::playerModels(const QVector<QUuid> &ids) const
{
    return getPlayers()->players(ids,dbContext());
}

AbstractPlayersContext::Players PlayersContext::playerModels(const QVector<QString> &names) const
{
    return getPlayers()->players(names,dbContext());
}
