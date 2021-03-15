#include "defaultmodelscontextinterface.h"

DefaultModelsContextInterface::~DefaultModelsContextInterface()
{
    delete _tournamentModelsContext;
    delete _playerModelsContext;
}

DefaultModelsContextInterface *DefaultModelsContextInterface::createInstance()
{
    auto dbContext = new DefaultModelsDbContext();
    auto tournamentModelsContext =
            LocalTournamentModelsContext::createInstance()
            ->setModelBuilder(new TournamentModelBuilder())
            ->setModelDBContext(dbContext)
            ->setup();
    auto playerModelsContext =
            LocalPlayerModelsContext::createInstance()
            ->setPlayerBuilder(new PlayerModelBuilder())
            ->setModelDBContext(dbContext)
            ->setup();
    return (new DefaultModelsContextInterface)
            ->setTournamentModelsContext(tournamentModelsContext)
            ->setPlayerModelsContext(playerModelsContext);
}
TournamentModelsContextInterface* DefaultModelsContextInterface::tournamentModelsContext() const
{
    return _tournamentModelsContext;
}

DefaultModelsContextInterface* DefaultModelsContextInterface::setTournamentModelsContext(TournamentModelsContextInterface *tournamentModelsContext)
{
    _tournamentModelsContext = tournamentModelsContext;
    return this;
}

PlayerModelsContextInterface *DefaultModelsContextInterface::playerModelsContext() const
{
    return _playerModelsContext;
}

DefaultModelsContextInterface* DefaultModelsContextInterface::setPlayerModelsContext(PlayerModelsContextInterface *playerModelsContext)
{
    _playerModelsContext = playerModelsContext;
    return this;
}

void DefaultModelsContextInterface::handleRequestForAddFTPTournament(const QString &title,
                                                              const QVector<int> &data,
                                                              const QVector<int> &assignedPlayerIndexes)
{
    auto playerIds = playerModelsContext()->assemblePlayerIds(assignedPlayerIndexes);
    tournamentModelsContext()->assembleAndAddFTPTournament(title,
                                                          data,
                                                           playerIds);
    emit transmitResponse(TournamentModelsContextResponse::TournamentCreatedOK,{});

}

void DefaultModelsContextInterface::handleAssignPlayersToTournament(const QUuid &tournament,
                                                             const QList<QUuid> &playersID)
{
    for (auto playerID : playersID)
        tournamentModelsContext()->assignPlayerToTournament(tournament,playerID);
}

void DefaultModelsContextInterface::handleDeleteTournaments(const QVector<int> &indexes)
{
    // TODO: Implement return functionality later
    auto status = tournamentModelsContext()->removeTournamentsFromIndexes(indexes);
    emit tournamentsDeletedSuccess(status);
}

void DefaultModelsContextInterface::handleRequestAssignedPlayers(const QUuid &tournament)
{
    auto assignedPlayersID = tournamentModelsContext()->tournamentAssignedPlayers(tournament);
    auto assignedPlayerNames = playerModelsContext()->assemblePlayerNamesFromIds(assignedPlayersID);
    emit sendAssignedPlayerNames(assignedPlayerNames);
}

