#include "playerservice.h"
#include "DbSLAs/IPlayersDbContext.h"
#include "DbSLAs/igetplayerfromdb.h"
#include "DbSLAs/iplayerbuilder.h"
#include "DbSLAs/isaveplayers.h"
#include "ModelsSLAs/iduplicatechecker.h"
#include "DataSLAs/ijsonbuilder.h"
AbsPlaCtx::ByteArray PlayerService::player(const QUuid &id) const
{
    auto player = getPlayers()->player(id,dbCtx());
    return jsonBuilder()->create(player);
}
AbsPlaCtx::ByteArray PlayerService::player(const QString &name) const
{
    auto player = getPlayers()->player(name, dbCtx());
    return jsonBuilder()->create(player);
}
bool PlayerService::createPlayer(const QByteArray &json)
{
    auto playerCand = playerBuilder()->createPlayer(json);
    if(dupChk()->isDup(playerCand,dbCtx())) return false;
    dbCtx()->add(playerCand);
    return persistDb()->save(dbCtx(),ioHandler(),jsonBuilder());
}
bool PlayerService::remove(const QVector<int> &indexes)
{
    dbCtx()->remove(indexes);
    return persistDb()->save(dbCtx(),ioHandler(),jsonBuilder());
}
QByteArray PlayerService::players()
{
    auto mds = dbCtx()->models();
    return jsonBuilder()->create(mds);
}
AbsPlaCtx::ByteArray PlayerService::players(const QVector<int> &indexes) const
{
    auto players =  getPlayers()->players(indexes,dbCtx());
    return jsonBuilder()->create(players);
}
AbsPlaCtx::ByteArray PlayerService::players(const QVector<QUuid> &ids) const
{
    auto players = getPlayers()->players(ids,dbCtx());
    return jsonBuilder()->create(players);
}
AbsPlaCtx::ByteArray PlayerService::players(const QVector<QString> &names) const
{
    auto players =  getPlayers()->players(names,dbCtx());
    return jsonBuilder()->create(players);
}
