#include "localplayermodelscontext.h"

QVector<QString> LocalPlayerModelsContext::assemblePlayerMailAdressesFromIds(const QVector<QUuid> &ids)
{
    QVector<QString> mailAdresses;
    for (auto id : ids) {
        auto mail = playerMailFromId(id);
        mailAdresses << mail;
    }
    return mailAdresses;
}

QVector<QString> LocalPlayerModelsContext::assemblePlayerNamesFromIds(const QVector<QUuid> &ids)
{
    QVector<QString> assignedPlayerNames;
    for (int i = 0; i <ids.count();i++) {
        auto playerID = ids.at(i);
        auto playerName = this->playerNameFromId(playerID);
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

QVector<QUuid> LocalPlayerModelsContext::assemblePlayerIds(const QVector<int> &indexes)
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

IModelsDbContext *LocalPlayerModelsContext::modelDBContext()
{
    return _dbContext;
}

LocalPlayerModelsContext *LocalPlayerModelsContext::setup()
{
    return this;
}

LocalPlayerModelsContext::~LocalPlayerModelsContext()
{

}


QUuid LocalPlayerModelsContext::createPlayer(const QString &name, const QString &mail, const int &role)
{
    return buildPlayerModel(name,mail,role);
}

DefaultPlayerBuilder *LocalPlayerModelsContext::playerBuilder()
{
    return _playerBuilder;
}

LocalPlayerModelsContext* LocalPlayerModelsContext::setPlayerBuilder(DefaultPlayerBuilder *builder)
{
    _playerBuilder = builder;
    return this;
}

LocalPlayerModelsContext* LocalPlayerModelsContext::setModelDBContext(IModelsDbContext *context)
{
    _dbContext = context;
    return this;
}

bool LocalPlayerModelsContext::deletePlayer(const int &index)
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

bool LocalPlayerModelsContext::deletePlayers(const QVector<int> &indexes)
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
    for (auto playerID : playerIds) {
        try {
            deletePlayerByID(playerID);
        }  catch (...) {
            status = false;
        }
    }
    return status;
}


void LocalPlayerModelsContext::deletePlayerByUserName(const QString &playerName)
{
    auto models = modelDBContext()->playerModels();
    for (auto model : models) {
        auto playerModel = dynamic_cast<const IDefaultPlayerModel*>(model);
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

void LocalPlayerModelsContext::deletePlayerByID(const QUuid &player)
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

void LocalPlayerModelsContext::deletePlayerByEmail(const QString &email)
{
    auto models = modelDBContext()->playerModels();
    for (auto model : models) {
        auto playerModel = dynamic_cast<const IDefaultPlayerModel*>(model);
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

QUuid LocalPlayerModelsContext::playerIdFromName(const QString &playerName)
{
    try {
        auto model = getModel(playerName);
        return model->id();
    } catch (const char *msg) {
        throw msg;
    }
}

QUuid LocalPlayerModelsContext::playerIdFromIndex(const int &index)
{
    try {
        auto model = modelDBContext()->playerModel(index);
        auto modelID = model->id();
        return modelID;
    } catch (...) {
        throw "Model not found";
    }
}

QString LocalPlayerModelsContext::playerNameFromId(const QUuid &id)
{
    auto models = modelDBContext()->playerModels();
    for (auto model : models) {
        auto playerModel = dynamic_cast<const IDefaultPlayerModel*>(model);
        auto modelID = playerModel->id();
        if(modelID == id)
            return playerModel->playerName();
    }

    return QString();
}

QString LocalPlayerModelsContext::playerMailFromId(const QUuid &id)
{
    auto models = modelDBContext()->playerModels();
    for (auto model : models) {
        auto playerModel = dynamic_cast<const IDefaultPlayerModel*>(model);
        auto modelID = model->id();
        if(modelID == id)
            return playerModel->email();
    }

    return QString();
}

QList<QUuid> LocalPlayerModelsContext::players()
{
    QList<QUuid> resultingList;
    auto models = modelDBContext()->playerModels();
    for (auto model : models) {
        auto modelID = model->id();
        resultingList << modelID;
    }
    return resultingList;
}

int LocalPlayerModelsContext::playersCount()
{
    auto models = modelDBContext()->playerModels();
    auto count = models.count();
    return count;
}

DefaultPlayerBuilder *LocalPlayerModelsContext::playerBuilder() const
{
    return _playerBuilder;
}


QUuid LocalPlayerModelsContext::buildPlayerModel(const QString &playerName,
                                                const QString &email,
                                                const int &role,
                                                const bool &generateID,
                                                const QUuid &id)
{
    auto model = playerBuilder()->buildPlayerModel([id,playerName,email,role]
    {
        PlayerBuilderParameters params;
        params.setId(id);
        params.setRole(role);
        params.setUserName(playerName);
        params.setMailAdress(email);
        return params;
    }(),[generateID]
    {
        PlayerModelOptions options;
        options.enableGenerateUniqueID(generateID);
        return options;
    }());
    try {
        modelDBContext()->addPlayerModel(model);
    }  catch (...) {
        return QUuid();
    }
    auto modelID = model->id();
    return modelID;
}

const IDefaultPlayerModel *LocalPlayerModelsContext::getModel(const QString &playerName)
{
    auto models = modelDBContext()->playerModels();
    for (auto model : models) {
        auto playerModel = dynamic_cast<const IDefaultPlayerModel*>(model);
        if(playerModel->playerName() == playerName)
            return playerModel;
    }

    throw "Model not found";
}



