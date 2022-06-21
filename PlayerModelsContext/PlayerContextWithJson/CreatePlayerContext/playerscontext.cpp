#include "playerscontext.h"
#include "PlayerModelsContext/Contracts/DbSLAs/IPlayersDbContext.h"
#include "PlayerModelsContext/Contracts/DbSLAs/igetplayerfromdb.h"
#include "PlayerModelsContext/Contracts/DbSLAs/iplayerbuilder.h"
#include "PlayerModelsContext/Contracts/DbSLAs/isaveplayers.h"
#include "PlayerModelsContext/Contracts/ModelsSLAs/iduplicatechecker.h"
#include "PlayerModelsContext/Contracts/DataSLAs/ijsonbuilder.h"

AbstractPlayerContext::ByteArray PlayersContext::player(const QUuid &id) const
{
    auto player = getPlayers()->player(id,dbCtx());
    return jsonBuilder()->create(player);
}

AbstractPlayerContext::ByteArray PlayersContext::player(const QString &name) const
{
    auto player = getPlayers()->player(name, dbCtx());
    return jsonBuilder()->create(player);
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

AbstractPlayerContext::ByteArray PlayersContext::players(const QVector<int> &indexes) const
{
    auto players =  getPlayers()->players(indexes,dbCtx());
    return jsonBuilder()->create(players);
}

AbstractPlayerContext::ByteArray PlayersContext::players(const QVector<QUuid> &ids) const
{
    auto players = getPlayers()->players(ids,dbCtx());
    return jsonBuilder()->create(players);
}

AbstractPlayerContext::ByteArray PlayersContext::players(const QVector<QString> &names) const
{
    auto players =  getPlayers()->players(names,dbCtx());
    return jsonBuilder()->create(players);
}
