#include "getplayersfromdb.h"
#include <qvector.h>
#include <PlayerModelsContext/DbSLAs/IPlayersDbContext.h>
#include <PlayerModelsContext/DbSLAs/iplayer.h>

GetPlayersFromDb::Player *GetPlayersFromDb::player(const QUuid &id, const DbContext *dbContext) const
{
        auto players = dbContext->models();
        return model(id,players);
}
GetPlayersFromDb::Player *GetPlayersFromDb::player(const QString &name, const DbContext *dbContext) const
{
        auto model = dbContext->model([name](IPlayer* m){
                if(m->name() == name)
                return true;
                return false;
});
    return dynamic_cast<IPlayer*>(model);
}
QVector<IPlayer *> GetPlayersFromDb::players(const QVector<int> &indexes, const DbContext *dbContext) const
{
        auto models = dbContext->models();
        QVector<IPlayer*> playerModels;
        for (const auto &index : indexes)
                playerModels << model(index,models);
        return playerModels;
}

GetPlayersFromDb::Players GetPlayersFromDb::players(const QVector<QUuid> &ids, const DbContext *dbContext) const
{
        auto models = dbContext->models([ids](Player* m){return ids.contains(m->name());});
        return convert(models);
}

GetPlayersFromDb::Players GetPlayersFromDb::players(const QVector<QString> &names, const DbContext *dbContext) const
{
        auto models = dbContext->models([names](IPlayer* m){
                return names.contains(m->name());
        });
        return convert(models);
}

IPlayer *GetPlayersFromDb::model(const int &index, const Players &models) const
{
        if(index < 0 || index >= models.count())
                return nullptr;
        return dynamic_cast<IPlayer*>(models.at(index));
}

GetPlayersFromDb::Player *GetPlayersFromDb::model(const QUuid &id, const Players &models) const
{
        for (auto &model : models)
        {
                if(model->id() == id)
                        return model;
        }
        return nullptr;
}

GetPlayersFromDb::Players GetPlayersFromDb::convert(const Players &models) const
{
        Players list;
        for (const auto &model : models)
                list << dynamic_cast<IPlayer*>(model);
        return list;
}
