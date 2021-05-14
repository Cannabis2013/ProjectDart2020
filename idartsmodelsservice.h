#ifndef TOURNAMENTMODELINTERFACE_H
#define TOURNAMENTMODELINTERFACE_H

#include <quuid.h>
#include "ipersistence.h"
#include "idartstournament.h"
#include "idartspointinput.h"
#include "idartsscoreinput.h"
#include "idartspointindexes.h"
#include "idartsscoreindexes.h"

class IDartsModelsService
{
public:
    /*
     * Tournament related section
     */
    virtual const IDartsTournament* dartsTournamentByIndex(const int&) const = 0;
    virtual QVector<const IDartsTournament*> dartsTournamentModels() const = 0;
    virtual const IDartsTournament* dartsTournamentModelById(const QUuid&) const = 0;
    virtual QUuid addDartsTournamentToDb(const IDartsTournament*) = 0;
    virtual bool removeTournamentsByIndexes(const QVector<int>& indexes) const = 0;
    virtual void tournamentSetWinnerId(const QUuid &tournament, const QUuid &winner) = 0;
    virtual void tournamentAssignPlayer(const QUuid &tournament, const QUuid &player) = 0;
    virtual void tournamentAssignPlayers(const QUuid &tournament,
                                         const QVector<QUuid> &player) = 0;
    virtual void tournamentUnAssignPlayer(const QUuid &tournament, const QUuid &player) = 0;
    /*
     * Points related section
     */
    virtual QVector<const IDartsPointInput*> dartsPointModelsByTournamentId(const QUuid& tournamentId) const = 0;
    virtual const IDartsPointIndexes* dartsPointIndexes(const QUuid &tournamentId) const = 0;
    virtual void addDartsPoint(const IDartsPointInput*) = 0;
    virtual QVector<const IDartsPointInput*> getDartsPointModelsOrdedByIndexes(const QUuid& tournamentId) const = 0;
    virtual const IDartsPointInput* getDartsPointModelById(const QUuid& id) const = 0;
    virtual int dartsPointsCount(const QUuid&,const int&) const = 0;
    virtual int dartsScoreCount(const QUuid&,const int&) const = 0;
    virtual const IDartsPointInput* setDartsPointHint(const QUuid&,const QUuid&,
                                                      const int&,const int&,
                                                      const int&) = 0;
    virtual void removePointById(const QUuid&) = 0;
    virtual void removeHiddenPoints(const QUuid&) = 0;
    virtual void removePointsByTournamentId(const QUuid&) = 0;
    virtual void removePointModel(const QUuid &playerScore) = 0;
    /*
     * Scores methods
     */
    virtual QVector<const IDartsScoreInput*> dartsScoreModelsByTournamentIdAndHint(const QUuid&, const int&) const = 0;
    virtual const IDartsScoreIndexes* dartsScoreIndexes(const QUuid&) const = 0;
    virtual void addDartsScore(const IDartsScoreInput*) = 0;
    virtual int dartsScoresCount(const int &hint) const = 0;
    virtual const IDartsScoreInput* setDartsScoreHint(const QUuid &tournamentId,
                                                      const QUuid &playerId,
                                                      const int &roundIndex,
                                                      const int &hint) = 0;
    virtual void removeScoreById(const QUuid&) = 0;
    virtual void removeHiddenScores(const QUuid&) = 0;
    virtual void removeScoresByTournamentId(const QUuid &tournament) = 0;
    virtual void removeScoreModel(const QUuid &playerScore) = 0;
};

#endif // TOURNAMENTMODELINTERFACE_H

