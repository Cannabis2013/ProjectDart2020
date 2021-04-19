#include "localmodelscontext.h"

LocalModelsContext::~LocalModelsContext()
{
    delete _tournamentModelsContext;
    delete _playerModelsContext;
}

LocalModelsContext *LocalModelsContext::createInstance()
{
    auto dbContext = new JsonDbContext();
    auto tournamentModelsContext =
            LocalTournamentModelsContext::createInstance()
            ->setTournamentBuilder(new TournamentBuilder())
            ->setScoreBuilder(new ScoreBuilder)
            ->setModelDBContext(dbContext)
            ->setup();
    auto playerModelsContext =
            LocalPlayerModelsContext::createInstance()
            ->setPlayerBuilder(new PlayerModelBuilder())
            ->setModelDBContext(dbContext)
            ->setup();
    return (new LocalModelsContext)
            ->setTournamentModelsContext(tournamentModelsContext)
            ->setPlayerModelsContext(playerModelsContext);
}
TournamentModelsContextInterface* LocalModelsContext::tournamentModelsContext() const
{
    return _tournamentModelsContext;
}

LocalModelsContext* LocalModelsContext::setTournamentModelsContext(TournamentModelsContextInterface *tournamentModelsContext)
{
    _tournamentModelsContext = tournamentModelsContext;
    return this;
}

PlayerModelsContextInterface *LocalModelsContext::playerModelsContext() const
{
    return _playerModelsContext;
}

LocalModelsContext* LocalModelsContext::setPlayerModelsContext(PlayerModelsContextInterface *playerModelsContext)
{
    _playerModelsContext = playerModelsContext;
    return this;
}

void LocalModelsContext::addFTPTournament(const QByteArray& json)
{
    auto jsonObject = QJsonDocument::fromJson(json).object();
    // Extract player-indexes
    QVector<int> assignedPlayerIndexes;
    auto arr = jsonObject["PlayerIndexes"].toArray();
    for (auto jsonVal : arr) {
        auto index = jsonVal.toInt();
        assignedPlayerIndexes << index;
    }
    // Extract ftp tournament values
    auto title = jsonObject.value("Title").toString();
    auto gameMode = jsonObject.value("GameMode").toInt();
    auto keyPoint = jsonObject.value("KeyPoint").toInt();
    auto terminalKeyCode = jsonObject.value("TerminalKeyCode").toInt();
    auto displayHint = jsonObject.value("DisplayHint").toInt();
    auto inputHint = jsonObject.value("InputHint").toInt();
    auto attempts = jsonObject.value("Attempts").toInt();
    // Get playerids
    auto playerIds = playerModelsContext()->assemblePlayerIds(assignedPlayerIndexes);
    tournamentModelsContext()->tournamentAssembleAndAddFTP(title,
                                                           gameMode,
                                                           keyPoint,
                                                           terminalKeyCode,
                                                           displayHint,
                                                           inputHint,
                                                           attempts,
                                                           playerIds);
    emit tournamentAssembledAndStored(true);

}

void LocalModelsContext::assignPlayersToTournament(const QUuid &tournament,
                                                             const QList<QUuid> &playersID)
{
    for (auto playerID : playersID)
        tournamentModelsContext()->tournamentAssignPlayer(tournament,playerID);
}

void LocalModelsContext::deleteTournaments(const QByteArray& json)
{
    QVector<int> indexes;
    auto obj = QJsonDocument::fromJson(json).object();
    auto arr = obj.value("Indexes").toArray();
    for (auto jsonValue : arr) {
        auto index = jsonValue.toInt();
        indexes << index;
    }
    auto status = tournamentModelsContext()->removeTournamentsFromIndexes(indexes);
    emit tournamentsDeletedStatus(status);
}

