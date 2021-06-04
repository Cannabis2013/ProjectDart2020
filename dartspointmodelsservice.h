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
        typedef IDartsSingleAttemptIndexesBuilder<IDartsPointIndexes,PlayerInput> IndexesBuilderService;
        typedef IModelsDbContext<PlayerInput> ModelsDbService;
        typedef IBinaryService<const PlayerInput*,const int&, const PlayerInput*> DartsInputHintService;

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
        void setDartsPointHint(const PlayerInput *inputModel, const int &hint, IDartsPointDb *dbService) override;
        // Set service methods
        DartsPointModelsService* setDartsInputsFilterService(FilterDartsInputsService *newDartsInputsFilterService);
        DartsPointModelsService* setAssembleDartsPointIndexes(IndexesBuilderService *newAssembleDartsPointIndexes);
        DartsPointModelsService* setDartsInputHintService(DartsInputHintService *newSetInputHintService);
        DartsPointModelsService* setDbService(IDartsPointDb *newDartsPointsDb);

    private:
        DartsInputHintService* _setInputHintService;
        IndexesBuilderService* _assembleDartsPointIndexes;
        FilterDartsInputsService* _dartsInputsFilterService;
    };
}

#endif // DARTSPOINTMODELSSERVICE_H
