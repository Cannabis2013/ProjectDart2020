#include "localplayermodelscontext.h"
void LocalPlayerModelsContext::handlePlayersFromIndexRequest(const QVector<int> &playerIndexes)
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
            throw "Inconsistency deteced";

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
                                                            const QList<QUuid> &assignedPlayersID)
{
    QStringList playerNames;
    for (auto playerID : assignedPlayersID) {
        auto playerName = this->playerName(playerID);
        playerNames << playerName;
    }
    emit sendProcessedTournamentMetaData(title,gameMode,keyPoint,playerNames);
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

void LocalPlayerModelsContext::handleRequestPlayersDetails()
{
    for (int i = 0; i < playersCount(); ++i) {
        auto playerID = playerIDFromIndex(i);
        auto playerName = this->playerName(playerID);
        auto mail = playerEMail(playerID);
        emit sendPlayerDetails(playerName,mail);
    }
}

QList<QUuid> LocalPlayerModelsContext::createDummyModels()
{
    // Test purposes
    auto mh = createPlayer("Martin Hansen","havnetrold2002@yahoo.dk",UserRoles::Player);
    auto w = createPlayer("Willerex","WildWill@gmail.com",UserRoles::Player);
    auto kk = createPlayer("Kent KillerHertz","KillerHertz@gmail.com",UserRoles::Player);
    auto sp = createPlayer("Sniffer Per","SnowWhite1977@hotmail.com",UserRoles::Player);
    auto ko = createPlayer("Kokain Ole","",UserRoles::Player);
    return {mh,w,kk,sp,ko};
}

DefaultPlayerBuilder *LocalPlayerModelsContext::playerBuilder()
{
    return _playerBuilder;
}

void LocalPlayerModelsContext::setPlayerBuilder(DefaultPlayerBuilder *builder)
{
    _playerBuilder = builder;
}

void LocalPlayerModelsContext::handleCreatePlayerRequest(const QString &name, const QString &mail)
{
    createPlayer(name,mail,UserRoles::Player);
    emit transmitResponse(ModelsContextResponse::PlayerCreatedOK,{});
}

void LocalPlayerModelsContext::handleDeletePlayerRequest(const int &index)
{
    QUuid playerID;
    try {
        playerID = playerIDFromIndex(index);
    }  catch (...) {
        return;
    }

    deletePlayerByID(playerID);
    emit transmitResponse(ModelsContextResponse::PlayerDeletedOK,{});
}

void LocalPlayerModelsContext::deletePlayers(const QVector<int> &playerIndexes)
{
    QList<QUuid> playersID;
    for (auto playerIndex : playerIndexes) {
        auto playerID = playerIDFromIndex(playerIndex);
        playersID << playerID;
    }
    for (auto playerID : playersID) {
        try {
            deletePlayerByID(playerID);
        }  catch (...) {
            throw "Inconsistency detected";
        }
    }

}

QUuid LocalPlayerModelsContext::createPlayer(const QString &playerName, const QString &email, const int &role)
{
    auto model = playerBuilder()->buildModel([playerName,email,role]
    {
        PlayerBuilderParameters params;
        params.setUserName(playerName);
        params.setMailAdress(email);
        params.setRole(role);
        return params;
    }(),[]
    {
        PlayerModelOptions options;
        options.setGenerateUniqueId(true);
        return options;
    }());

    _models << model;
    auto playerID = model->id();
    return playerID;
}

void LocalPlayerModelsContext::deletePlayerByUserName(const QString &playerName)
{
    for (auto model : _models) {
        auto uName = model->playerName();
        if(uName == playerName)
        {
            _models.removeOne(model);
            return;
        }
    }

    throw "No model found with given id";
}

void LocalPlayerModelsContext::deletePlayerByID(const QUuid &player)
{
    for (auto model : _models) {
        auto modelID = model->id();
        if(modelID == player)
        {
            _models.removeOne(model);
            return;
        }
    }

    throw "No model found with given id";
}

void LocalPlayerModelsContext::deletePlayerByEmail(const QString &email)
{
    for (auto model : _models) {
        auto mailAdress = model->email();
        if(mailAdress == email)
        {
            _models.removeOne(model);
            return;
        }
    }

    throw "No model found with given mail adress";
}

QUuid LocalPlayerModelsContext::playerIDFromName(const QString &playerName) const
{
    try {
        auto model = getModel(playerName);
        return model->id();
    } catch (const char *msg) {
        throw msg;
    }
}

QUuid LocalPlayerModelsContext::playerIDFromIndex(const int &index) const
{
    try {
        auto model = _models.at(index);
        auto modelID = model->id();
        return modelID;
    } catch (...) {
        throw "Model not found";
    }
}

QString LocalPlayerModelsContext::playerName(const QUuid &id) const
{
    for (auto model : _models) {
        auto modelID = model->id();
        if(modelID == id)
            return model->playerName();
    }

    return QString();
}

QString LocalPlayerModelsContext::playerEMail(const QUuid &id) const
{
    for (auto model : _models) {
        auto modelID = model->id();
        if(modelID == id)
            return model->email();
    }

    return QString();
}

QList<QUuid> LocalPlayerModelsContext::players() const
{
    QList<QUuid> resultingList;
    for (auto model : _models) {
        auto modelID = model->id();
        resultingList << modelID;
    }

    return resultingList;
}

int LocalPlayerModelsContext::playersCount() const
{
    return _models.count();
}

DefaultPlayerBuilder *LocalPlayerModelsContext::playerBuilder() const
{
    return _playerBuilder;
}

void LocalPlayerModelsContext::buildPlayerModel(const QUuid &id, const QString &playerName, const QString &email)
{
    auto model = playerBuilder()->buildModel([id,playerName,email]
    {
        PlayerBuilderParameters params;
        params.setId(id);
        params.setUserName(playerName);
        params.setMailAdress(email);
        return params;
    }(),[]
    {
        PlayerModelOptions options;
        options.setGenerateUniqueId(false);
        return options;
    }());

    _models << model;
}

DefaultPlayerInterface *LocalPlayerModelsContext::getModel(const QString &playerName) const
{
    for (auto model : _models) {
        if(model->playerName() == playerName)
            return model;
    }

    throw "Model not found";
}



