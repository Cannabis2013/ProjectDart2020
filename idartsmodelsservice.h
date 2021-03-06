#ifndef TOURNAMENTMODELINTERFACE_H
#define TOURNAMENTMODELINTERFACE_H

#include <quuid.h>
#include "ipersistence.h"
#include "idartstournament.h"
#include "idartspointinput.h"
#include "idartsscoreinput.h"
#include "idartspointindexes.h"
#include "idartsscoreindexes.h"

namespace DartsModelsContext {
    class IDartsModelsService
    {
    public:

        /*
         * Public types
         */
        typedef IDartsInput PlayerInput;
        typedef QVector<const IDartsInput*> PlayerInputs;
        /*
         * Tournament related section
         */
        virtual const IDartsTournament* dartsTournamentByIndex(const int&) const = 0;
        virtual QVector<const IDartsTournament*> dartsTournamentModels() const = 0;
        virtual const IDartsTournament* dartsTournamentModelById(const QUuid&) const = 0;
        virtual QUuid addDartsTournamentToDb(const IDartsTournament*) = 0;
        virtual bool removeTournamentsByIndexes(const QVector<int>& indexes) const = 0;
        virtual void tournamentSetWinnerId(const QUuid &tournament, const QUuid &winner) = 0;
        virtual const IDartsTournament* assignPlayerIdsToDartsTournament(const IDartsTournament*,
                                                                         const QVector<QUuid>&) const = 0;
        /*
         * Points related section
         */
        virtual PlayerInputs dartsPointModelsByTournamentId(const QUuid& tournamentId) const = 0;
        virtual const IDartsPointIndexes* dartsPointIndexes(const QUuid &tournamentId) const = 0;
        virtual void addDartsPoint(const PlayerInput*) = 0;
        virtual PlayerInputs getDartsPointModelsOrdedByIndexes(const QUuid& tournamentId) const = 0;
        virtual const PlayerInput* getDartsPointModelById(const QUuid& id) const = 0;
        virtual int dartsPointsCount(const QUuid&,const int&) const = 0;
        virtual int dartsScoreCount(const QUuid&,const int&) const = 0;
        virtual const PlayerInput* setDartsPointHint(const QUuid&,const QUuid&,
                                                          const int&,const int&,
                                                          const int&) = 0;
        virtual void removePointById(const QUuid&) = 0;
        virtual void removeHiddenPoints(const QUuid&) = 0;
        virtual void removePointsByTournamentId(const QUuid&) = 0;
        /*
         * Scores methods
         */
        virtual const PlayerInput* dartsScoreModel(const QUuid&, const QUuid&, const int&) const = 0;
        virtual PlayerInputs dartsScoreModelsByTournamentIdAndHint(const QUuid&, const int&) const = 0;
        virtual const DartsModelsContext::IDartsScoreIndexes* dartsScoreIndexes(const QUuid&) const = 0;
        virtual void addDartsScore(const IDartsScoreInput*) = 0;
        virtual int dartsScoresCount(const int &hint) const = 0;
        virtual const PlayerInput* setDartsScoreHint(const PlayerInput*,
                                                          const int &hint) = 0;
        virtual void removeScoreById(const QUuid&) = 0;
        virtual void removeHiddenScores(const QUuid&) = 0;
        virtual void removeScoresByTournamentId(const QUuid &tournament) = 0;
        virtual void removeScoreModel(const QUuid &playerScore) = 0;
    };
}


#endif // TOURNAMENTMODELINTERFACE_H