void LocalModelsContext::handleRequestFtpScores(const QUuid &tournament)
{
    QJsonObject jsonData;
    QJsonArray jsonEntities;
    auto attempts = tournamentModelsContext()->tournamentAttempts(tournament);
    auto assignedPlayerIds = tournamentModelsContext()->tournamentAssignedPlayers(tournament);
    for (auto i = 0;i < assignedPlayerIds.count();i++) {
        auto round = 1;
        auto attempt = 0;
        auto assignedPlayerId = assignedPlayerIds.at(i);
        auto assignedPlayerName = playerModelsContext()->playerNameFromId(assignedPlayerId);
        while (1)
        {
            QUuid scoreId;
            try {
                scoreId = tournamentModelsContext()->ftpScore(tournament,
                                                              assignedPlayerId,
                                                              round,
                                                              attempt++,
                                                              ModelDisplayHint::DisplayHint);
            }  catch (...) {
                break;
            }
            int point;
            int score;
            int accumulatedScore;
            int modKeyCode;
            try {
                point = tournamentModelsContext()->ftpScorePointValue(scoreId);
                score = tournamentModelsContext()->ftpScoreValue(scoreId);
                accumulatedScore = tournamentModelsContext()->ftpAccumulatedScoreValue(scoreId);
                modKeyCode = tournamentModelsContext()->scoreKeyCode(scoreId);
            } catch (const char *msg) {
                throw msg;
            }
            QJsonObject jsonEntity = {
                {"playerId",assignedPlayerId.toString()},
                {"playerName",assignedPlayerName},
                {"playerPoint",point},
                {"playerScore",score},
                {"playerAccumulatedScore",accumulatedScore},
                {"modKeyCode",modKeyCode}
            };
            jsonEntities << jsonEntity;
            if(attempt % attempts == 0)
            {
                attempt = 0;
                round++;
            }
        }
    }
    auto jsonDocument = QJsonDocument(jsonEntities);
    auto jsonString = jsonDocument.toJson(QJsonDocument::Compact);
    emit sendFtpMultiScores(jsonString);
}

void LocalModelsContext::handleRequestTournaments()
{
    QVariantList tournaments;
    auto count = tournamentModelsContext()->tournamentsCount();
    for (int i = 0; i < count; ++i) {
        auto id = tournamentModelsContext()->tournamentIdFromIndex(i);
        auto title = tournamentModelsContext()->tournamentTitle(id);
        auto gameMode = tournamentModelsContext()->tournamentGameMode(id);
        auto playersCount = tournamentModelsContext()->tournamentAssignedPlayers(id).count();
        auto winnerId = tournamentModelsContext()->tournamentWinner(id);
        auto winnerName = playerModelsContext()->playerNameFromId(winnerId);
        tournaments += {id,title,gameMode,winnerName,playersCount};
    }
    emit sendTournaments(tournaments);
}

void LocalModelsContext::handleRequestGameMode(const int &index)
{
    QUuid tournamentId;
    try {
        tournamentId = tournamentModelsContext()->tournamentIdFromIndex(index);
    }  catch (const char *msg) {
        return;
    }
    auto gameMode = tournamentModelsContext()->tournamentGameMode(tournamentId);
    emit requestAssembleTournament(tournamentId,gameMode);
}
void LocalModelsContext::addFtpScore(const QByteArray &json)
{
    auto jsonObject = QJsonDocument::fromJson(json).object();
    auto tournamentStringId = jsonObject.value("tournamentId").toString();
    auto tournamentId = QUuid::fromString(tournamentStringId);
    auto currentPlayerStringId = jsonObject.value("playerId").toString();
    auto currentPlayerId = QUuid::fromString(currentPlayerStringId);
    auto roundIndex = jsonObject.value("roundIndex").toInt();
    auto setIndex = jsonObject.value("setIndex").toInt();
    auto attempt = jsonObject.value("attempt").toInt();
    auto point = jsonObject.value("point").toInt();
    auto score = jsonObject.value("scoreValue").toInt();
    auto accumulatedScore = jsonObject.value("accumulatedScoreValue").toInt();
    auto modKeyCode = jsonObject.value("modKeyCode").toInt();
    auto isWinnerDetermined = jsonObject.value("isWinnerDetermined").toBool();
    tournamentModelsContext()->addFTPScore(tournamentId,
                                           currentPlayerId,
                                           roundIndex,
                                           setIndex,
                                           attempt,
                                           point,
                                           score,
                                           accumulatedScore,
                                           modKeyCode,
                                           isWinnerDetermined);
    auto playerName = playerModelsContext()->playerNameFromId(currentPlayerId);
    jsonObject["playerName"] = playerName;
    auto newJson = QJsonDocument(jsonObject).toJson();

    emit scoreAddedToDataContext(newJson);
}

