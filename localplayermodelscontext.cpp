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

ImodelsDBContext<DefaultPlayerModelInterface, QUuid> *LocalPlayerModelsContext::modelDBContext()
{
    return _dbContext;
}

LocalPlayerModelsContext *LocalPlayerModelsContext::setup()
{
    read();
    return this;
}

LocalPlayerModelsContext::~LocalPlayerModelsContext()
{
}

void LocalPlayerModelsContext::read()
{
    QJsonObject JSONObject;
    try {
        JSONObject = readJSONFromFile("PlayerModels");
    } catch (...) {
        return;
    }
    auto playersJSONArray = JSONObject["PlayersData"].toArray();

    extractPlayerModelsFromJSON(playersJSONArray);
}

void LocalPlayerModelsContext::write()
{
    /*
     * Persist tournament models
     */
    QJsonObject modelJSON;
    modelJSON["PlayersData"] = assemblePlayersJSONArray();
    writeJSONToFile(modelJSON,"PlayerModels");
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

LocalPlayerModelsContext* LocalPlayerModelsContext::setModelDBContext(ImodelsDBContext<DefaultPlayerModelInterface, QUuid> *context)
{
    _dbContext = context;
    return this;
}

bool LocalPlayerModelsContext::deletePlayer(const int &index)
{
    bool status = true;
    QUuid playerID;
    try {
        playerID = playerIdFromIndex(index);
    }  catch (...) {
        status = false;
    }
    // Delete model from state
    deletePlayerByID(playerID);
    // Persist state change
    write();
    return status;
}

bool LocalPlayerModelsContext::deletePlayers(const QVector<int> &indexes)
{
    bool status = true;
    QList<QUuid> playerIds;
    for (auto index : indexes) {
        auto playerId = playerIdFromIndex(index);
        playerIds << playerId;
    }
    for (auto playerID : playerIds) {
        try {
            deletePlayerByID(playerID);
        }  catch (...) {
            status = false;
        }
    }
    // Persist state change
    write();
    return status;
}


void LocalPlayerModelsContext::deletePlayerByUserName(const QString &playerName)
{
    auto models = modelDBContext()->models("Player");
    for (auto model : models) {
        auto uName = model->playerName();
        if(uName == playerName)
        {
            auto index = modelDBContext()->indexOfModel("Player",model);
            modelDBContext()->removeModel("Player",index);
            return;
        }
    }

    throw "No model found with given id";
}

void LocalPlayerModelsContext::deletePlayerByID(const QUuid &player)
{
    auto models = modelDBContext()->models("Player");
    for (auto model : models) {
        auto modelID = model->id();
        if(modelID == player)
        {
            modelDBContext()->removeModel(modelID,-1);
            return;
        }
    }

    throw "No model found with given id";
}

void LocalPlayerModelsContext::deletePlayerByEmail(const QString &email)
{
    auto models = modelDBContext()->models("Player");
    for (auto model : models) {
        auto mailAdress = model->email();
        if(mailAdress == email)
        {
            auto index = modelDBContext()->indexOfModel("Player",model);
            modelDBContext()->removeModel("Player",index);
            return;
        }
    }

    throw "No model found with given mail adress";
}

QUuid LocalPlayerModelsContext::playerIDFromName(const QString &playerName)
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
        auto model = modelDBContext()->model(QUuid(),index);
        auto modelID = model->id();
        return modelID;
    } catch (...) {
        throw "Model not found";
    }
}

QString LocalPlayerModelsContext::playerNameFromId(const QUuid &id)
{
    auto models = modelDBContext()->models("Player");
    for (auto model : models) {
        auto modelID = model->id();
        if(modelID == id)
            return model->playerName();
    }

    return QString();
}

QString LocalPlayerModelsContext::playerMailFromId(const QUuid &id)
{
    auto models = modelDBContext()->models("Player");
    for (auto model : models) {
        auto modelID = model->id();
        if(modelID == id)
            return model->email();
    }

    return QString();
}

QList<QUuid> LocalPlayerModelsContext::players()
{
    QList<QUuid> resultingList;
    auto models = modelDBContext()->models("Player");
    for (auto model : models) {
        auto modelID = model->id();
        resultingList << modelID;
    }
    return resultingList;
}

int LocalPlayerModelsContext::playersCount()
{
    auto count = modelDBContext()->countOfModels("Player");
    return count;
}

DefaultPlayerBuilder *LocalPlayerModelsContext::playerBuilder() const
{
    return _playerBuilder;
}

QJsonArray LocalPlayerModelsContext::assemblePlayersJSONArray()
{
    QJsonArray playersJSON;
    auto players = this->players();
    for (auto playerID : players) {
        QJsonObject playerJSON;
        playerJSON["ID"] = playerID.toString();
        playerJSON["UserName"] = playerNameFromId(playerID);
        playerJSON["Mail"] = playerMailFromId(playerID);

        playersJSON.append(playerJSON);
    }
    return playersJSON;
}

void LocalPlayerModelsContext::extractPlayerModelsFromJSON(const QJsonArray &arr)
{
    for (auto JSONValue : arr) {
        auto stringID = JSONValue["ID"].toString();
        auto id = QUuid::fromString(stringID);
        auto playerName = JSONValue["UserName"].toString();
        auto mail = JSONValue["Mail"].toString();
        buildPlayerModel(playerName,mail,UserRoles::Player,false,id);
    }
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
        modelDBContext()->addModel(model->id(),model);
    }  catch (...) {
        return QUuid();
    }
    auto modelID = model->id();
    return modelID;
}

const DefaultPlayerModelInterface *LocalPlayerModelsContext::getModel(const QString &playerName)
{
    auto models = modelDBContext()->models("Player");
    for (auto model : models) {
        if(model->playerName() == playerName)
            return model;
    }

    throw "Model not found";
}



