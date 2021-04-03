#include "remotemodelscontext.h"



RemoteModelsContext::RemoteModelsContext()
{
    _netMng->setParserService(new UrlParser);
}

void RemoteModelsContext::transmitResponse(const int &response, const QVariantList &args)
{
}

void RemoteModelsContext::addFTPTournament(const QString &title,
                                                 const QVector<int> &data,
                                                 const QVector<int> &playerIndexes)
{
    QJsonObject jsonObject = {
        {"Title", title},
        {"GameMode",data[0]},
        {"KeyPoint",data[1]},
        {"TerminalKeyCode",data[2]},
        {"DisplayHint",data[3]},
        {"InputHint",data[4]},
        {"Attempts",data[5]}
    };
    QJsonArray indexes;
    for (auto i = playerIndexes.constBegin();i != playerIndexes.constEnd() ;++i )
        indexes << *i;
    jsonObject["Indexes"] = indexes;
    auto tournament = QJsonDocument(jsonObject).toJson();
    _netMng->sendPostRequest("AddFtpTournament",
                             tournament,
                             QString(),
                             {},
                             this,
                             SLOT(handleAddFTPTournamentReply()));
}

void RemoteModelsContext::assignPlayersToTournament(const QUuid &tournament, const QList<QUuid> &playersID)
{
}

void RemoteModelsContext::deleteTournaments(const QVector<int> &indexes)
{
    RemoteContext::RemoteJsonObject jsonObject;
    QJsonArray arr;
    for (auto i = indexes.constBegin(); i != indexes.constEnd(); ++i) {
        auto value = *i;
        arr << value;
    }
    jsonObject["Indexes"] = arr;
    auto data = jsonObject.toJson();
    _netMng->sendPostRequest("DeleteTournamentsFromIndexes",
                             data,QString(),{},this,
                             SLOT(handleDeleteTournamentsReply()));
}

void RemoteModelsContext::handleRequestAssignedPlayers(const QUuid &tournament)
{
}

void RemoteModelsContext::handleRequestFtpScores(const QUuid &tournament)
{

}

void RemoteModelsContext::handleRequestTournaments()
{
    _netMng->sendGetRequest("GetTournaments",
                            QString(),
                            {},
                            this,
                            SLOT(handleRecievedTournamentsReply()));
}

void RemoteModelsContext::handleRequestGameMode(const int &index)
{
    _netMng->sendGetRequest("GetTournamentGameMode",
                            QString(),{},this,
                            SLOT(handleRequestGameModeReply()));
}

void RemoteModelsContext::assembleFTPMetaDataFromId(const QUuid &tournamentId)
{
    auto formattedTournamentId  = tournamentId.toString(QUuid::WithoutBraces);
    _netMng->sendGetRequest("GetFtpTournamentMeta",
                            QString(),{{"tournamentId",formattedTournamentId}},
                            this,SLOT(handleFtpTournamentMetaReply()));
}

void RemoteModelsContext::addFtpScore(const QUuid &tournamentId,
                                         const QUuid &playerId,
                                         const int &roundIndex,
                                         const int &setIndex,
                                         const int &attemptIndex,
                                         const int &point,
                                         const int &score,
                                         const int &keyCode,
                                         const bool &isWinnerDetermined)
{
    QJsonObject jsonObject= {
        {"TournamentId", tournamentId.toString(QUuid::WithoutBraces)},
        {"PlayerId",playerId.toString(QUuid::WithoutBraces)},
        {"RoundIndex", roundIndex},
        {"SetIndex", setIndex},
        {"AttemptIndex",attemptIndex},
        {"Point",point},
        {"ScoreValue",score},
        {"KeyCode",keyCode}
    };
    auto winnerId = isWinnerDetermined ? playerId.toString() : "";

    auto document = QJsonDocument(jsonObject);
    auto data = document.toJson();

    _netMng->sendPostRequest("AddFtpScore",
                             data,QString(),
                             {{"winnerId",winnerId}},
                             this,SLOT(handleAddFtpScoreReply()));

}

void RemoteModelsContext::setFtpScoreHint(const QUuid &tournament,
                                          const QUuid &player,
                                          const int &roundIndex,
                                          const int &attemptIndex,
                                          const int &hint)
{
    auto tournamentId = tournament.toString(QUuid::WithoutBraces);
    auto playerId = player.toString(QUuid::WithoutBraces);
    QVector<NetworkManager::Query> stringQuery = {
        {"tournamentId", tournamentId},
        {"playerId",playerId},
        {"roundIndex",QString::number(roundIndex)},
        {"attemptIndex",QString::number(attemptIndex)},
        {"hint",QString::number(hint)}
    };
    _netMng->sendPostRequest("SetFtpScoreHint",QByteArray(),QString(),stringQuery,this,SLOT(handleSetScoreHintReply()));
}

