#include "PlayerModelsContext/playerscontext.h"

AbstractPlayersContext::Player *PlayersContext::player(const QUuid &id) const
{
    return getPlayers()->player(id,dbContext());
}

AbstractPlayersContext::Player *PlayersContext::player(const QString &name) const
{
    return getPlayers()->player(name, dbContext());
}

bool PlayersContext::createPlayer(const QByteArray &json)
{
    auto playerModel = playerBuilder()->createPlayer(json);
    dbContext()->add(playerModel);
    return persistDbCtx()->save(dbContext(),jsonBuilder());
}

bool PlayersContext::remove(const QVector<int> &indexes)
{
    dbContext()->remove(indexes);
    return persistDbCtx()->save(dbContext(),jsonBuilder());
}

QByteArray PlayersContext::players()
{
    auto playerModels = dbContext()->models();
    return jsonBuilder()->create(playerModels);
}

AbstractPlayersContext::Players PlayersContext::players(const QVector<int> &indexes) const
{
    return getPlayers()->players(indexes,dbContext());
}

AbstractPlayersContext::Players PlayersContext::players(const QVector<QUuid> &ids) const
{
    return getPlayers()->players(ids,dbContext());
}

AbstractPlayersContext::Players PlayersContext::players(const QVector<QString> &names) const
{
    return getPlayers()->players(names,dbContext());
}
