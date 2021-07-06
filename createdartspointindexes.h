#ifndef CREATEDARTSPOINTINDEXES_H
#define CREATEDARTSPOINTINDEXES_H

#include "icreatedartsindexes.h"
#include "dartspointindexes.h"
#include "idartstournament.h"
#include "sortdartspointinputsbyindexes.h"

namespace DartsModelsContext {
    class CreateDartsPointIndexes : public ICreateDartsIndexes<IDartsPointIndexes>
    {
    public:
        enum ModelDisplayHint{
            HiddenHint = 0x1,
            DisplayHint = 0x2,
            allHints = HiddenHint | DisplayHint
        };
        virtual const IDartsPointIndexes *createIndexes(const ITournament *tournament,
                                                        const IGetInputModelsService *getInputsService,
                                                        const ISortInputModels *sortInputsService,
                                                        const ICountInputModels *countInputsService,
                                                        const IDartsInputDb *dbService) const override;
    private:
        const IDartsPointIndexes* createDartsIndexesByModels(const ITournament *tournament, const QVector<const IPlayerInput*>& orderedModels, const int &totalInputModelsCount) const;;
        const IDartsPointIndexes* createInitialDartsIndexes() const;
    };
}

#endif // GETLASTENTEREDDARTSPOINTMODEL_H
