#include "playermodelscontext.h"

void PlayerModelsContext::createPlayer(const QByteArray &json)
{
    auto playerModel = createPlayerModel()->createPlayerModel(json);
    try {
        modelsDbContext()->add(playerModel);
    }  catch (...) {
        emit playerAddedError("");
        return;
    }
    emit playerAddedSucces();
}

void PlayerModelsContext::deletePlayersFromIndexes(const QVector<int> &indexes)
{
    auto status = removeFromDb()->remove(indexes,modelsDbContext());
    emit playersDeletedStatus(status);
}

void PlayerModelsContext::handleRequestPlayersDetails()
{
    auto playerModels = modelsDbContext()->models();
    auto json = dartsPlayerCreateJson()->createJson(playerModels);
    emit sendPlayers(json);
}

QFuture<IPlayerModelsContext::Models> PlayerModelsContext::playerModels(const QByteArray &json) const
{
    auto createModels = [=]()
    {
        auto models = createPlayerModels()->createPlayerModels(json,getPlayerModelsFromDb(),modelsDbContext());
        return models;
    };
    return QtConcurrent::run(createModels);
}




