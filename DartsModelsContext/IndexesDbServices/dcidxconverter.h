#ifndef DCIDXCONVERTER_H
#define DCIDXCONVERTER_H
#include <DartsModelsContext/IndexesSLAs/idcidxbuilder.h>
#include <DartsController/DCIndexSLAs/dcindex.h>
#include "DartsModelsContext//TournamentModels/tnmvalues.h"
#include "DartsModelsContext/IndexesDbServices/dartsindex.h"
class DCIdxConverter : public IDCIdxBuilder
{
public:
    virtual TnmVals convert(const DCIndex &idx) const override
    {
        TnmVals cvtdIdx;
        cvtdIdx.totalTurns = idx.totalTurns;
        cvtdIdx.turnIndex = idx.turnIndex;
        cvtdIdx.roundIndex = idx.roundIndex;
        cvtdIdx.setIndex = idx.setIndex;
        cvtdIdx.attemptIndex = idx.attemptIndex;
        return cvtdIdx;
    }
};
#endif // DARTSINDEXESBUILDER_H
