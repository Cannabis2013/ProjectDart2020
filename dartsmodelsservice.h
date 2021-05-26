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
#include "predicate.h"
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
        typedef IBinaryService<PlayerInputs&,
                              const Predicate*,
                              PlayerInputs> SortDartsInputsByPredicateService;
        typedef ITernaryService<const QVector<const PlayerInput *> &,
                                const IDartsTournament *,
                                const int &,
                                const IDartsPointIndexes *> GetPointIndexesFromDartsTournamentService;
        typedef ITernaryService<const QVector<const PlayerInput*>&,
                                const IDartsTournament*,
                                const int&,
                                const IDartsScoreIndexes*> GetScoreIndexesByDartsTournamentService;
        typedef IBinaryService<const PlayerInput*,const int&,const PlayerInput*> SetDartsModelHint;
        typedef IBinaryService<const PlayerInput*,const int&, const PlayerInput*> setInputHintService;
        typedef IModelsDbContext<PlayerInput,QUuid> ModelsDbService;
        typedef IBinaryService<const QUuid&,const ModelsDbService*,QVector<const IDartsInput*>> GetDartsInputsByIdService;
        typedef IBinaryService<const QVector<int>&,IDartsTournamentDb*,bool> DeleteTournamentByIndexes;
        typedef IBinaryService<const int&,const IDartsTournamentDb*,const IDartsTournament*> GetTournamentByIndexService;
        typedef IBinaryService<const QUuid&,const IDartsTournamentDb*,const IDartsTournament*> GetDartsTournamentByIdService;
        typedef IBinaryService<const QUuid&,const ModelsDbService*, const PlayerInput*> GetDartsInputModelByIdService;
        typedef QVector<const PlayerInput*> PointModels;
        typedef QVector<const PlayerInput*> DartsPlayerInputs;
        typedef IBinaryService<const DartsPlayerInputs&,ModelsDbService*,void> RemoveModelsService;
        typedef IDartsInputsFilter<PlayerInput,QUuid> FilterDartsInputsService;
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
        const IDartsPointIndexes *dartsPointIndexes(const QUuid &tournamentId) const override;
        /*
         * Points related section
         */
        QVector<const PlayerInput *> dartsPointModelsByTournamentId(const QUuid &tournamentId) const override;
        const PlayerInput* getDartsPointModelById(const QUuid& pointId) const override;
        void addDartsPoint(const PlayerInput *model) override;
        QVector<const PlayerInput*> getDartsPointModelsOrdedByIndexes(const QUuid& tournamentId) const override;
        int dartsPointsCount(const QUuid& tournamentId,const int &hint) const override;
        const PlayerInput *setDartsPointHint(const QUuid &tournamentId,
                                                  const QUuid &playerId ,
                                                  const int &roundIndex,
                                                  const int &attempt,
                                                  const int &hint) override;
        void removePointById(const QUuid &pointId) override;
        void removeHiddenPoints(const QUuid &tournamentId) override;
        void removePointsByTournamentId(const QUuid &tournamentId) override;
        /*
         * Scores methods
         */
        const PlayerInput *dartsScoreModel(const QUuid &tournamentId, const QUuid &playerId, const int &roundIndex) const override;
        QVector<const PlayerInput *> dartsScoreModelsByTournamentIdAndHint(const QUuid &tournamentId, const int &hint) const override;
        void addDartsScore(const IDartsScoreInput *pointModel) override;
        int dartsScoresCount(const int &hint) const override;
        const PlayerInput *setDartsScoreHint(const PlayerInput* model,
                                                  const int &hint) override;
        void removeScoreById(const QUuid &scoreId) override;
        void removeHiddenScores(const QUuid &tournamentId) override;
        void removeScoresByTournamentId(const QUuid &tournamentId) override;
        void removeScoreModel(const QUuid &scoreId) override;
        const IDartsScoreIndexes *dartsScoreIndexes(const QUuid &tournamentId) const override;
        int dartsScoreCount(const QUuid &tournamentId, const int &hint) const override;
        // Set services method
        DartsModelsService *setTournamentsDbContext(
                IDartsTournamentDb *tournamentsDbContext);
        DartsModelsService* setAssembleDartsPointIndexes(GetPointIndexesFromDartsTournamentService *getDartsPointIndexes);
        DartsModelsService* setGetOrderedDartsScoreModels(SortDartsInputsByPredicateService *getOrderedDartsScoreModels);
        DartsModelsService* setGetScoreIndexesByTournamentId(GetScoreIndexesByDartsTournamentService *getScoreIndexesByTournamentId);
        DartsModelsService* setGetTournamentByIndexService(GetTournamentByIndexService *newGetTournamentByIndexService);
        DartsModelsService* setGetDartsTournamentByIdService(GetDartsTournamentByIdService *getDartsTournamentByService);
        DartsModelsService* setDartsPointModelHintService(setInputHintService *dartsPointModelHintService);
        DartsModelsService* setGetDartsInputModelByIdService(GetDartsInputModelByIdService *getDartsPointByIdService);
        DartsModelsService* setDeleteTournamentsByIndexes(DeleteTournamentByIndexes *deleteTournamentsByIndexes);
        // set db service methods
        DartsModelsService* setDartsPointsDb(IDartsPointDb *dartsPointsDb);
        DartsModelsService* setDartsScoreDb(IDartsScoreDb *dartsScoreDb);
        DartsModelsService* setDartsScoresDb(IDartsScoreDb *dartsScoresDb);
        DartsModelsService* setRemoveModelsService(RemoveModelsService *newRemoveModelsService);
        DartsModelsService* setDartsPointLessThanPredicate(Predicate *predicate);
        DartsModelsService* setDartsScoreLessThanPredicate(Predicate *predicate);
        DartsModelsService* setDartsInputsFilterService(FilterDartsInputsService *newFilterDartsInputsService);
        DartsModelsService* setAssignPlayerIdsToDartsTournament(AssignPlayerIdsToTournament *newAssignPlayerIdsToDartsTournament);

    private:
        /*
         * Services
         */
        // General services
        RemoveModelsService* _removeModelsService;
        setInputHintService* _setInputHintService;
        SortDartsInputsByPredicateService* _sortDartsInputModelsByPredicate;
        FilterDartsInputsService* _dartsInputsFilterService;
        GetDartsInputModelByIdService* _getInputModelByIdService;
        AssignPlayerIdsToTournament* _assignPlayerIdsToDartsTournament;
        // Point services
        GetPointIndexesFromDartsTournamentService* _assembleDartsPointIndexes;
        Predicate* _dartsPointLessThanPredicate;
        // Score services
        GetScoreIndexesByDartsTournamentService* _getDartsScoreIndexesByModels;
        Predicate* _dartsScoreLessThanPredicate;
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
