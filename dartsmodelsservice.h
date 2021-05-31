#ifndef TOURNAMENTMODELCONTEXT_H
#define TOURNAMENTMODELCONTEXT_H

#include <qjsonobject.h>
#include <qjsonarray.h>
#include <qfile.h>

#include "iplayermodelsdb.h"
#include "idartsmodelsservice.h"
#include "abstractjsonpersistence.h"
#include "idartspointinput.h"
#include "idartsscoreinput.h"
#include "idartstournamentdb.h"
#include "idartspointdb.h"
#include "iunaryservice.h"
#include "ibinaryservice.h"
#include "iternaryservice.h"
#include "idartspointindexes.h"
#include "idartsscoredb.h"
#include "idartsscoreindexes.h"
#include "ipredicate.h"
#include "abstractdartsfilterpredicate.h"
#include "idartsinputsfilter.h"


#define THROW_OBJECT_WITH_ID_NOT_FOUND(x) QString("Model with ID: '%1' does not exists in the current context").arg(x).toStdString();
#define THROW_OBJECT_WITH_INDEX_NOT_FOUND(x) QString("Model with index: '%1' does not exists in the current context").arg(x).toStdString();

/*
 * Context responsibilities
 *  - Get and modify data values from data storage class containers
 *  - Build and persist data storage class containers by the help of appropriate services
 */

namespace DartsModelsContext{
    class DartsModelsService :
            public IDartsModelsService
    {
    public:
        /*
         * Public types
         */
        enum GameModes {
            FirstToPost = 0x1,
            RoundLimit =0x2,
            Circular = 0x3,
            Cricket = 0x4
        };
        enum ModelsContextResponse{
            TournamentCreatedOK = 0x32,
            TournamentDeletedOK = 0x35,
            EndOfTransmission = 0x10,
            TournamentDetailsFailed
        };
        enum ModelDisplayHint{
            HiddenHint = 0x1,
            DisplayHint = 0x2,
            AllHints = 0x3
        };
        typedef IBinaryService<const QVector<int>&,IDartsTournamentDb*,bool> DeleteTournamentByIndexes;
        typedef IBinaryService<const int&,const IDartsTournamentDb*,const IDartsTournament*> GetTournamentByIndexService;
        typedef IBinaryService<const QUuid&,const IDartsTournamentDb*,const IDartsTournament*> GetDartsTournamentByIdService;
        typedef IBinaryService<const IDartsTournament*,const QVector<QUuid>&,const IDartsTournament*> AssignPlayerIdsToTournament;

        /*
         * Create and setup instance
         */
        static DartsModelsService *createInstance();
        /*
         * Darts tournament related section
         */
        const IDartsTournament *dartsTournamentModelById(const QUuid &tournamentId) const override;
        const IDartsTournament *dartsTournamentByIndex(const int &index) const override;
        QVector<const IDartsTournament *> dartsTournamentModels() const override;
        bool removeTournamentsByIndexes(const QVector<int>& indexes) const override;
        void tournamentSetWinnerId(const QUuid &tournamentId,
                                   const QUuid &winnerId) override;
        const IDartsTournament *assignPlayerIdsToDartsTournament(const IDartsTournament* tournament,
                                                                 const QVector<QUuid>& playerIds) const override;
        QUuid addDartsTournamentToDb(const IDartsTournament *tournament) override;
        // Set services method
        DartsModelsService *setTournamentsDbContext(
                IDartsTournamentDb *tournamentsDbContext);
        DartsModelsService* setGetTournamentByIndexService(GetTournamentByIndexService *service);
        DartsModelsService* setGetDartsTournamentByIdService(GetDartsTournamentByIdService *service);
        DartsModelsService* setDeleteTournamentsByIndexes(DeleteTournamentByIndexes *service);
        // set db service methods
        DartsModelsService* setDartsPointsDb(IDartsPointDb *dartsPointsDb);
        DartsModelsService* setDartsScoreDb(IDartsScoreDb *dartsScoreDb);
        DartsModelsService* setDartsScoresDb(IDartsScoreDb *dartsScoresDb);
        DartsModelsService* setAssignPlayerIdsToDartsTournament(AssignPlayerIdsToTournament *newAssignPlayerIdsToDartsTournament);

    private:
        /*
         * Services
         */
        // General services
        AssignPlayerIdsToTournament* _assignPlayerIdsToDartsTournament;
        // Tournament services
        GetTournamentByIndexService* _getDartsTournamentByIndexService;
        GetDartsTournamentByIdService* _getDartsTournamentByIdService;
        DeleteTournamentByIndexes* _deleteTournamentsByIndexes;
        // Db services
        IDartsTournamentDb* _tournamentsDbContext;
        IDartsPointDb* _dartsPointsDb;
        IDartsScoreDb* _dartsScoresDb;
    };
}

#endif // TOURNAMENTMODELCONTEXT_H