void RemoteModelsContext::resetTournament(const QUuid &tournament)
{
    auto tournamentId = tournament.toString(QUuid::WithoutBraces);
    _netMng->sendPostRequest("ResetTournament",QByteArray(),QString(),{{"tournamentId",tournamentId}},this,SLOT(tournamentResetReply()));
}

void RemoteModelsContext::assembleFtpKeyValues(const QUuid &tournament)
{
    _netMng->sendGetRequest("GetFtpDetails",
                            QString(),{{"tournamentId",tournament.toString(QUuid::WithoutBraces)}},this,
                            SLOT(handleRequestFtpDetailsReply()));
}

void RemoteModelsContext::createPlayer(const QString &name, const QString &mail)
{
    QJsonObject obj({{"PlayerName",name},{"PlayerMail",mail}});
    auto data = QJsonDocument(obj).toJson();
    _netMng->sendPostRequest("CreatePlayer",
                             data,QString(),{},this,
                             SLOT(handleCreatePlayerResponse()));
}

void RemoteModelsContext::deletePlayerFromIndex(const int &index)
{
}

void RemoteModelsContext::deletePlayersFromIndexes(const QVector<int> &playerIndexes)
{
}

void RemoteModelsContext::handleRequestPlayersDetails()
{
    _netMng->sendGetRequest("GetPlayers",
                            QString(),
                            {},
                            this,
                            SLOT(handleRequestPlayersReply()));
}

void RemoteModelsContext::assembleFtpIndexesAndScores(const QUuid &tournament)
{
    auto tournamentId = tournament.toString(QUuid::WithoutBraces);
    _netMng->sendGetRequest("GetFtpIndexesAndScores",
                            QString(),{{"tournamentId",tournamentId}},
                            this,SLOT(handleFtpIndexesAndScores()));
}

void RemoteModelsContext::handleRecievedTournamentsReply()
{
    if(!_netMng->reply()->isOpen())
        emit emit sendTournaments({});
    auto byteData = _netMng->reply()->readAll();
    auto jsonDocument = QJsonDocument::fromJson(byteData);
    auto jsonObject = jsonDocument.object();
    auto responseCode = jsonObject.value("response");
    if(responseCode == 0x1)
        return;
    auto tournaments = jsonObject.value("payLoad").toArray();
    QVariantList list;
    for (auto i = tournaments.constBegin(); i != tournaments.constEnd(); ++i) {
        auto jsonData = (*i).toObject();
        auto tournamentId = jsonData.value("id").toString();
        auto tournamentTitle = jsonData.value("title").toString();
        auto tournamentGameMode = jsonData.value("gameMode").toInt();
        auto winnerName = jsonData.value("winnerName").toString();
        auto playersCount = jsonData.value("playersCount").toInt();
        list += {tournamentId,tournamentTitle,tournamentGameMode,winnerName,playersCount};
    }
    emit sendTournaments(list);
}

void RemoteModelsContext::handleAddFTPTournamentReply()
{
    if(!_netMng->reply()->isOpen())
        emit tournamentAssembledAndStored(false);
    auto byteData = _netMng->reply()->readAll();
    auto jsonDocument = QJsonDocument::fromJson(byteData);
    auto jsonObject = jsonDocument.object();
    auto responseCode = jsonObject.value("response");
    if(responseCode == 0x1)
        emit tournamentAssembledAndStored(false);
    else
        emit tournamentAssembledAndStored(true);
}

void RemoteModelsContext::handleDeleteTournamentsReply()
{
    if(!_netMng->reply()->isOpen())
        emit tournamentAssembledAndStored(false);
    auto byteData = _netMng->reply()->readAll();
    auto jsonDocument = QJsonDocument::fromJson(byteData);
    auto jsonObject = jsonDocument.object();
    auto responseCode = jsonObject.value("response");
    if(responseCode == 0x1)
        emit tournamentsDeletedStatus(false);
    else
        emit tournamentsDeletedStatus(true);
}


