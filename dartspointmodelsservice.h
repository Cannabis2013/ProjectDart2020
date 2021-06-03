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
    class DartsPointModelsService : public IDartsPointModelsService<IDartsPointDb>
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
        typedef IDartsInputsFilter<IPlayerInput,QUuid> FilterDartsInputsService;
        typedef IPredicate<IPlayerInput> Predicate;
        typedef IBinaryService<const PlayerInputs&,
                               const Predicate*,
                               PlayerInputs> SortDartsInputsByPredicateService;
        typedef IDartsSingleAttemptIndexesBuilder<IDartsPointIndexes,PlayerInput> IndexesBuilderService;
        typedef IModelsDbContext<PlayerInput> ModelsDbService;
        typedef IBinaryService<const QUuid&,const ModelsDbService*, const PlayerInput*> GetDartsInputModelByIdService;
        typedef IBinaryService<const PlayerInput*,const int&, const PlayerInput*> DartsInputHintService;
        typedef IBinaryService<const PlayerInputs&,ModelsDbService*,void> RemoveModelsService;

        // Create instance
        static DartsPointModelsService* createInstance();
        // Methods

        const PlayerInput *dartsPointModel(const QUuid &tournamentId,
                                           const QUuid &playerId,
                                           const int &roundIndex,
                                           const int &attemptIndex,
                                           const IDartsPointDb* dbService) const override;
        const IDartsPointIndexes *dartsPointIndexes(const QVector<const PlayerInput*>& models,
                                                    const int& totalInputModelsCount,
                                                    const int& assignedPlayersCount) const override;
        int dartsPointsCount(const QUuid &tournamentId, const int &hint, const IDartsPointDb* dbService) const override;
        void setDartsPointHint(const PlayerInput *inputModel, const int &hint, IDartsPointDb *dbService) override;
        QVector<const PlayerInput *> sortDartsPointsByIndexes(const QVector<const PlayerInput *> &models) const override;
        // Set service methods
        DartsPointModelsService* setDartsInputsFilterService(FilterDartsInputsService *newDartsInputsFilterService);
        DartsPointModelsService* setSortDartsInputModelsByPredicate(SortDartsInputsByPredicateService *newSortDartsInputModelsByPredicate);
        DartsPointModelsService* setAssembleDartsPointIndexes(IndexesBuilderService *newAssembleDartsPointIndexes);
        DartsPointModelsService* setDartsSortingPredicate(Predicate *newDartsPointLessThanPredicate);
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
        Predicate* _dartsPointLessThanPredicate;
        FilterDartsInputsService* _dartsInputsFilterService;
    };
}

#endif // DARTSPOINTMODELSSERVICE_H
