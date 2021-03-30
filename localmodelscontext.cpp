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

void LocalModelsContext::addFTPTournament(const QString &title,
                                                          const QVector<int> &data,
                                                          const QVector<int> &assignedPlayerIndexes)
{
    auto playerIds = playerModelsContext()->assemblePlayerIds(assignedPlayerIndexes);
    tournamentModelsContext()->tournamentAssembleAndAddFTP(title,
                                                           data,
                                                           playerIds);
    emit tournamentAssembledAndStored(true);

}

void LocalModelsContext::assignPlayersToTournament(const QUuid &tournament,
                                                             const QList<QUuid> &playersID)
{
    for (auto playerID : playersID)
        tournamentModelsContext()->tournamentAssignPlayer(tournament,playerID);
}

void LocalModelsContext::deleteTournaments(const QVector<int> &indexes)
{
    // TODO: Implement return functionality later
    auto status = tournamentModelsContext()->removeTournamentsFromIndexes(indexes);
    emit tournamentsDeletedSuccess(status);
}

void LocalModelsContext::handleRequestAssignedPlayers(const QUuid &tournament)
{
    auto assignedPlayersID = tournamentModelsContext()->tournamentAssignedPlayers(tournament);
    auto assignedPlayerNames = playerModelsContext()->assemblePlayerNamesFromIds(assignedPlayersID);
    emit sendAssignedPlayerNames(assignedPlayerNames);
}

