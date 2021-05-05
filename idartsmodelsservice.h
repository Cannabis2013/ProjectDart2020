#ifndef TOURNAMENTMODELINTERFACE_H
#define TOURNAMENTMODELINTERFACE_H

#include <quuid.h>
#include "ipersistence.h"
#include "idartstournament.h"
#include "idartspointinput.h"
#include "idartsscoreinput.h"

class IDartsModelsService
{
public:
    virtual ~IDartsModelsService()= default;
    /*
     * Tournament related section
     */
    virtual const IDartsTournament<QUuid,QString>* getDartsTournamentById(const QUuid&) const = 0;
    virtual const IDartsTournament<QUuid,QString>* assembleDartsTournamentFromJson(const QByteArray& json) = 0;
    virtual QUuid addDartsTournamentToDb(const IDartsTournament<QUuid,QString>*) = 0;
    virtual bool removeTournamentsByIndexes(const QVector<int>& indexes) = 0;
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
    virtual void tournamentAssignPlayers(const QUuid &tournament,
                                         const QVector<QUuid> &player) = 0;
    virtual void tournamentUnAssignPlayer(const QUuid &tournament, const QUuid &player) = 0;
    virtual const QVector<int> dartsIndexes(const QUuid &tournament) = 0;
    /*
     * Points related section
     */
    virtual const IDartsPointInput<QUuid> * assembleDartsInputPointFromJson(const QByteArray& json) = 0;
    virtual void addDartsPoint(const IDartsPointInput<QUuid>*) = 0;
    virtual QVector<const IDartsPointInput<QUuid>*> getDartsPointModelsOrdedByIndexes(const QUuid& tournamentId) const = 0;
    virtual QUuid getDartsPointId(const QUuid &tournament,
                           const QUuid &player ,
                           const int &round,
                           const int &throwIndex,
                           const int &hint) = 0;
    virtual QUuid getDartsPointId(const QUuid &tournament,
                           const QUuid &player ,
                           const int &round,
                           const int &throwIndex) = 0;
    virtual QList<QUuid> dartsPointIds() const  = 0;
    virtual QList<QUuid> dartsPointIds(const QUuid &tournament) const = 0;
    virtual QList<QUuid> dartsPointIds(const QUuid &tournament, const int &roundID) = 0;
    virtual QList<QUuid> dartsPointIds(const QUuid &tournament, const int &roundID, const int &setID) = 0;
    virtual QList<QUuid> dartsPointIds(const int &hint,const QUuid &tournament) = 0;
    virtual QList<QUuid> pointsByPlayerId(const QUuid &tournament, const QUuid &player, const int &hint) = 0;
    virtual int dartsPointsCount(const int &hint) = 0;
    virtual QUuid setDartsPointHint(const QUuid &point, const int &hint) = 0;
    virtual int dartsPointRoundIndex(const QUuid &) = 0;
    virtual int dartsPointSetIndex(const QUuid &) = 0;
    virtual int dartsPointAttemptIndex(const QUuid &) = 0;
    virtual int pointValueFromPointId(const QUuid &) const = 0;
    virtual QUuid tournamentIdFromPointId(const QUuid &playerScore) = 0;
    virtual QUuid playerIdFromPointId(const QUuid &playerScore) const = 0;
    virtual int pointHint(const QUuid &scoreID) = 0;
    virtual int pointKeyCode(const QUuid&) const = 0;
    virtual void removePointById(const QUuid&) = 0;
    virtual void removeHiddenPoints(const QUuid&) = 0;
    virtual int point(const QUuid&, const QUuid&) = 0;
    virtual int point(const QUuid &player) = 0;
    virtual QList<QUuid> pointModels(const QUuid &player) = 0;
    virtual void removePointsByTournamentId(const QUuid &tournament) = 0;
    virtual void removePointModel(const QUuid &playerScore) = 0;
    /*
     * Scores methods
     */
    virtual const IDartsScoreInput<QUuid> * assembleDartsScoresFromJson(const QByteArray& json) = 0;
    virtual void addDartsScore(const IDartsScoreInput<QUuid>*) = 0;
    virtual QUuid getDartsScoreId(const QUuid&,
                           const QUuid&,
                           const int&,
                           const int&) = 0;
    virtual QUuid getDartsScoreId(const QUuid &tournament,
                           const QUuid &,
                           const int &) = 0;
    virtual QList<QUuid> dartsScoreIds() const  = 0;
    virtual QList<QUuid> dartsScoreIds(const QUuid &tournament) const = 0;
    virtual QList<QUuid> dartsScoreIds(const QUuid &tournament, const int &roundID) = 0;
    virtual QList<QUuid> dartsScoreIds(const QUuid &tournament, const int &roundID, const int &setID) = 0;
    virtual QList<QUuid> dartsScoreIds(const int &hint,const QUuid &tournament) = 0;
    virtual QList<QUuid> ScoresByPlayerId(const QUuid &tournament, const QUuid &player, const int &hint) = 0;
    virtual int dartsScoresCount(const int &hint) = 0;
    virtual QUuid setDartsScoreHint(const QUuid &point, const int &hint) = 0;
    virtual int dartsScoreRoundIndex(const QUuid &) = 0;
    virtual int dartsScoreSetIndex(const QUuid &) = 0;
    virtual int ScoreValueFromScoreId(const QUuid &) const = 0;
    virtual QUuid tournamentIdFromScoreId(const QUuid &playerScore) = 0;
    virtual QUuid playerIdFromScoreId(const QUuid &playerScore) const = 0;
    virtual int ScoreHint(const QUuid &scoreID) = 0;
    virtual int ScoreKeyCode(const QUuid&) const = 0;
    virtual void removeScoreById(const QUuid&) = 0;
    virtual void removeHiddenScores(const QUuid&) = 0;
    virtual int Score(const QUuid&, const QUuid&) = 0;
    virtual int Score(const QUuid &player) = 0;
    virtual QList<QUuid> ScoreModels(const QUuid &player) = 0;
    virtual void removeScoresByTournamentId(const QUuid &tournament) = 0;
    virtual void removeScoreModel(const QUuid &playerScore) = 0;
    /*
     * Tournament scores
     */
    virtual QVector<int> dartsPointValuesByTournamentId(const QUuid &tournament) = 0;
};

#endif // TOURNAMENTMODELINTERFACE_H