void RemoteModelsContext::handleRequestPlayersReply()
{
    if(!_netMng->reply()->isOpen())
        emit sendPlayers({});
    auto byteData = _netMng->reply()->readAll();
    auto jsonDocument = QJsonDocument::fromJson(byteData);
    auto jsonObject = jsonDocument.object();
    auto responseCode = jsonObject.value("response");
    if(responseCode == 0x1)
        return;
    QVariantList list;
    auto players = jsonObject.value("payLoad").toArray();
    for (auto i = players.constBegin(); i != players.constEnd(); ++i) {
        auto obj = (*i).toObject();
        auto name = obj.value("playerName").toString();
        auto mail = obj.value("mail").toString();
        list += {name,mail};
    }
    emit sendPlayers(list);
}

void RemoteModelsContext::handleCreatePlayerResponse()
{
    if(!_netMng->reply()->isOpen())
        emit createPlayerResponse(false);
    auto byteData = _netMng->reply()->readAll();
    auto jsonDocument = QJsonDocument::fromJson(byteData);
    auto jsonObject = jsonDocument.object();
    auto responseCode = jsonObject.value("response").toInt();
    if(responseCode == 0x1)
        emit createPlayerResponse(false);
    else
        emit createPlayerResponse(true);
}

void RemoteModelsContext::handleRequestGameModeReply()
{
    if(!_netMng->reply()->isOpen())
        emit createPlayerResponse(false);
    auto byteData = _netMng->reply()->readAll();
    auto jsonDocument = QJsonDocument::fromJson(byteData);
    auto jsonObject = jsonDocument.object();
    auto payLoad = jsonObject.value("payLoad").toObject();
    auto gameMode = payLoad.value("gameMode").toInt();
    auto tournamentId = payLoad.value("tournamentId").toString();
    emit requestAssembleTournament(tournamentId,gameMode);
}

void RemoteModelsContext::handleRequestFtpDetailsReply()
{
    if(!_netMng->reply()->isOpen())
        emit createPlayerResponse(false);
    auto byteData = _netMng->reply()->readAll();
    auto jsonDocument = QJsonDocument::fromJson(byteData);
    auto jsonObject = jsonDocument.object();
    auto responseCode = jsonObject.value("response");
    if(responseCode != 0x2)
    {
        auto msg = jsonObject.value("message").toString();
        throw msg;
    }
    auto payLoad = jsonObject.value("payLoad").toObject();
    /*
     * Assemble basic tournament values
     */
    auto tournament = payLoad.value("tournament").toObject();
    auto tournamentId = tournament.value("id").toString();
    auto winnerId = tournament.value("winnerId").toString();
    /*
     * Asemble ftp tournament values:
     *  - Gamemode
     *  - Keypoint
     *  - Attempts
     *  - Terminalkeycode
     *  - Input hint
     */
    auto ftpDetails = payLoad.value("ftpDetails").toObject();
    auto keyPoint = ftpDetails.value("keyPoint").toInt();
    auto attempt = ftpDetails.value("attempts").toInt();
    auto terminalKeyCode = ftpDetails.value("terminalKeyCode").toInt();
    auto inputHint = ftpDetails.value("inputHint").toInt();
    QVector<int> tournamentValues {
        keyPoint,
        attempt,
        terminalKeyCode,
        inputHint
    };
    emit sendTournamentFtpDetails(tournamentId,
                                  winnerId,
                                  tournamentValues);
}

void RemoteModelsContext::handleFtpIndexesAndScores()
{
    if(!_netMng->reply()->isOpen())
    {
        throw "msg";
    }
    auto byteData = _netMng->reply()->readAll();
    auto jsonDocument = QJsonDocument::fromJson(byteData);
    auto jsonObject = jsonDocument.object();
    auto responseCode = jsonObject.value("response");
    if(responseCode != 0x2)
    {
        auto msg = jsonObject.value("message").toString();
        throw msg;
    }
    auto payLoad = jsonObject.value("payLoad").toObject();
    auto indexes = payLoad.value("indexes").toObject();
    auto totalTurns = indexes.value("totalTurns").toInt();
    auto turns = indexes.value("turns").toInt();
    auto roundIndex = indexes.value("roundIndex").toInt();
    auto setIndex = indexes.value("setIndex").toInt();
    auto attemptIndex = indexes.value("attemptIndex").toInt();

    QVector<PlayerEntity> playerEntities;
    auto playerIdsAndNames = payLoad.value("playerEntities").toArray();
    for (auto i = playerIdsAndNames.constBegin(); i != playerIdsAndNames.constEnd(); ++i) {
        auto value = *i;
        auto object = value.toObject();
        auto playerId = object.value("id").toString();
        auto playerName = object.value("playerName").toString();
        playerEntities << PlayerEntity(playerId,playerName);
    }
    QVector<ScoreEntity> scoreEntities;
    auto playerIdsAndScoreValues = payLoad.value("scoreEntities").toArray();
    for (auto i = playerIdsAndScoreValues.constBegin(); i != playerIdsAndScoreValues.constEnd(); ++i) {
        auto value = *i;
        auto object = value.toObject();
        auto playerId = object.value("playerId").toString();
        auto scoreValue = object.value("scoreValue").toInt();
        scoreEntities << ScoreEntity(playerId,scoreValue);
    }
    emit sendFtpIndexesAndScoreEntities(totalTurns,turns,
                                        roundIndex,setIndex,attemptIndex,
                                        playerEntities,scoreEntities);
}