void LocalModelsContext::setFtpScoreHint(const QUuid &tournament,
                                         const QUuid &player,
                                         const int &roundIndex,
                                         const int &attemptIndex,
                                         const int &hint)
{
    QUuid scoreId;
    try {
        scoreId = tournamentModelsContext()->ftpScore(tournament,
                                                         player,
                                                         roundIndex,
                                                         attemptIndex);

    }  catch (const char *msg) {
        emit scoreHintNotUpdated(tournament,msg);
        return;
    } 
    tournamentModelsContext()->setScoreHint(scoreId,hint);
    QJsonObject obj;
    obj["point"] = tournamentModelsContext()->ftpScorePointValue(scoreId);
    obj["scoreValue"] = tournamentModelsContext()->ftpScoreValue(scoreId);
    obj["modKeyCode"] = tournamentModelsContext()->scoreKeyCode(scoreId);;
    obj["playerId"] = player.toString(QUuid::WithoutBraces);
    auto json = QJsonDocument(obj).toJson();
    emit scoreHintUpdated(json);
}

void LocalModelsContext::resetTournament(const QUuid &tournament)
{
    /*
     * - Remove models associated to the tournament
     * - Reset tournament winner
     */
    tournamentModelsContext()->removeTournamentScores(tournament);
    tournamentModelsContext()->tournamentSetWinnerId(tournament,QUuid());
    emit tournamentResetSuccess();
}

void LocalModelsContext::assembleFtpKeyValues(const QUuid &tournamentId)
{
    QJsonObject obj;
    obj["tournamentId"] = tournamentId.toString(QUuid::WithoutBraces);
    obj["gameMode"] = tournamentModelsContext()->tournamentGameMode(tournamentId);
    obj["attempts"] = tournamentModelsContext()->tournamentAttempts(tournamentId);
    obj["keyPoint"] = tournamentModelsContext()->tournamentKeyPoint(tournamentId);
    obj["terminalKeyCode"] = tournamentModelsContext()->tournamentTerminalKeyCode(tournamentId);
    obj["inputHint"] = tournamentModelsContext()->tournamentInputMode(tournamentId);
    auto winnerId = tournamentModelsContext()->tournamentWinner(tournamentId);
    obj["winnerId"] = winnerId.toString(QUuid::WithoutBraces);
    auto json = QJsonDocument(obj).toJson();
    emit sendTournamentFtpDetails(json);
}

void LocalModelsContext::createPlayer(const QByteArray &json)
{
    auto document = QJsonDocument::fromJson(json);
    auto jsonObject = document.object();
    auto name = jsonObject.value("playerName").toString();
    auto mail = jsonObject.value("playerMail").toString();
    try {
        playerModelsContext()->playerIdFromName(name);
    }  catch (const char *msg) {
        auto id = playerModelsContext()->createPlayer(name,mail);
        auto status = id != QUuid() ? true :
                                      false;
        // Notify front-end
        emit createPlayerResponse(status);
        return;
    }
    emit createPlayerResponse(false);
}

void LocalModelsContext::deletePlayerFromIndex(const QByteArray &json)
{
    auto jsonObject = QJsonDocument::fromJson(json).object();
    auto index = jsonObject.value("index").toInt();
    auto status = playerModelsContext()->deletePlayer(index);
    emit playersDeletedStatus(status);
}

void LocalModelsContext::deletePlayersFromIndexes(const QByteArray &json)
{
    auto jsonArray = QJsonDocument::fromJson(json).array();
    QVector<int> indexes;
    for (auto i = jsonArray.constBegin(); i != jsonArray.constEnd(); ++i) {
        auto index = (*i).toInt();
        indexes << index;
    }
    auto status = playerModelsContext()->deletePlayers(indexes);
    emit playersDeletedStatus(status);
}

