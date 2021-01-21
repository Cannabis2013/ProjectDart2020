#ifndef TOURNAMENTMODELINTERFACE_H
#define TOURNAMENTMODELINTERFACE_H

#include <quuid.h>
#include "persistenceinterface.h"

class TournamentModelsContextInterface : public PersistenceInterface
{
public:
    virtual ~TournamentModelsContextInterface()= default;
    /*
     * Tournament related section
     */
    virtual QUuid assembleAndAddFTPTournament(const QString &title,
                                              const QVector<int> &data,
                                              const QVector<QUuid> &playerIds) = 0;
    virtual bool removeTournament(const QUuid &tournament) = 0;
    virtual bool removeTournamentsFromIndexes(const QVector<int>& indexes) = 0;
    virtual QUuid tournamentIdFromIndex(const int &index) = 0;
    virtual QVector<QUuid> tournaments() = 0;
    virtual int tournamentsCount() = 0;
    virtual QString tournamentTitle(const QUuid &tournament) = 0;
    virtual int tournamentNumberOfThrows(const QUuid &tournament) = 0;
    virtual QVector<QUuid> tournamentAssignedPlayers(const QUuid &tournament) = 0;
    virtual int tournamentGameMode(const QUuid &tournament) = 0;
    virtual int tournamentLastThrowKeyCode(const QUuid &tournament) = 0;
    virtual int tournamentKeyPoint(const QUuid &tournament) = 0;
    virtual int tournamentTableViewHint(const QUuid &tournament) = 0;
    virtual int tournamentInputMode(const QUuid &tournament) = 0;
    virtual int tournamentStatus(const QUuid &tournament) = 0;
    virtual QUuid tournamentDeterminedWinner(const QUuid &tournament) = 0;
    virtual void setTournamentDeterminedWinner(const QUuid &tournament, const QUuid &winner) = 0;
    virtual void assignPlayerToTournament(const QUuid &tournament, const QUuid &player) = 0;
    virtual void tournamentRemovePlayer(const QUuid &tournament, const QUuid &player) = 0;
    /*
     * Scores related section
     */
    virtual void addScore(const QUuid &tournament,
                  const QUuid &player,
                  const QList<int> &dataValues,
                  const bool &isWinnerDetermined) = 0;
    virtual QUuid playerScore(const QUuid &tournament, const QUuid &player ,
                              const int &round,
                              const int &throwIndex,
                              const int &hint) = 0;
    virtual QList<QUuid> scores() = 0;
    virtual QList<QUuid> scores(const QUuid &tournament) = 0;
    virtual QList<QUuid> scores(const QUuid &tournament, const int &roundID) = 0;
    virtual QList<QUuid> scores(const QUuid &tournament, const int &roundID, const int &setID) = 0;
    virtual QList<QUuid> scores(const int &hint,const QUuid &tournament) = 0;
    virtual QList<QUuid> playerScores(const QUuid &tournament, const QUuid &player, const int &hint) = 0;
    virtual int playerScoreCount(const int &hint) = 0;
    virtual QUuid setScoreHint(const QUuid &point, const int &hint) = 0;
    virtual QUuid editScore(const QUuid &pointId, const int &value, const int &score,const int &hint) = 0;
    virtual int scoreRoundIndex(const QUuid &playerScore) = 0;
    virtual int scoreSetIndex(const QUuid &playerScore) = 0;
    virtual int scoreThrowIndex(const QUuid &playerScore) = 0;
    virtual int scorePointValue(const QUuid &playerScore) = 0;
    virtual int scoreValue(const QUuid &point) = 0;
    virtual QUuid scoreTournament(const QUuid &playerScore) = 0;
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
    virtual const QList<int> indexes(const QUuid &tournament) = 0;
    /*
     * Tournament scores
     */
    virtual QList<int> tournamentUserScores(const QUuid &tournament) = 0;
};

#endif // TOURNAMENTMODELINTERFACE_H

