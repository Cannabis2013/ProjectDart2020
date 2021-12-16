#ifndef PLAYERSCONTEXT_H
#define PLAYERSCONTEXT_H
#include <QtConcurrent/QtConcurrent>
#include "PlayerModelsContext/SLAs/absplactx.h"
#include "PlayerModelsContext/DbSLAs/PlayersDbSLAs.h"
class PlayersContext : public AbsPlaCtx,
                       public PlayersDbSLAs
{
    Q_OBJECT
public:
    Player *player(const QUuid &id) const override {return getPlayers()->player(id,dbCtx());}
    Player *player(const QString &name) const override {return getPlayers()->player(name, dbCtx());}
    bool createPlayer(const QByteArray &json) override
    {
        auto playerCand = playerBuilder()->createPlayer(json);
        if(dupChk()->isDup(playerCand,dbCtx())) return false;
        dbCtx()->add(playerCand);
        return persistDb()->save(dbCtx(),ioHandler(),jsonBuilder());
    }
    bool remove(const QVector<int> &indexes) override
    {
        dbCtx()->remove(indexes);
        return persistDb()->save(dbCtx(),ioHandler(),jsonBuilder());
    }
    QByteArray players() override
    {
        auto mds = dbCtx()->models();
        return jsonBuilder()->create(mds);
    }
    Players players(const QVector<int> &indexes) const override {return getPlayers()->players(indexes,dbCtx());}
    Players players(const QVector<QUuid> &ids) const override {return getPlayers()->players(ids,dbCtx());}
    Players players(const QVector<QString> &names) const override {return getPlayers()->players(names,dbCtx());}
};
#endif // PLAYERSCONTEXT_H
