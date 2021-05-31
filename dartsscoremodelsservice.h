#ifndef DARTSSCOREMODELSSERVICE_H
#define DARTSSCOREMODELSSERVICE_H

#include "idartsscoremodelsservice.h"
#include "idartsscoredb.h"
#include <qvector.h>
#include "idartsinputsfilter.h"
#include "ibinaryservice.h"
#include "ipredicate.h"
#include "iternaryservice.h"
#include "idartsmultiattemptindexesbuilder.h"

namespace DartsModelsContext {
    class DartsScoreModelsService : public IDartsScoreModelsService
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
        typedef IModelsDbContext<PlayerInput,QUuid> ModelsDbService;
        typedef IBinaryService<const DartsPlayerInputs&,ModelsDbService*,void> RemoveModelsService;
        typedef IBinaryService<const QUuid&,const ModelsDbService*, const PlayerInput*> GetDartsInputModelByIdService;
        typedef IBinaryService<const PlayerInput*,const int&, const PlayerInput*> setInputHintService;
        typedef IBinaryService<PlayerInputs&,
                              const IPredicate*,
                              PlayerInputs> SortDartsInputsByPredicateService;
        typedef IDartsMultiAttemptIndexesBuilder<IDartsScoreIndexes,PlayerInput> GetScoreIndexesByModels;
        // Create instance
        static DartsScoreModelsService* createInstance();
        // Methods
        const PlayerInput *dartsScoreModel(const QUuid &tournamentId, const QUuid &playerId, const int &roundIndex) const override;
        QVector<const PlayerInput *> dartsScoreModelsByTournamentIdAndHint(const QUuid &tournamentId, const int &hint) const override;
        void addDartsScore(const IDartsScoreInput *scoreModel) override;
        void removeHiddenScores(const QUuid &tournamentId) override;
        void removeScoreById(const QUuid &scoreId) override;
        void removeScoresByTournamentId(const QUuid &tournamentId) override;
        void removeScoreModel(const QUuid &scoreId) override;
        void setDartsScoreHint(const PlayerInput *model, const int &hint) override;
        const IDartsScoreIndexes *dartsScoreIndexes(const QUuid &tournamentId,
                                                    const int& assignedPlayersCount) const override;
        int dartsScoreCount(const QUuid &tournamentId, const int &hint) const override;
        DartsScoreModelsService* setDartsInputsFilterService(FilterDartsInputsService *newDartsInputsFilterService);
        DartsScoreModelsService* setRemoveModelsService(RemoveModelsService *newRemoveModelsService);
        DartsScoreModelsService* setGetInputModelByIdService(GetDartsInputModelByIdService *newGetInputModelByIdService);
        DartsScoreModelsService* setSetInputHintService(setInputHintService *newSetInputHintService);
        DartsScoreModelsService* setSortDartsInputModelsByPredicate(SortDartsInputsByPredicateService *newSortDartsInputModelsByPredicate);
        DartsScoreModelsService* setGetDartsScoreIndexesByModels(GetScoreIndexesByModels *newGetDartsScoreIndexesByModels);
        DartsScoreModelsService* setDartsScoreLessThanPredicate(IPredicate *newDartsPointLessThanPredicate);
        DartsScoreModelsService* setDbService(IDartsScoreDb *service);

    private:
        IPredicate* _dartsScoreLessThanPredicate;
        SortDartsInputsByPredicateService* _sortDartsInputModelsByPredicate;
        GetScoreIndexesByModels* _getDartsScoreIndexesByModels;
        setInputHintService* _setInputHintService;
        GetDartsInputModelByIdService* _getInputModelByIdService;
        RemoveModelsService* _removeModelsService;
        FilterDartsInputsService* _dartsInputsFilterService;
        IDartsScoreDb* _dartsScoresDb;
    };
}


#endif // DARTSSCOREMODELSSERVICE_H