void RemoteModelsContext::handleFtpTournamentMetaReply()
{
    if(!_netMng->reply()->isOpen())
        emit createPlayerResponse(false);
    auto byteData = _netMng->reply()->readAll();
    auto jsonDocument = QJsonDocument::fromJson(byteData);
    auto jsonObject = jsonDocument.object();
    auto responseCode = jsonObject.value("response").toInt();
    if(responseCode == 0x1)
        throw "Tournament doesn't exists";
    auto payLoad = jsonObject.value("payLoad").toObject();
    auto title = payLoad.value("title").toString();
    auto winnerName = payLoad.value("winnerName").toString();
    auto keyPoint = payLoad.value("keyPoint").toInt();
    auto attempts = payLoad.value("attempts").toInt();
    auto displayHint = payLoad.value("displayHint").toInt();
    auto inputHint = payLoad.value("inputHint").toInt();
    auto gameMode = payLoad.value("gameMode").toInt();
    QVector<QString> stringData = {title,winnerName};
    QVector<int> numericData = {
        gameMode,
        keyPoint,
        attempts,
        displayHint,
        inputHint
    };
    auto playerNames = payLoad.value("assignedPlayerNames").toArray();
    QVector<QString> assignedPlayerNames;
    for (auto i = playerNames.constBegin(); i != playerNames.constEnd(); ++i) {
        auto playerName = (*i).toString();;
        assignedPlayerNames << playerName;
    }
    emit sendTournamentMeta(stringData,
                            numericData,
                            assignedPlayerNames);
}

void RemoteModelsContext::handleAddFtpScoreReply()
{
    auto reply = _netMng->reply();
    if(!reply->isOpen())
        emit scoreNotAddedToDataContext(reply->errorString());
    auto byteData = _netMng->reply()->readAll();
    auto jsonDocument = QJsonDocument::fromJson(byteData);
    auto jsonObject = jsonDocument.object();
    auto responseCode = jsonObject.value("response").toInt();
    if(responseCode == 0x1)
        emit scoreNotAddedToDataContext("Something went wrong!");
    auto payLoad = jsonObject.value("payLoad").toObject();
    auto playerId = payLoad.value("playerId").toString();
    auto point = payLoad.value("point").toInt();
    auto score = payLoad.value("scoreValue").toInt();
    auto keyCode = payLoad.value("keyCode").toInt();
    emit scoreAddedToDataContext(playerId,point,score,keyCode);
}

void RemoteModelsContext::handleSetScoreHintReply()
{
    auto reply = _netMng->reply();
    if(!reply->isOpen())
    {
        // TODO : Implement error functionality here
        return;
    }
    auto byteData = _netMng->reply()->readAll();
    auto jsonDocument = QJsonDocument::fromJson(byteData);
    auto jsonObject = jsonDocument.object();
    auto responseCode = jsonObject.value("response").toInt();
    auto payLoad = jsonObject.value("payLoad").toObject();
    if(responseCode == 0x1)
    {
        auto playerId = payLoad.value("playerId").toString();
        auto message = payLoad.value("message").toString();
        emit scoreHintNotUpdated(playerId,message);
    }
    auto playerId = payLoad.value("playerId").toString();
    auto point = payLoad.value("point").toInt();
    auto score = payLoad.value("scoreValue").toInt();
    auto keyCode = payLoad.value("keyCode").toInt();
    emit scoreHintUpdated(playerId,point,score,keyCode);
}

void RemoteModelsContext::tournamentResetReply()
{
    auto reply = _netMng->reply();
    if(!reply->isOpen())
    {
        // TODO : Implement error functionality here
        emit tournamentResetFailed();
        return;
    }
    auto byteData = _netMng->reply()->readAll();
    auto jsonDocument = QJsonDocument::fromJson(byteData);
    auto jsonObject = jsonDocument.object();
    auto responseCode = jsonObject.value("response").toInt();
    if(responseCode == 0x1)
        emit tournamentResetFailed();
    else
        emit tournamentResetSuccess();
}
