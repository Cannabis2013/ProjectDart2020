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
        virtual const IDartsTournament* assignPlayerIdsToDartsTournament(const IDartsTournament*,const QVector<QUuid>&) const = 0;
    };
}


#endif // TOURNAMENTMODELINTERFACE_H

