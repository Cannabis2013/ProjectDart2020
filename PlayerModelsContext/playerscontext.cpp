#include "playerscontext.h"
AbsPlaCtx::Player *PlayersContext::player(const QUuid &id) const
{
    return getPlayers()->player(id,dbCtx());
}
AbsPlaCtx::Player *PlayersContext::player(const QString &name) const
{
    return getPlayers()->player(name, dbCtx());
}
bool PlayersContext::createPlayer(const QByteArray &json)
{
    auto playerCand = playerBuilder()->createPlayer(json);
    if(dupChk()->isDup(playerCand,dbCtx())) return false;
    dbCtx()->add(playerCand);
    return persistDb()->save(dbCtx(),ioHandler(),jsonBuilder());
}
bool PlayersContext::remove(const QVector<int> &indexes)
{
    dbCtx()->remove(indexes);
    return persistDb()->save(dbCtx(),ioHandler(),jsonBuilder());
}
QByteArray PlayersContext::players()
{
    auto mds = dbCtx()->models();
    return jsonBuilder()->create(mds);
}
AbsPlaCtx::Players PlayersContext::players(const QVector<int> &indexes) const
{
    return getPlayers()->players(indexes,dbCtx());
}
AbsPlaCtx::Players PlayersContext::players(const QVector<QUuid> &ids) const {return getPlayers()->players(ids,dbCtx());}
AbsPlaCtx::Players PlayersContext::players(const QVector<QString> &names) const {return getPlayers()->players(names,dbCtx());}
