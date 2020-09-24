#include "localplayermodelscontext.h"
void LocalPlayerModelsContext::assembleListOfPlayersFromIndexes(const QVector<int> &playerIndexes)
{
    QList<QUuid> playersID;

    for (auto index : playerIndexes) {
        try {
            auto playerID = playerIDFromIndex(index);
            playersID << playerID;

        }  catch (...)
        {
            return;
        }
    }
    emit sendPlayersID(playersID);
}

void LocalPlayerModelsContext::processTournamentDetails(const QUuid &tournament,
                                                           const QUuid &winner,
                                                           const int &keyPoint,
                                                           const int &terminalKeyCode,
                                                           const int &numberOfThrows,
                                                           const int &gameMode,
                                                           const QList<QUuid> &players)
{
    QList<QPair<QUuid,QString>> resultingList;
    for (int i = 0; i <players.count();i++) {
        auto playerID = players.at(i);
        auto playerName = this->playerName(playerID);
        if(playerName == QString())
        {
            QVariantList args = {tournament};
            emit transmitResponse(ContextResponse::InconsistencyDetected,{tournament});
            return;
        }

        auto pair = QPair<QUuid,QString>(playerID,playerName);

        resultingList << pair;
    }
    auto winnerName = playerName(winner);
    emit sendTournamentDetails(tournament,
                               winnerName,
                               keyPoint,
                               terminalKeyCode,
                               numberOfThrows,
                               gameMode,
                               resultingList);
}

void LocalPlayerModelsContext::handleAndProcessTournamentMetaData(const QString &title,
                                                                  const int &gameMode,
                                                                  const int &keyPoint,
                                                                  const QUuid &winnerID,
                                                                  const QList<QUuid> &assignedPlayersID)
{
    QStringList playerNames;
    for (auto playerID : assignedPlayersID) {
        auto playerName = this->playerName(playerID);
        playerNames << playerName;
    }
    auto winnerName = playerName(winnerID);
    emit sendProcessedTournamentMetaData(title,
                                         gameMode,
                                         keyPoint,
                                         winnerName,
                                         playerNames);
}

void LocalPlayerModelsContext::handleProcessCreatedTournament(const QString &title,
                                                              const int &numberOfThrows,
                                                              const int &gameMode,
                                                              const int &winCondition,
                                                              const int &keyPoint,
                                                              const QList<int> &playerIndexes)
{
    QList<QUuid> playersID;
    for (int i = 0; i < playerIndexes.count(); ++i) {
        auto playerIndex = playerIndexes.at(i);
        auto playerID = playerIDFromIndex(playerIndex);
        auto playerName = this->playerName(playerID);
        playersID << playerID;
    }
    emit sendProcessedTournamentDetails(title,gameMode,numberOfThrows,winCondition,keyPoint,playersID);
}

ImodelsDBContext<IDefaultPlayerModel, QUuid> *LocalPlayerModelsContext::modelDBContext()
{
    return _dbContext;
}

void LocalPlayerModelsContext::handleRequestPlayersDetails()
{
    for (int i = 0; i < playersCount(); ++i) {
        auto playerID = playerIDFromIndex(i);
        auto playerName = this->playerName(playerID);
        auto mail = playerEMail(playerID);
        emit sendPlayerDetails(playerName,mail);
    }
    emit lastPlayerDetailTransmitted();
}

AbstractPlayerModelsContext *LocalPlayerModelsContext::setup()
{
    read();
    return this;
}

LocalPlayerModelsContext::~LocalPlayerModelsContext()
{
    write();
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

DefaultPlayerBuilder *LocalPlayerModelsContext::playerBuilder()
{
    return _playerBuilder;
}

AbstractPlayerModelsContext *LocalPlayerModelsContext::setPlayerBuilder(DefaultPlayerBuilder *builder)
{
    _playerBuilder = builder;
    return this;
}

AbstractPlayerModelsContext *LocalPlayerModelsContext::setModelDBContext(ImodelsDBContext<IDefaultPlayerModel, QUuid> *context)
{
    _dbContext = context;
    return this;
}

void LocalPlayerModelsContext::createPlayer(const QString &name, const QString &mail)
{
    auto id = buildPlayerModel(name,mail,UserRoles::Player);
    auto status = id != QUuid() ? true : false;
    emit confirmPlayerCreated(status);
}

void LocalPlayerModelsContext::deletePlayer(const int &index)
{
    bool status = true;
    QUuid playerID;
    try {
        playerID = playerIDFromIndex(index);
    }  catch (...) {
        status = false;
    }

    deletePlayerByID(playerID);
    emit playersDeletedStatus(status);
}

void LocalPlayerModelsContext::deletePlayers(const QVector<int> &playerIndexes)
{
    bool status = true;
    QList<QUuid> playersID;
    for (auto playerIndex : playerIndexes) {
        auto playerID = playerIDFromIndex(playerIndex);
        playersID << playerID;
    }
    for (auto playerID : playersID) {
        try {
            deletePlayerByID(playerID);
        }  catch (...) {
            status = false;
        }
    }
    emit playersDeletedStatus(status);
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
            auto index = modelDBContext()->indexOfModel("Player",model);
            modelDBContext()->removeModel("Player",index);
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

QUuid LocalPlayerModelsContext::playerIDFromIndex(const int &index)
{
    try {
        auto model = modelDBContext()->model(QUuid(),index);
        auto modelID = model->id();
        return modelID;
    } catch (...) {
        throw "Model not found";
    }
}

QString LocalPlayerModelsContext::playerName(const QUuid &id)
{
    auto models = modelDBContext()->models("Player");
    for (auto model : models) {
        auto modelID = model->id();
        if(modelID == id)
            return model->playerName();
    }

    return QString();
}

QString LocalPlayerModelsContext::playerEMail(const QUuid &id)
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
        playerJSON["UserName"] = playerName(playerID);
        playerJSON["Mail"] = playerEMail(playerID);

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
    auto model = playerBuilder()->buildModel([id,playerName,email,role]
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
        options.setGenerateUniqueId(generateID);
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

const IDefaultPlayerModel *LocalPlayerModelsContext::getModel(const QString &playerName)
{
    auto models = modelDBContext()->models("Player");
    for (auto model : models) {
        if(model->playerName() == playerName)
            return model;
    }

    throw "Model not found";
}



