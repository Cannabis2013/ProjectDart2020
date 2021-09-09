#ifndef DARTSCREATEINDEXES_H
#define DARTSCREATEINDEXES_H

#include "idartscreateindexes.h"
#include "dartspointindexes.h"
#include "abstractdartstournament.h"
#include "sortdartspointinputsbyindexes.h"

class DartsCreateIndexes : public IDartsCreateIndexes<IDartsPointIndexes>
{
public:
    enum ModelDisplayHint{
        HiddenHint = 0x1,
        DisplayHint = 0x2,
        allHints = HiddenHint | DisplayHint
    };
    virtual const IDartsPointIndexes *createIndexes(const IModel<QUuid> *tournament,
                                                    const IGetInputModelsService *getInputsService,
                                                    const ISortInputModels *sortInputsService,
                                                    const ICountInputModels *countInputsService,
                                                    const IModelsDbContext *dbService) const override;
private:
    const IDartsPointIndexes* createDartsIndexesByModels(const IModel<QUuid> *tournament, const QVector<const IModel<QUuid> *> &orderedModels, const int &totalInputModelsCount) const;;
    const IDartsPointIndexes* createInitialDartsIndexes() const;
};

#endif // GETLASTENTEREDDARTSPOINTMODEL_H
