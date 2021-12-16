#ifndef GETPLAYERSFROMDB_H
#define GETPLAYERSFROMDB_H
#include "PlayerModelsContext/DbSLAs/igetplayerfromdb.h"
#include "PlayerModelsContext/DbSLAs/iplayer.h"
#include "PlayerModelsContext/DbSLAs/IPlayersDbContext.h"
class GetPlayersFromDb : public IGetPlayersFromDb<IPlayer,IPlayersDbContext<IPlayer>>
{
public:
    Player *player(const QUuid &id, const DbContext *dbContext) const override
    {
        auto players = dbContext->models();
        return model(id,players);
    }
    Player *player(const QString &name, const DbContext *dbContext) const override
    {
        auto model = dbContext->model([name](IPlayer* m){
                if(m->name() == name)
                    return true;
                return false;
            });
        return dynamic_cast<IPlayer*>(model);
    }
    QVector<IPlayer*> players(const QVector<int> &indexes, const DbContext *dbContext) const override
    {
        auto models = dbContext->models();
        QVector<IPlayer*> playerModels;
        for (const auto &index : indexes)
            playerModels << model(index,models);
        return playerModels;
    }
    Players players(const QVector<QUuid> &ids, const DbContext *dbContext) const override
    {
        auto models = dbContext->models([ids](Player* m){return ids.contains(m->name());});
        return convert(models);
    }
    Players players(const QVector<QString> &names, const DbContext *dbContext) const override
    {
        auto models = dbContext->models([names](IPlayer* m){
                return names.contains(m->name());
            });
        return convert(models);
    }
private:
    IPlayer *model(const int &index, const Players &models) const
    {
        if(index < 0 || index >= models.count())
            return nullptr;
        return dynamic_cast<IPlayer*>(models.at(index));
    }
    Player *model(const QUuid &id, const Players &models) const
    {
        for (auto &model : models)
        {
            if(model->id() == id)
                return model;
        }
        return nullptr;
    }
    Players convert(const Players &models) const
    {
        Players list;
        for (const auto &model : models)
            list << dynamic_cast<IPlayer*>(model);
        return list;
    }
};
#endif // GETPLAYERDATAFROMDB_H
