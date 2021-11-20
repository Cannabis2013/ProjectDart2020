#include "PlayerModelsContext/playerscontext.h"

AbstractPlaCtx::Player *PlayersContext::playerModel(const QUuid &id) const
{
    return getPlayers()->player(id,dbContext());
}

AbstractPlaCtx::Player *PlayersContext::playerModel(const QString &name) const
{
    return getPlayers()->player(name, dbContext());
}

void PlayersContext::createPlayer(const QByteArray &json)
{
    auto playerModel = playerBuilder()->createPlayer(json);
    dbContext()->add(playerModel);
    RunLater::run<bool>(dbContext()->saveChanges(jsonBuilder()),[=](const bool &result){
        if(result) emit playerAdded();
    });
}

void PlayersContext::remove(const QVector<int> &indexes)
{
    dbContext()->remove(indexes);
    RunLater::run<bool>(dbContext()->saveChanges(jsonBuilder()),[=](const bool &result){
        if(result) emit playersDeleted();
    });
}

QByteArray PlayersContext::playerModels()
{
    auto playerModels = dbContext()->models();
    auto json = jsonBuilder()->toJson(playerModels);
    return json;
}

AbstractPlaCtx::Players PlayersContext::playerModels(const QVector<int> &indexes) const
{
    return getPlayers()->players(indexes,dbContext());
}

AbstractPlaCtx::Players PlayersContext::playerModels(const QVector<QUuid> &ids) const
{
    return getPlayers()->players(ids,dbContext());
}

AbstractPlaCtx::Players PlayersContext::playerModels(const QVector<QString> &names) const
{
    return getPlayers()->players(names,dbContext());
}
