#include "localplayermodelsservice.h"

QVector<QString> LocalPlayerModelsService::assemblePlayerMailAdressesFromIds(const QVector<QUuid> &ids) const
{
    QVector<QString> mailAdresses;
    for (auto id : ids) {
        auto mail = playerMailFromId(id);
        mailAdresses << mail;
    }
    return mailAdresses;
}

QVector<QString> LocalPlayerModelsService::assemblePlayerNamesFromIds(const QVector<QUuid> &ids) const
{
    QVector<QString> assignedPlayerNames;
    for (int i = 0; i <ids.count();i++) {
        auto playerID = ids.at(i);
        auto playerName = this->playerNameById(playerID);
        if(playerName == QString())
        {
            /*
             * TODO: Implement proper exception string
             */
            throw "Some text";
        }
        assignedPlayerNames << playerName;
    }
    return assignedPlayerNames;
}

QVector<QUuid> LocalPlayerModelsService::assemblePlayerIds(const QVector<int> &indexes) const
{
    QVector<QUuid> playersId;

    for (auto index : indexes) {
        try {
            auto playerID = playerIdFromIndex(index);
            playersId << playerID;

        }  catch (...)
        {
            // TODO: Implement proper exception string
            throw "Some warning";
        }
    }
    return playersId;
}

IModelsDbContext *LocalPlayerModelsService::modelDBContext() const
{
    return _dbContext;
}

LocalPlayerModelsService *LocalPlayerModelsService::createInstance()
{
    return new LocalPlayerModelsService();
}

const QUuid LocalPlayerModelsService::addPlayerModelToDb(const IPlayerModel* model)
{
    _dbContext->addPlayerModel(model);
    return model->id();
}

LocalPlayerModelsService* LocalPlayerModelsService::setModelDBContext(IModelsDbContext *context)
{
    _dbContext = context;
    return this;
}

bool LocalPlayerModelsService::deletePlayer(const int &index)
{
    QUuid playerID;
    try {
        playerID = playerIdFromIndex(index);
    }  catch (...) {
        return false;
    }
    // Delete model from state
    deletePlayerByID(playerID);
    // Persist state change
    return true;
}

bool LocalPlayerModelsService::deletePlayersByIndexes(const QVector<int> &indexes)
{
    bool status = true;
    QList<QUuid> playerIds;
    for (auto index : indexes) {
        QUuid playerId;
        try {
            playerId = playerIdFromIndex(index);
        }  catch (...) {
            return false;
        }
        playerIds << playerId;
    }
    for (auto playerID : qAsConst(playerIds)) {
        try {
            deletePlayerByID(playerID);
        }  catch (...) {
            status = false;
        }
    }
    return status;
}


void LocalPlayerModelsService::deletePlayerByUserName(const QString &playerName)
{
    auto models = modelDBContext()->playerModels();
    for (auto model : models) {
        auto playerModel = dynamic_cast<const IPlayerModel*>(model);
        auto uName = playerModel->playerName();
        if(uName == playerName)
        {
            auto index = modelDBContext()->indexOfPlayerModel(model);
            modelDBContext()->removePlayerModel(index);
            return;
        }
    }
    throw "No model found with given id";
}

void LocalPlayerModelsService::deletePlayerByID(const QUuid &player)
{
    auto models = modelDBContext()->playerModels();
    for (auto model : models) {
        auto modelID = model->id();
        if(modelID == player)
        {
            auto index = modelDBContext()->indexOfPlayerModel(model);
            modelDBContext()->removePlayerModel(index);
            return;
        }
    }
    throw "No model found with given id";
}

void LocalPlayerModelsService::deletePlayerByEmail(const QString &email)
{
    auto models = modelDBContext()->playerModels();
    for (auto model : models) {
        auto playerModel = dynamic_cast<const IPlayerModel*>(model);
        auto mailAdress = playerModel->email();
        if(mailAdress == email)
        {
            auto index = modelDBContext()->indexOfPlayerModel(model);
            modelDBContext()->removePlayerModel(index);
            return;
        }
    }
    throw "No model found with given mail adress";
}

QUuid LocalPlayerModelsService::playerIdFromName(const QString &playerName) const
{
    try {
        auto model = getModel(playerName);
        return model->id();
    } catch (const char *msg) {
        throw msg;
    }
}

QUuid LocalPlayerModelsService::playerIdFromIndex(const int &index) const
{
    try {
        auto model = modelDBContext()->playerModel(index);
        auto modelID = model->id();
        return modelID;
    } catch (...) {
        throw "Model not found";
    }
}

QString LocalPlayerModelsService::playerNameById(const QUuid &id) const
{
    auto models = modelDBContext()->playerModels();
    for (auto model : models) {
        auto playerModel = dynamic_cast<const IPlayerModel*>(model);
        auto modelID = playerModel->id();
        if(modelID == id)
            return playerModel->playerName();
    }
    return QString();
}

QString LocalPlayerModelsService::playerMailFromId(const QUuid &id) const
{
    auto models = modelDBContext()->playerModels();
    for (auto model : models) {
        auto playerModel = dynamic_cast<const IPlayerModel*>(model);
        auto modelID = model->id();
        if(modelID == id)
            return playerModel->email();
    }

    return QString();
}

QList<QUuid> LocalPlayerModelsService::players() const
{
    QList<QUuid> resultingList;
    auto models = modelDBContext()->playerModels();
    for (auto model : models) {
        auto modelID = model->id();
        resultingList << modelID;
    }
    return resultingList;
}

int LocalPlayerModelsService::playersCount() const
{
    auto models = modelDBContext()->playerModels();
    auto count = models.count();
    return count;
}
const IPlayerModel *LocalPlayerModelsService::getModel(const QString &playerName) const
{
    auto models = modelDBContext()->playerModels();
    for (auto model : models) {
        auto playerModel = dynamic_cast<const IPlayerModel*>(model);
        if(playerModel->playerName() == playerName)
            return playerModel;
    }
    throw "Model not found";
}