void LocalModelsContext::handleRequestFtpScores(const QUuid &tournament)
{
    QVariantList list;
    auto numberOfThrows = tournamentModelsContext()->tournamentAttempts(tournament);
    auto assignedPlayerIds = tournamentModelsContext()->tournamentAssignedPlayers(tournament);
    for (auto i = 0;i < assignedPlayerIds.count();i++) {
        auto roundIndex = 1;
        auto attemptIndex = 0;
        auto assignedPlayerId = assignedPlayerIds.at(i);
        auto assignedPlayerName = playerModelsContext()->playerNameFromId(assignedPlayerId);
        while (1)
        {
            QUuid scoreID;
            try {
                scoreID = tournamentModelsContext()->playerScore(tournament,
                                      assignedPlayerId,
                                      roundIndex,
                                      attemptIndex++,
                                      ModelDisplayHint::DisplayHint);
            }  catch (...) {
                break;
            }
            int score;
            int point;
            int keyCode;
            try {
                point = tournamentModelsContext()->scorePointValue(scoreID);
                score = tournamentModelsContext()->scoreValue(scoreID);
                keyCode = tournamentModelsContext()->scoreKeyCode(scoreID);
            } catch (const char *msg) {
                throw msg;
            }
            QVariantList subList = {assignedPlayerName,point,score,keyCode};
            list.append(subList);
            if(attemptIndex % numberOfThrows == 0)
            {
                attemptIndex = 0;
                roundIndex++;
            }
        }
    }
    emit transmitResponse(TournamentModelsContextResponse::EndOfTransmission,{list});
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
void LocalModelsContext::addFtpScore(const QUuid &tournament,
                                        const QUuid &player,
                                        const int &roundIndex,
                                        const int &setIndex,
                                        const int &attemptIndex,
                                        const int &point,
                                        const int &score,
                                        const int &keyCode,
                                        const bool &isWinnerDetermined)
{
    tournamentModelsContext()->addFTPScore(tournament,
                                           player,
                                           roundIndex,
                                           setIndex,
                                           attemptIndex,
                                           point,
                                           score,
                                           keyCode,
                                           isWinnerDetermined);
    emit scoreAddedToDataContext(player,
                                 point,
                                 score);
}

void LocalModelsContext::setFtpScoreHint(const QUuid &tournament,
                                         const QUuid &player,
                                         const int &roundIndex,
                                         const int &attemptIndex,
                                         const int &hint)
{
    QUuid scoreID;
    try {
        scoreID = tournamentModelsContext()->playerScore(tournament,
                                                         player,
                                                         roundIndex,
                                                         attemptIndex);

    }  catch (const char *msg) {
        emit scoreHintNotUpdated(tournament,msg);
        return;
    }
    auto point = tournamentModelsContext()->scorePointValue(scoreID);
    auto score = tournamentModelsContext()->scoreValue(scoreID);
    tournamentModelsContext()->setScoreHint(scoreID,hint);
    emit scoreHintUpdated(player,point,score);
}

void LocalModelsContext::resetTournament(const QUuid &tournament)
{
    /*
     * - Remove models associated to the tournament
     * - Add a round model and a set model
     */
    tournamentModelsContext()->removeTournamentScores(tournament);
    tournamentModelsContext()->tournamentSetWinnerId(tournament,QUuid());
    emit tournamentResetSuccess();
}

void LocalModelsContext::assembleFtpKeyValues(const QUuid &tournamentId)
{
    /*
     * Asemble ftp tournament values:
     *  - Gamemode
     *  - Keypoint
     *  - Attempts
     *  - Terminalkeycode
     *  - Input hint
     */
    QVector<int> tournamentValues {
        tournamentModelsContext()->tournamentGameMode(tournamentId),
        tournamentModelsContext()->tournamentKeyPoint(tournamentId),
        tournamentModelsContext()->tournamentAttempts(tournamentId),
        tournamentModelsContext()->tournamentTerminalKeyCode(tournamentId),
        tournamentModelsContext()->tournamentInputMode(tournamentId)
    };
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
    /*
     *  Get assigned player names
     */
    auto winnerId = tournamentModelsContext()->tournamentWinner(tournamentId);
    emit sendTournamentFtpDetails(tournamentId,
                                  winnerId,
                                  tournamentValues);
}

void LocalModelsContext::createPlayer(const QString &name, const QString &mail)
{
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

void LocalModelsContext::deletePlayerFromIndex(const int &index)
{
    auto status = playerModelsContext()->deletePlayer(index);
    emit playersDeletedStatus(status);
}

void LocalModelsContext::deletePlayersFromIndexes(const QVector<int> &indexes)
{
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

void LocalModelsContext::handleRequestPersistTournamentState()
{
    // Implement save state
    emit tournamentModelsStatePersisted();
}

void LocalModelsContext::assembleFtpIndexesAndScores(const QUuid &tournament)
{
    auto indexes = tournamentModelsContext()->indexes(tournament);
    auto totalTurns = indexes.at(0);
    auto turns  = indexes.at(1);
    auto roundIndex = indexes.at(2);
    auto setIndex = indexes.at(3);
    auto attemptIndex = indexes.at(4);
    auto assignedPlayerIds = tournamentModelsContext()->tournamentAssignedPlayers(tournament);
    auto assignedPlayerNames = playerModelsContext()->assemblePlayerNamesFromIds(assignedPlayerIds);
    auto scores = tournamentModelsContext()->scores(tournament);
    QVector<PlayerEntity> playerEntities;
    for (int i = 0; i < assignedPlayerIds.count(); ++i) {
        auto playerId = assignedPlayerIds.at(i);
        auto playerName = assignedPlayerNames.at(i);
        playerEntities << PlayerEntity(playerId,playerName);
    }
    QVector<ScoreEntity> scoreEntities;
    for (auto i = scores.constBegin(); i != scores.constEnd(); ++i) {
        auto scoreId = *i;
        auto playerId = tournamentModelsContext()->scorePlayer(scoreId);
        auto scoreValue = tournamentModelsContext()->scoreValue(scoreId);
        scoreEntities << ScoreEntity(playerId,scoreValue);
    }
    emit sendFtpIndexesAndScoreEntities(totalTurns,turns,roundIndex,
                                        setIndex,attemptIndex,
                                        playerEntities,scoreEntities);
}

void LocalModelsContext::assembleFTPMetaDataFromId(const QUuid &tournament)
{
    auto title = tournamentModelsContext()->tournamentTitle(tournament);
    // Get winner name from id, if any
    auto winnerId = tournamentModelsContext()->tournamentWinner(tournament);
    auto winnerName = playerModelsContext()->playerNameFromId(winnerId);
    auto gameMode = tournamentModelsContext()->tournamentGameMode(tournament);
    auto keyPoint = tournamentModelsContext()->tournamentKeyPoint(tournament);
    auto attempts = tournamentModelsContext()->tournamentAttempts(tournament);
    auto displayHint = tournamentModelsContext()->tournamentTableViewHint(tournament);
    auto inputMode = tournamentModelsContext()->tournamentInputMode(tournament);
    // Get playernames from ids
    auto playerIds = tournamentModelsContext()->tournamentAssignedPlayers(tournament);
    auto assignedPlayerNames = playerModelsContext()->assemblePlayerNamesFromIds(playerIds);
    QVector<QString> stringMetaData = {
        title,
        winnerName
    };
    QVector<int> numericMetaData = {
        gameMode,
        keyPoint,
        attempts,
        displayHint,
        inputMode
    };
    emit sendTournamentMeta(stringMetaData,
                            numericMetaData,
                            assignedPlayerNames);
}
