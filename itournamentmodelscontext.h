#ifndef TOURNAMENTMODELINTERFACE_H
#define TOURNAMENTMODELINTERFACE_H

#include <quuid.h>
#include "persistenceinterface.h"

class ITournamentModelsContext
{
public:
    virtual ~ITournamentModelsContext()= default;
    /*
     * Tournament related section
     */
    virtual QUuid tournamentAssembleAndAddFTP(const QString &title,
                                              const int& gameMode,
                                              const int& keyPoint,
                                              const int& winKeyCode,
                                              const int& displayHint,
                                              const int& inputHint,
                                              const int& attempts,
                                              const QVector<QUuid> &playerIds) = 0;
    virtual bool removeTournament(const QUuid &tournament) = 0;
    virtual bool removeTournamentsFromIndexes(const QVector<int>& indexes) = 0;
    virtual QUuid tournamentIdFromIndex(const int &index) = 0;
    virtual QVector<QUuid> tournaments() = 0;
    virtual int tournamentsCount() = 0;
    virtual QString tournamentTitle(const QUuid &tournament) = 0;
    virtual int tournamentAttempts(const QUuid &tournament) = 0;
    virtual QVector<QUuid> tournamentAssignedPlayers(const QUuid &tournament) = 0;
    virtual int tournamentGameMode(const QUuid &tournament) = 0;
    virtual int tournamentTerminalKeyCode(const QUuid &tournament) = 0;
    virtual int tournamentKeyPoint(const QUuid &tournament) = 0;
    virtual int tournamentTableViewHint(const QUuid &tournament) = 0;
    virtual int tournamentInputMode(const QUuid &tournament) = 0;
    virtual int tournamentStatus(const QUuid &tournament) = 0;
    virtual QUuid tournamentWinner(const QUuid &tournament) = 0;
    virtual void tournamentSetWinnerId(const QUuid &tournament, const QUuid &winner) = 0;
    virtual void tournamentAssignPlayer(const QUuid &tournament, const QUuid &player) = 0;
    virtual void tournamentUnAssignPlayer(const QUuid &tournament, const QUuid &player) = 0;
    /*
     * Scores related section
     */
    virtual void addDartsPoint(const QUuid &tournament,
                             const QUuid &player,
                             const int &roundIndex,
                             const int &setIndex,
                             const int &attemptIndex,
                             const int &point,
                             const int &score,
                             const int &keyCode,
                             const bool &isWinnerDetermined) = 0;
    virtual QUuid ftpScore(const QUuid &tournament,
                           const QUuid &player ,
                           const int &round,
                           const int &throwIndex,
                           const int &hint) = 0;
    virtual QUuid ftpScore(const QUuid &tournament,
                           const QUuid &player ,
                           const int &round,
                           const int &throwIndex) = 0;
    virtual QList<QUuid> ftpScoreIds() = 0;
    virtual QList<QUuid> ftpScoreIds(const QUuid &tournament) = 0;
    virtual QList<QUuid> ftpScoreIds(const QUuid &tournament, const int &roundID) = 0;
    virtual QList<QUuid> ftpScoreIds(const QUuid &tournament, const int &roundID, const int &setID) = 0;
    virtual QList<QUuid> ftpScoreIds(const int &hint,const QUuid &tournament) = 0;
    virtual QList<QUuid> playerScores(const QUuid &tournament, const QUuid &player, const int &hint) = 0;
    virtual int ftpScoresCount(const int &hint) = 0;
    virtual QUuid setDartsPointHint(const QUuid &point, const int &hint) = 0;
    virtual QUuid editScore(const QUuid &pointId, const int &value, const int &score,const int &hint) = 0;
    virtual int ftpScoreRoundIndex(const QUuid &) = 0;
    virtual int ftpScoreSetIndex(const QUuid &) = 0;
    virtual int ftpScoreAttemptIndex(const QUuid &) = 0;
    virtual int ftpScorePointValue(const QUuid &) = 0;
    virtual int ftpScoreValue(const QUuid &) = 0;
    virtual int ftpAccumulatedScoreValue(const QUuid&) = 0;
    virtual QUuid ftpScoreTournament(const QUuid &playerScore) = 0;
    virtual QUuid scorePlayer(const QUuid &playerScore) = 0;
    virtual int scoreHint(const QUuid &scoreID) = 0;
    virtual int scoreKeyCode(const QUuid &scoreID) = 0;
    virtual bool removeScore(const QUuid &point) = 0;
    virtual void removePlayerScore(const QUuid &point) = 0;
    virtual void removeHiddenScores(const QUuid &tournament) = 0;
    virtual int score(const QUuid &tournament, const QUuid &player) = 0;
    virtual int score(const QUuid &player) = 0;
    virtual QList<QUuid> pointModels(const QUuid &player) = 0;
    virtual void removeTournamentScores(const QUuid &tournament) = 0;
    virtual void removeTournamentModel(const QUuid &tournament) = 0;
    virtual void removePointModel(const QUuid &playerScore) = 0;
    /*
     * Tournament indexes
     */
    virtual const QVector<int> indexes(const QUuid &tournament) = 0;
    /*
     * Tournament scores
     */
    virtual QVector<int> tournamentUserScores(const QUuid &tournament) = 0;
};

#endif // TOURNAMENTMODELINTERFACE_H

