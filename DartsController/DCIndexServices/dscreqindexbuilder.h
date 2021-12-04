#ifndef DSCREQINDEXBUILDER_H
#define DSCREQINDEXBUILDER_H
#include <DartsController/DCIndexSLAs/abstractdcreqidxbuilder.h>
#include "DartsModelsContext/IndexesDbServices/dartsindex.h"
class DSCReqIndexBuilder : public AbstractDCReqIdxBuilder
{
public:
    DSCReqIndexBuilder(AbsDCIdxCtrl *indexCtrl)
    {
        setIndexCtrl(indexCtrl);
    }
    virtual DCIndex prevIdx() const override
    {
        auto reqIdx = indexCtrl()->index();
        reqIdx.roundIndex--;
        return reqIdx;
    }
};
#endif // DSCREQINDEXBUILDER_H
