#ifndef DARTSSCOREMODELSSERVICE_H
#define DARTSSCOREMODELSSERVICE_H

#include "idartsscoremodelsservice.h"
#include "idartsinputdb.h"
#include <qvector.h>
#include "idartsinputsfilter.h"
#include "ibinaryservice.h"
#include "ipredicate.h"
#include "iternaryservice.h"
#include "idartsmultiattemptindexesbuilder.h"
#include "idartsinputdb.h"

namespace DartsModelsContext {
    class DartsScoreModelsService : public IDartsScoreModelsService<IDartsInputDb>
    {
    public:
        /*
         * Public types
         *  - Enums
         *  - Typedefs
         */
        enum ModelDisplayHint{
            HiddenHint = 0x1,
            DisplayHint = 0x2,
            AllHints = 0x3
        };
        typedef IDartsInputsFilter<PlayerInput,QUuid> FilterDartsInputsService;
        typedef QVector<const PlayerInput*> DartsPlayerInputs;
        typedef IBinaryService<const PlayerInput*,const int&, const PlayerInput*> setInputHintService;
        typedef IPredicate<IPlayerInput> Predicate;
        typedef IBinaryService<const PlayerInputs&,
                              const Predicate*,
                              PlayerInputs> SortDartsInputsByPredicateService;
        typedef IDartsMultiAttemptIndexesBuilder<IDartsScoreIndexes,PlayerInput> GetScoreIndexesByModels;
        // Create instance
        static DartsScoreModelsService* createInstance();
        // Methods
        virtual const PlayerInput *dartsScoreModel(const QUuid &tournamentId, const QUuid &playerId, const int &roundIndex, const DbModelsService *dbService) const override;
        void setDartsScoreHint(const PlayerInput *model, const int &hint, DbModelsService* dbService) override;
        const IDartsScoreIndexes *dartsScoreIndexes(const QUuid &tournamentId,
                                                    const int& assignedPlayersCount,
                                                    const DbModelsService* dbService) const override;
        DartsScoreModelsService* setDartsInputsFilterService(FilterDartsInputsService *newDartsInputsFilterService);
        DartsScoreModelsService* setSetInputHintService(setInputHintService *newSetInputHintService);
        DartsScoreModelsService* setSortDartsInputModelsByPredicate(SortDartsInputsByPredicateService *newSortDartsInputModelsByPredicate);
        DartsScoreModelsService* setGetDartsScoreIndexesByModels(GetScoreIndexesByModels *newGetDartsScoreIndexesByModels);
        DartsScoreModelsService* setDartsScoreLessThanPredicate(Predicate *newDartsPointLessThanPredicate);

    private:
        Predicate* _dartsScoreLessThanPredicate;
        SortDartsInputsByPredicateService* _sortDartsInputModelsByPredicate;
        GetScoreIndexesByModels* _getDartsScoreIndexesByModels;
        setInputHintService* _setInputHintService;
        FilterDartsInputsService* _dartsInputsFilterService;

    };
}


#endif // DARTSSCOREMODELSSERVICE_H
