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
        virtual const PlayerInput* dartsPointModel(const QUuid& tournamentId,
                                                   const QUuid& playerId,
                                                   const int& roundIndex,
                                                   const int& attemptIndex) const = 0;
        virtual PlayerInputs dartsPointModelsByTournamentId(const QUuid& tournamentId) const = 0;
        virtual const IDartsPointIndexes* dartsPointIndexes(const QUuid &tournamentId) const = 0;
        virtual void addDartsPoint(const PlayerInput*) = 0;
        virtual PlayerInputs getDartsPointModelsOrdedByIndexes(const QUuid& tournamentId) const = 0;
        virtual const PlayerInput* getDartsPointModelById(const QUuid& id) const = 0;
        virtual int dartsPointsCount(const QUuid&,const int&) const = 0;
        virtual void setDartsPointHint(const PlayerInput* inputModel,const int& hint) = 0;
        virtual void removePointById(const QUuid&) = 0;
        virtual void removeHiddenPoints(const QUuid&) = 0;
        virtual void removePointsByTournamentId(const QUuid&) = 0;
    };
}


#endif // TOURNAMENTMODELINTERFACE_H

