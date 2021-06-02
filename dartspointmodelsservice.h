#ifndef DARTSPOINTMODELSSERVICE_H
#define DARTSPOINTMODELSSERVICE_H

#include "idartspointmodelsservice.h"
#include <qvector.h>
#include "idartspointdb.h"
#include "idartsinputsfilter.h"
#include "ipredicate.h"
#include "ibinaryservice.h"
#include "iternaryservice.h"
#include "idartssingleattemptindexesbuilder.h"

namespace DartsModelsContext {
    class DartsPointModelsService : public IDartsPointModelsService
    {
    public:
        /*
         * Public types
         */
        enum ModelDisplayHint{
            HiddenHint = 0x1,
            DisplayHint = 0x2,
            AllHints = 0x3
        };
        // Typedefs
        typedef IDartsInputsFilter<PlayerInput,QUuid> FilterDartsInputsService;
        typedef IBinaryService<const PlayerInputs&,
                               const IPredicate*,
                               PlayerInputs> SortDartsInputsByPredicateService;
        typedef IDartsSingleAttemptIndexesBuilder<IDartsPointIndexes,IDartsInput> IndexesBuilderService;
        typedef IModelsDbContext<PlayerInput,QUuid> ModelsDbService;
        typedef IBinaryService<const QUuid&,const ModelsDbService*, const PlayerInput*> GetDartsInputModelByIdService;
        typedef IBinaryService<const PlayerInput*,const int&, const PlayerInput*> DartsInputHintService;
        typedef IBinaryService<const PlayerInputs&,ModelsDbService*,void> RemoveModelsService;

        // Create instance
        static DartsPointModelsService* createInstance();
        // Methods

        const PlayerInput *dartsPointModel(const QUuid &tournamentId, const QUuid &playerId, const int &roundIndex, const int &attemptIndex) const override;
        PlayerInputs dartsPointModelsByTournamentId(const QUuid &tournamentId) const override;
        const IDartsPointIndexes *dartsPointIndexes(const QVector<const IDartsInput*>& models,
                                                    const int& assignedPlayersCount) const override;
        void addDartsPoint(const PlayerInput *model) override;
        PlayerInputs getDartsPointModelsOrdedByIndexes(const QUuid &tournamentId) const override;
        const PlayerInput *getDartsPointModelById(const QUuid &id) const override;
        int dartsPointsCount(const QUuid &tournamentId, const int &hint) const override;
        void setDartsPointHint(const PlayerInput *inputModel, const int &hint) override;
        void removePointById(const QUuid &pointModelId) override;
        void removeHiddenPoints(const QUuid &tournamentId) override;
        void removePointsByTournamentId(const QUuid &tournamentId) override;
        QVector<const IDartsInput *> sortDartsPointsByIndexes(const QVector<const IDartsInput *> &models) const override;

        DartsPointModelsService* setDartsInputsFilterService(FilterDartsInputsService *newDartsInputsFilterService);
        DartsPointModelsService* setSortDartsInputModelsByPredicate(SortDartsInputsByPredicateService *newSortDartsInputModelsByPredicate);
        DartsPointModelsService* setAssembleDartsPointIndexes(IndexesBuilderService *newAssembleDartsPointIndexes);
        DartsPointModelsService* setDartsSortingPredicate(IPredicate *newDartsPointLessThanPredicate);
        DartsPointModelsService* setDartsInputHintService(DartsInputHintService *newSetInputHintService);
        DartsPointModelsService* setRemoveModelsService(RemoveModelsService *newRemoveModelsService);
        DartsPointModelsService* setGetInputModelByIdService(GetDartsInputModelByIdService *newGetInputModelByIdService);
        DartsPointModelsService* setDbService(IDartsPointDb *newDartsPointsDb);

    private:
        RemoveModelsService* _removeModelsService;
        DartsInputHintService* _setInputHintService;
        GetDartsInputModelByIdService* _getInputModelByIdService;
        IndexesBuilderService* _assembleDartsPointIndexes;
        SortDartsInputsByPredicateService* _sortDartsInputModelsByPredicate;
        IPredicate* _dartsPointLessThanPredicate;
        FilterDartsInputsService* _dartsInputsFilterService;
        IDartsPointDb* _dartsPointsDb;
    };
}

#endif // DARTSPOINTMODELSSERVICE_H
