#include "PlayerModelsContext/playerscontext.h"

AbstractPlayersContext::Player *PlayersContext::player(const QUuid &id) const
{
    return getPlayers()->player(id,dbCtx());
}

AbstractPlayersContext::Player *PlayersContext::player(const QString &name) const
{
    return getPlayers()->player(name, dbCtx());
}

bool PlayersContext::createPlayer(const QByteArray &json)
{
    auto playerCand = playerBuilder()->createPlayer(json);
    if(dupChk()->isDup(playerCand,dbCtx())) return false;
    dbCtx()->add(playerCand);
    return persistDbCtx()->save(dbCtx(),jsonBuilder());
}

bool PlayersContext::remove(const QVector<int> &indexes)
{
    dbCtx()->remove(indexes);
    return persistDbCtx()->save(dbCtx(),jsonBuilder());
}

QByteArray PlayersContext::players()
{
    auto mds = dbCtx()->models();
    return jsonBuilder()->create(mds);
}

AbstractPlayersContext::Players PlayersContext::players(const QVector<int> &indexes) const
{
    return getPlayers()->players(indexes,dbCtx());
}

AbstractPlayersContext::Players PlayersContext::players(const QVector<QUuid> &ids) const
{
    return getPlayers()->players(ids,dbCtx());
}

AbstractPlayersContext::Players PlayersContext::players(const QVector<QString> &names) const
{
    return getPlayers()->players(names,dbCtx());
}
