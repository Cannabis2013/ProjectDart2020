#ifndef CREATEINDEXESFROMDARTSSCORES_H
#define CREATEINDEXESFROMDARTSSCORES_H

#include "idartsscoreinput.h"
#include <quuid.h>
#include "dartsscoreindexes.h"
#include "idartscreateindexes.h"
#include "idartstournament.h"
#include "sortdartsscoreinputsbyindexes.h"

namespace ModelsContext {
    class CreateDartsScoreIndexes : public IDartsCreateIndexes<IDartsScoreIndexes>
    {
    public:
        enum ModelDisplayHint{
            HiddenHint = 0x1,
            DisplayHint = 0x2,
            allHints = HiddenHint | DisplayHint
        };
        virtual const IDartsScoreIndexes *createIndexes(const IModel<QUuid> *tournament,
                                                        const IGetInputModelsService *getInputsService,
                                                        const ISortInputModels *sortInputsService,
                                                        const ICountInputModels *countInputsService,
                                                        const IDbService *dbService) const override;

    private:
        const IDartsScoreIndexes *createDartsIndexesByModels(const IModel<QUuid> *tournament,
                                                             const QVector<const IModel<QUuid> *> &orderedModels,
                                                             const int&  totalModelsCount) const;;
        const IDartsScoreIndexes* createInitialDartsIndexes() const;
    };

}

#endif // ASSEMBLEDARTSSCOREINDEXESBYMODEL_H
