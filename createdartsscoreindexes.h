#ifndef CREATEINDEXESFROMDARTSSCORES_H
#define CREATEINDEXESFROMDARTSSCORES_H

#include "idartsscoreinput.h"
#include <quuid.h>
#include "dartsscoreindexes.h"
#include "icreatedartsindexes.h"
#include "idartstournament.h"
#include "sortdartsscoreinputsbyindexes.h"

namespace DartsModelsContext {
    class CreateDartsScoreIndexes : public ICreateDartsIndexes<IDartsScoreIndexes>
    {
    public:
        enum ModelDisplayHint{
            HiddenHint = 0x1,
            DisplayHint = 0x2,
            allHints = HiddenHint | DisplayHint
        };
        virtual const IDartsScoreIndexes *createIndexes(const ITournament *tournament,
                                                        const IGetInputModelsService *getInputsService,
                                                        const ISortInputModels *sortInputsService,
                                                        const ICountInputModels *countInputsService,
                                                        const IDartsInputDb *dbService) const override;

    private:
        const IDartsScoreIndexes *createDartsIndexesByModels(const ITournament* tournament,
                                                             const QVector<const IPlayerInput*>& orderedModels,
                                                             const int&  totalModelsCount) const;;
        const IDartsScoreIndexes* createInitialDartsIndexes() const;
    };

}

#endif // ASSEMBLEDARTSSCOREINDEXESBYMODEL_H