void LocalModelsContext::handleRequestPlayersDetails()
{
    auto count = playerModelsContext()->playersCount();
    QVariantList list;
    for (int i = 0; i < count; ++i) {
        auto playerId = playerModelsContext()->playerIdFromIndex(i);
        auto playerName = playerModelsContext()->playerNameFromId(playerId);
        auto mail = playerModelsContext()->playerMailFromId(playerId);
        list += {playerName,mail};
    }
    emit sendPlayers(list);
}

void LocalModelsContext::assembleFtpIndexesAndScores(const QUuid &tournament)
{
    auto indexes = tournamentModelsContext()->indexes(tournament);
    auto playerIds = tournamentModelsContext()->tournamentAssignedPlayers(tournament);
    auto playerNames = playerModelsContext()->assemblePlayerNamesFromIds(playerIds);
    QJsonObject obj;
    QJsonObject indexesObj;
    indexesObj["totalTurns"] = indexes.at(0);
    indexesObj["turns"]  = indexes.at(1);
    indexesObj["roundIndex"] = indexes.at(2);
    indexesObj["setIndex"] = indexes.at(3);
    indexesObj["attemptIndex"] = indexes.at(4);
    obj["indexes"] = indexesObj;
    QJsonArray playerJsonArray;
    for (int i = 0; i < playerIds.count(); ++i) {
        QJsonObject playerJsonObject;
        playerJsonObject["playerId"] = playerIds.at(i).toString(QUuid::WithoutBraces);
        playerJsonObject["playerName"] = playerNames.at(i);
        playerJsonArray << playerJsonObject;
    }
    obj["playerEntities"] = playerJsonArray;
    auto scores = tournamentModelsContext()->ftpScoreIds(tournament);
    QJsonArray scoresJsonArray;
    for (auto i = scores.constBegin(); i != scores.constEnd(); ++i) {
        auto scoreId = *i;
        QJsonObject playerJsonObject;
        auto playerId = tournamentModelsContext()->scorePlayer(scoreId);
        auto scoreValue = tournamentModelsContext()->ftpScoreValue(scoreId);
        playerJsonObject["playerId"] = playerId.toString(QUuid::WithoutBraces);
        playerJsonObject["score"] = scoreValue;
        scoresJsonArray << playerJsonObject;
    }
    obj["scoreEntities"] = scoresJsonArray;
    auto json = QJsonDocument(obj).toJson();
    emit sendFtpIndexesAndScoreEntities(json);
}

void LocalModelsContext::assembleFtpMetaDataFromId(const QUuid &tournament)
{
    auto title = tournamentModelsContext()->tournamentTitle(tournament);
    // Get winner name from id, if any
    auto winnerId = tournamentModelsContext()->tournamentWinner(tournament);
    auto winnerName = playerModelsContext()->playerNameFromId(winnerId);
    auto gameMode = tournamentModelsContext()->tournamentGameMode(tournament);
    auto keyPoint = tournamentModelsContext()->tournamentKeyPoint(tournament);
    auto attempts = tournamentModelsContext()->tournamentAttempts(tournament);
    auto displayHint = tournamentModelsContext()->tournamentTableViewHint(tournament);
    auto inputHint = tournamentModelsContext()->tournamentInputMode(tournament);
    // Get playernames from ids
    auto playerIds = tournamentModelsContext()->tournamentAssignedPlayers(tournament);
    auto assignedPlayerNames = playerModelsContext()->assemblePlayerNamesFromIds(playerIds);
    QJsonObject obj;
    obj["title"] = title;
    obj["winnerName"] = winnerName;
    obj["gameMode"] = gameMode;
    obj["attempts"] = attempts;
    obj["keyPoint"] = keyPoint;
    obj["displayHint"] = displayHint;
    obj["inputHint"] = inputHint;
    QJsonArray arr;
    for (auto assignedPlayerName : assignedPlayerNames)
        arr << assignedPlayerName;
    obj["assignedPlayerNames"] = arr;
    auto json = QJsonDocument(obj).toJson();
    emit sendTournamentMeta(json);
}
