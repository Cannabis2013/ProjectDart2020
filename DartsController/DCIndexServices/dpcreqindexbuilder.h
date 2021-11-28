#ifndef DPCREQINDEXBUILDER_H
#define DPCREQINDEXBUILDER_H
#include "DartsController/DCIndexSLAs/abstractdcreqidxbuilder.h"
class DPCReqIndexBuilder : public AbstractDCReqIdxBuilder
{
public:
    DPCReqIndexBuilder(AbstractDCIdxCtrl *indexCtrl)
    {
        setIndexCtrl(indexCtrl);
    }
    virtual DCIndex prevIdx() const override
    {
        auto reqIdx = indexCtrl()->index();
        if(reqIdx.attemptIndex > 0)
            reqIdx.attemptIndex--;
        else
            reqIdx.roundIndex--;
        return reqIdx;
    }
};
#endif // DPCREQINDEXBUILDER_H