void DefaultModelsContextInterface::handleTransmitPlayerScores(const QUuid &tournament)
{
    QVariantList list;
    auto numberOfThrows = tournamentModelsContext()->tournamentAttempts(tournament);
    auto assignedPlayerIds = tournamentModelsContext()->tournamentAssignedPlayers(tournament);
    for (auto i = 0;i < assignedPlayerIds.count();i++) {
        auto roundIndex = 1;
        auto throwIndex = 0;
        auto assignedPlayerId = assignedPlayerIds.at(i);
        auto assignedPlayerName = playerModelsContext()->playerNameFromId(assignedPlayerId);
        while (1)
        {
            QUuid scoreID;
            try {
                scoreID = tournamentModelsContext()->playerScore(tournament,
                                      assignedPlayerId,
                                      roundIndex,
                                      throwIndex++,
                                      DisplayHint);
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
            if(throwIndex % numberOfThrows == 0)
            {
                throwIndex = 0;
                roundIndex++;
            }
        }
    }
    emit transmitResponse(TournamentModelsContextResponse::EndOfTransmission,{list});
}

void DefaultModelsContextInterface::handleTransmitTournamentData()
{
    auto count = tournamentModelsContext()->tournamentsCount();
    for (int i = 0; i < count; ++i) {
        auto id = tournamentModelsContext()->tournamentIdFromIndex(i);
        auto title = tournamentModelsContext()->tournamentTitle(id);
        auto gameMode = tournamentModelsContext()->tournamentGameMode(id);
        auto playersCount = tournamentModelsContext()->tournamentAssignedPlayers(id).count();
        emit sendTournament(title,gameMode,playersCount);
    }
    emit lastTournamentTransmitted();
}

void DefaultModelsContextInterface::handleRequestTournamentGameMode(const int &index)
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
void DefaultModelsContextInterface::handleAddScore(const QUuid &tournament,
                                            const QUuid &player,
                                            const QVector<int> &dataValues,
                                            const bool &isWinnerDetermined)
{
    tournamentModelsContext()->addScore(tournament,
                                        player,
                                        dataValues,
                                        isWinnerDetermined);
    emit scoreAddedToDataContext(player,dataValues.at(3),dataValues.at(4));
}

void DefaultModelsContextInterface::handleRequestSetScoreHint(const QUuid &tournament,
                                                      const QUuid &player,
                                                      const int &roundIndex,
                                                      const int &throwIndex, const int &hint)
{
    QUuid scoreID;
    try {
        scoreID = tournamentModelsContext()->playerScore(tournament,
                              player,
                              roundIndex,
                              throwIndex,
                              ModelDisplayHint::allHints);

    }  catch (const char *msg) {
        emit scoreHintNotUpdated(tournament,msg);
        return;
    }
    auto point = tournamentModelsContext()->scorePointValue(scoreID);
    auto score = tournamentModelsContext()->scoreValue(scoreID);
    tournamentModelsContext()->setScoreHint(scoreID,hint);
    emit scoreHintUpdated(player,point,score);
}

void DefaultModelsContextInterface::handleResetTournament(const QUuid &tournament)
{
    /*
     * - Remove models associated to the tournament
     * - Add a round model and a set model
     */
    tournamentModelsContext()->removeTournamentScores(tournament);
    tournamentModelsContext()->setTournamentDeterminedWinner(tournament,QUuid());
    emit tournamentResetSuccess();
}

void DefaultModelsContextInterface::handleRequestFTPDetails(const QUuid &tournament)
{
    QVector<int> tournamentValues = {
        tournamentModelsContext()->tournamentGameMode(tournament),
        tournamentModelsContext()->tournamentKeyPoint(tournament),
        tournamentModelsContext()->tournamentAttempts(tournament),
        tournamentModelsContext()->tournamentLastThrowKeyCode(tournament),
        tournamentModelsContext()->tournamentInputMode(tournament)
    };
    QVector<QUuid> assignedPlayersId;
    try {
        assignedPlayersId = tournamentModelsContext()->tournamentAssignedPlayers(tournament);
    }  catch (const char *msg) {
        return;
    }
    auto assignedPlayerNames = playerModelsContext()->assemblePlayerNamesFromIds(assignedPlayersId);
    auto winnerId = tournamentModelsContext()->tournamentDeterminedWinner(tournament);
    QVector<QUuid> tournamentIdAndWinner = {
        tournament,
        winnerId
    };
    tournamentValues += tournamentModelsContext()->indexes(tournament);
    tournamentValues += tournamentModelsContext()->tournamentUserScores(tournament);
    emit sendTournamentFTPDetails(tournamentIdAndWinner,
                                  tournamentValues,
                                  assignedPlayersId,
                                  assignedPlayerNames);
}

void DefaultModelsContextInterface::handleCreatePlayer(const QString &name, const QString &mail)
{
    auto id = playerModelsContext()->createPlayer(name,mail);
    auto status = id != QUuid() ? true :
                                  false;
    // Persist state change
    playerModelsContext()->write();
    // Notify front-end
    emit confirmPlayerCreated(status);
}

void DefaultModelsContextInterface::handleDeletePlayerFromIndex(const int &index)
{
    auto status = playerModelsContext()->deletePlayer(index);
    emit playersDeletedStatus(status);
}

void DefaultModelsContextInterface::handleDeletePlayersFromIndexes(const QVector<int> &indexes)
{
    auto status = playerModelsContext()->deletePlayers(indexes);
    emit playersDeletedStatus(status);
}

void DefaultModelsContextInterface::handleRequestPlayersDetails()
{
    auto count = playerModelsContext()->playersCount();
    for (int i = 0; i < count; ++i) {
        auto playerId = playerModelsContext()->playerIdFromIndex(i);
        auto playerName = playerModelsContext()->playerNameFromId(playerId);
        auto mail = playerModelsContext()->playerMailFromId(playerId);
        emit sendPlayerDetails(playerName,mail);
    }
    emit lastPlayerDetailTransmitted();
}

void DefaultModelsContextInterface::handleRequestPersistTournamentState()
{
    tournamentModelsContext()->write();
    emit tournamentModelsStatePersisted();
}

void DefaultModelsContextInterface::assembleTournamentMetaDataFromId(const QUuid &tournament)
{
    auto title = tournamentModelsContext()->tournamentTitle(tournament);
    // Get winner name from id, if any
    auto winnerId = tournamentModelsContext()->tournamentDeterminedWinner(tournament);
    auto winnerName = playerModelsContext()->playerNameFromId(winnerId);
    auto gameMode = tournamentModelsContext()->tournamentGameMode(tournament);
    auto keyPoint = tournamentModelsContext()->tournamentKeyPoint(tournament);
    auto attempts = tournamentModelsContext()->tournamentAttempts(tournament);
    auto modelTableViewHint = tournamentModelsContext()->tournamentTableViewHint(tournament);
    auto inputMode = tournamentModelsContext()->tournamentInputMode(tournament);
    // Get playernames from ids
    auto playersId = tournamentModelsContext()->tournamentAssignedPlayers(tournament);
    auto assignedPlayerNames = playerModelsContext()->assemblePlayerNamesFromIds(playersId);
    QVector<QString> stringMetaData = {
        title,
        winnerName
    };
    QVector<int> numericMetaData = {
        gameMode,
        keyPoint,
        attempts,
        modelTableViewHint,
        inputMode
    };
    emit sendTournamentMeta(stringMetaData,
                            numericMetaData,
                            assignedPlayerNames);
}
