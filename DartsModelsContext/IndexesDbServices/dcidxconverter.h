#ifndef DCIDXCONVERTER_H
#define DCIDXCONVERTER_H
#include "ModelsContext/ModelsSLAs/imodel.h"
#include <DartsModelsContext/IndexesSLAs/idcidxconverter.h>
#include "DartsModelsContext/IndexesDbServices/dartsindex.h"
class DCIdxConverter : public IDCIdxConverter
{
public:
    virtual IDartsIndex *convert(const DCIndex &idx) const override
    {
        auto mdlIdx = new DartsIndex;
        mdlIdx->setTotalTurns(idx.totalTurns);
        mdlIdx->setTurnIndex(idx.turnIndex);
        mdlIdx->setRoundIndex(idx.roundIndex);
        mdlIdx->setSetIndex(idx.setIndex);
        mdlIdx->setAttemptIndex(idx.attemptIndex);
        return mdlIdx;
    }
    virtual DCIndex convert(IDartsIndex *mdlIdx) const override
    {
        DCIndex idx;
        idx.totalTurns = mdlIdx->totalTurns();
        idx.turnIndex = mdlIdx->turnIndex();
        idx.roundIndex = mdlIdx->roundIndex();
        idx.setIndex = mdlIdx->setIndex();
        idx.attemptIndex = mdlIdx->attemptIndex();
        return idx;
    }
};
#endif // DARTSINDEXESBUILDER_H
