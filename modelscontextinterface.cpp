#include "modelscontextinterface.h"

ModelsContextInterface::ModelsContextInterface()
{

}

ModelsContextInterface *ModelsContextInterface::createInstance()
{
    return new ModelsContextInterface();
}
TournamentModelsContextInterface* ModelsContextInterface::tournamentModelsContext() const
{
    return _tournamentModelsContext;
}

ModelsContextInterface* ModelsContextInterface::setTournamentModelsContext(TournamentModelsContextInterface *tournamentModelsContext)
{
    _tournamentModelsContext = tournamentModelsContext;
    return this;
}

PlayerModelsContextInterface *ModelsContextInterface::playerModelsContext() const
{
    return _playerModelsContext;
}

ModelsContextInterface* ModelsContextInterface::setPlayerModelsContext(PlayerModelsContextInterface *playerModelsContext)
{
    _playerModelsContext = playerModelsContext;
    return this;
}

void ModelsContextInterface::handleRequestForAddFTPTournament(const QString &title,
                                                              const QVector<int> &data,
                                                              const QVector<int> &assignedPlayerIndexes)
{
    auto playerIds = playerModelsContext()->assemblePlayerIds(assignedPlayerIndexes);
    tournamentModelsContext()->assembleAndAddFTPTournament(title,
                                                           data,
                                                           playerIds);

}

void ModelsContextInterface::handleAssignPlayersToTournament(const QUuid &tournament,
                                                             const QList<QUuid> &playersID)
{
    for (auto playerID : playersID)
        tournamentModelsContext()->assignPlayerToTournament(tournament,playerID);
}

void ModelsContextInterface::handleDeleteTournaments(const QVector<int> &indexes)
{
    // TODO: Implement return functionality later
    auto status = tournamentModelsContext()->removeTournamentsFromIndexes(indexes);
    emit tournamentsDeletedSuccess(status);
}

void ModelsContextInterface::handleRequestAssignedPlayers(const QUuid &tournament)
{
    auto assignedPlayersID = tournamentModelsContext()->tournamentAssignedPlayers(tournament);
    auto assignedPlayerNames = playerModelsContext()->assemblePlayerNamesFromIds(assignedPlayersID);
    emit sendAssignedPlayerNames(assignedPlayerNames);
}

void ModelsContextInterface::handleTransmitPlayerScores(const QUuid &tournament)
{
    QVariantList list;
    auto numberOfThrows = tournamentModelsContext()->tournamentNumberOfThrows(tournament);
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

void ModelsContextInterface::handleTransmitTournamentData()
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

void ModelsContextInterface::handleRequestTournamentGameMode(const int &index)
{
    QUuid tournamentId;
    try {
        tournamentId = tournamentModelsContext()->tournamentIdFromIndex(index);
    }  catch (const char *msg) {
        return;
    }
    auto gameMode = tournamentModelsContext()->tournamentGameMode(tournamentId);
    emit sendTournamentGameMode(tournamentId,gameMode);
}
void ModelsContextInterface::handleAddScore(const QUuid &tournament,
                                            const QUuid &player,
                                            const QList<int> &dataValues,
                                            const bool &isWinnerDetermined)
{
    tournamentModelsContext()->addScore(tournament,player,dataValues,isWinnerDetermined);
    emit scoreAddedToDataContext(player,dataValues.at(3),dataValues.at(4));
}

void ModelsContextInterface::handleRequestSetScoreHint(const QUuid &tournament,
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

void ModelsContextInterface::handleResetTournament(const QUuid &tournament)
{
    /*
     * - Remove models associated to the tournament
     * - Add a round model and a set model
     */
    tournamentModelsContext()->removeTournamentScores(tournament);
    tournamentModelsContext()->setTournamentDeterminedWinner(tournament,QUuid());
    emit tournamentResetSuccess();
}

void ModelsContextInterface::handleRequestFTPDetails(const QUuid &tournament)
{
    QList<int> tournamentValues = {
        tournamentModelsContext()->tournamentGameMode(tournament),
        tournamentModelsContext()->tournamentKeyPoint(tournament),
        tournamentModelsContext()->tournamentNumberOfThrows(tournament),
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
    auto winnerID = tournamentModelsContext()->tournamentDeterminedWinner(tournament);
    tournamentValues += tournamentModelsContext()->indexes(tournament);
    tournamentValues += tournamentModelsContext()->tournamentUserScores(tournament);
    emit sendTournamentFTPDetails(tournament,
                                  winnerID,tournamentValues.toVector(),
                                  assignedPlayersId,
                                  assignedPlayerNames);
}

void ModelsContextInterface::handleCreatePlayer(const QString &name, const QString &mail)
{
    auto id = playerModelsContext()->createPlayer(name,mail);
    auto status = id != QUuid() ? true :
                                  false;
    // Persist state change
    playerModelsContext()->write();
    // Notify front-end
    emit confirmPlayerCreated(status);
}

void ModelsContextInterface::handleDeletePlayerFromIndex(const int &index)
{
    auto status = playerModelsContext()->deletePlayer(index);
    emit playersDeletedStatus(status);
}

void ModelsContextInterface::handleDeletePlayersFromIndexes(const QVector<int> &indexes)
{
    auto status = playerModelsContext()->deletePlayers(indexes);
    emit playersDeletedStatus(status);
}

void ModelsContextInterface::handleRequestPlayersDetails()
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

void ModelsContextInterface::handleRequestForFTPMetaData(const QUuid &tournament)
{
    auto title = tournamentModelsContext()->tournamentTitle(tournament);
    // Get winner name from id, if any
    auto winnerId = tournamentModelsContext()->tournamentDeterminedWinner(tournament);
    auto winnerName = playerModelsContext()->playerNameFromId(winnerId);
    auto gameMode = tournamentModelsContext()->tournamentGameMode(tournament);
    auto keyPoint = tournamentModelsContext()->tournamentKeyPoint(tournament);
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
        modelTableViewHint,
        inputMode
    };
    emit sendTournamentMeta(stringMetaData,
                            numericMetaData,
                            assignedPlayerNames);
}
