#include "remotemodelscontext.h"



RemoteModelsContext::RemoteModelsContext()
{
    _netMng->setParserService(new UrlParser);
}

void RemoteModelsContext::transmitResponse(const int &response, const QVariantList &args)
{
}

void RemoteModelsContext::handleAddFTPTournament(const QString &title,
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

void RemoteModelsContext::handleAssignPlayersToTournament(const QUuid &tournament, const QList<QUuid> &playersID)
{
}

void RemoteModelsContext::handleDeleteTournaments(const QVector<int> &indexes)
{
}

void RemoteModelsContext::handleRequestAssignedPlayers(const QUuid &tournament)
{
}

void RemoteModelsContext::handleRequestFTPScores(const QUuid &tournament)
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

void RemoteModelsContext::assembleTournamentMetaDataFromId(const QUuid &tournament)
{
}

void RemoteModelsContext::handleAddScore(const QUuid &tournament, const QUuid &player, const QVector<int> &dataValues, const bool &isWinnerDetermined)
{
}

void RemoteModelsContext::handleRequestSetScoreHint(const QUuid &tournament, const QUuid &player, const int &roundIndex, const int &throwIndex, const int &hint)
{
}

void RemoteModelsContext::handleResetTournament(const QUuid &tournament)
{
}

void RemoteModelsContext::handleRequestFtpDetails(const QUuid &tournament)
{
    _netMng->sendGetRequest("GetFtpDetails",
                            QString(),{{"tournamentId",tournament.toString(QUuid::WithoutBraces)}},this,
                            SLOT(handleRequestFtpDetailsReply()));
}

void RemoteModelsContext::handleCreatePlayer(const QString &name, const QString &mail)
{
    QJsonObject obj({{"PlayerName",name},{"PlayerMail",mail}});
    auto data = QJsonDocument(obj).toJson();
    _netMng->sendPostRequest("CreatePlayer",
                             data,QString(),{},this,
                             SLOT(handleCreatePlayerResponse()));
}

void RemoteModelsContext::handleDeletePlayerFromIndex(const int &index)
{
}

void RemoteModelsContext::handleDeletePlayersFromIndexes(const QVector<int> &playerIndexes)
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

void RemoteModelsContext::handleRequestPersistTournamentState()
{
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
    auto gameMode = tournament.value("gameMode").toInt();
    auto winnerId = tournament.value("winnerId").toString();
    QVector<QUuid> tournamentIdAndWinner {
        QUuid::fromString(tournamentId),
        QUuid::fromString(winnerId)
    };
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
        gameMode,
        keyPoint,
        attempt,
        terminalKeyCode,
        inputHint
    };
    auto jsonPlayerIds = payLoad.value("assignedPlayerObjects").toArray();
    QVector<QUuid> assignedPlayerIds;
    QVector<QString> assignedPlayerNames;
    for (auto i = jsonPlayerIds.constBegin(); i != jsonPlayerIds.constEnd(); ++i)
    {
        auto jsonVal = *i;
        auto jsonObj = jsonVal.toObject();
        auto playerStringId = jsonObj.value("id").toString();
        auto playerId = QUuid::fromString(playerStringId);
        assignedPlayerIds << playerId;
        auto playerName = jsonObj.value("playerName").toString();
        assignedPlayerNames << playerName;
    }
    auto jsonPlayerScores = payLoad.value("scores").toArray();
    QVector<int> assignedPlayerScores;
    for (auto i = jsonPlayerScores.constBegin(); i != jsonPlayerScores.constEnd(); ++i)
    {
        auto jsonVal = *i;
        auto jsonObj = jsonVal.toObject();
        auto playerScore = jsonObj.value("score").toInt();
        assignedPlayerScores << playerScore;
    }
    auto totalTurns = payLoad.value("totalTurns").toInt();
    auto turnIndex = payLoad.value("turnIndex").toInt();
    auto roundIndex = payLoad.value("roundIndex").toInt();
    auto setIndex = payLoad.value("setIndex").toInt();
    auto attemptIndex = payLoad.value("attemptIndex").toInt();

    tournamentValues << totalTurns
                     << turnIndex
                     << roundIndex
                     << setIndex
                     << attemptIndex;

    emit sendTournamentFTPDetails(tournamentIdAndWinner,
                                  tournamentValues,
                                  assignedPlayerIds,
                                  assignedPlayerNames,
                                  assignedPlayerScores);
}
