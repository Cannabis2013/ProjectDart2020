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
                {"PlayerId",assignedPlayerId.toString()},
                {"PlayerName",assignedPlayerName},
                {"PlayerPoint",point},
                {"PlayerScore",score},
                {"PlayerAccumulatedScore",accumulatedScore},
                {"ModKeyCode",modKeyCode}
            };
            jsonEntities << jsonEntity;
            if(attempt % attempts == 0)
            {
                attempt = 0;
                round++;
            }
        }
    }
    jsonData["ScoreEntities"] = jsonEntities;
    auto jsonDocument = QJsonDocument(jsonData);
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
    auto tournamentStringId = jsonObject.value("TournamentId").toString();
    auto tournamentId = QUuid::fromString(tournamentStringId);
    auto currentPlayerStringId = jsonObject.value("CurrentPlayerId").toString();
    auto currentPlayerId = QUuid::fromString(currentPlayerStringId);
    auto roundIndex = jsonObject.value("RoundIndex").toInt();
    auto setIndex = jsonObject.value("SetIndex").toInt();
    auto attempt = jsonObject.value("Attempt").toInt();
    auto point = jsonObject.value("Point").toInt();
    auto score = jsonObject.value("Score").toInt();
    auto accumulatedScore = jsonObject.value("AccumulatedScore").toInt();
    auto modKeyCode = jsonObject.value("ModKeyCode").toInt();
    auto isWinnerDetermined = jsonObject.value("IsWinnerDetermined").toBool();

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
    jsonObject["CurrentPlayerName"] = playerName;
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
    auto point = tournamentModelsContext()->ftpScorePointValue(scoreId);
    auto score = tournamentModelsContext()->ftpScoreValue(scoreId);
    auto keyCode = tournamentModelsContext()->scoreKeyCode(scoreId);
    tournamentModelsContext()->setScoreHint(scoreId,hint);
    emit scoreHintUpdated(player,point,score,keyCode);
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
    obj["TournamentId"] = tournamentId.toString(QUuid::WithoutBraces);
    obj["GameMode"] = tournamentModelsContext()->tournamentGameMode(tournamentId);
    obj["Attempts"] = tournamentModelsContext()->tournamentAttempts(tournamentId);
    obj["KeyPoint"] = tournamentModelsContext()->tournamentKeyPoint(tournamentId);
    obj["TerminalKeyCode"] = tournamentModelsContext()->tournamentTerminalKeyCode(tournamentId);
    obj["InputHint"] = tournamentModelsContext()->tournamentInputMode(tournamentId);
    auto winnerId = tournamentModelsContext()->tournamentWinner(tournamentId);
    obj["WinnerId"] = winnerId.toString(QUuid::WithoutBraces);
    /*
     * Get assigned player ids
     */
    QVector<QUuid> assignedPlayersId;
    try {
        assignedPlayersId = tournamentModelsContext()->tournamentAssignedPlayers(tournamentId);
    }  catch (const char *msg) {
        cout << msg << endl;
        throw msg;
    }
    QJsonArray playerIds;
    for (auto assignedPlayerId : assignedPlayersId) {
        auto assignedPlayerStringId = assignedPlayerId.toString(QUuid::WithoutBraces);
        playerIds << assignedPlayerStringId;
    }

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
    obj["TotalTurns"] = indexes.at(0);
    obj["Turns"]  = indexes.at(1);
    obj["RoundIndex"] = indexes.at(2);
    obj["SetIndex"] = indexes.at(3);
    obj["AttemptIndex"] = indexes.at(4);
    QJsonArray playerJsonArray;
    for (int i = 0; i < playerIds.count(); ++i) {
        QJsonObject playerJsonObject;
        playerJsonObject["PlayerId"] = playerIds.at(i).toString(QUuid::WithoutBraces);
        playerJsonObject["PlayerName"] = playerNames.at(i);
        playerJsonArray << playerJsonObject;
    }
    obj["PlayerEntities"] = playerJsonArray;
    auto scores = tournamentModelsContext()->ftpScoreIds(tournament);
    QJsonArray scoresJsonArray;
    for (auto i = scores.constBegin(); i != scores.constEnd(); ++i) {
        auto scoreId = *i;
        QJsonObject playerJsonObject;
        auto playerId = tournamentModelsContext()->scorePlayer(scoreId);
        auto scoreValue = tournamentModelsContext()->ftpScoreValue(scoreId);
        playerJsonObject["PlayerId"] = playerId.toString(QUuid::WithoutBraces);
        playerJsonObject["Score"] = scoreValue;
        scoresJsonArray << playerJsonObject;
    }
    obj["ScoreEntities"] = scoresJsonArray;
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
    obj["Title"] = title;
    obj["WinnerName"] = winnerName;
    obj["GameMode"] = gameMode;
    obj["Attempts"] = attempts;
    obj["KeyPoint"] = keyPoint;
    obj["DisplayHint"] = displayHint;
    obj["InputHint"] = inputHint;
    QJsonArray arr;
    for (auto assignedPlayerName : assignedPlayerNames)
        arr << assignedPlayerName;
    obj["AssignedPlayerNames"] = arr;
    auto json = QJsonDocument(obj).toJson();
    emit sendTournamentMeta(json);
}
