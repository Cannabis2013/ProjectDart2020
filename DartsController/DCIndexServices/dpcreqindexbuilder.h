#ifndef DPCREQINDEXBUILDER_H
#define DPCREQINDEXBUILDER_H
#include "DartsController/DCIndexSLAs/abstractdcreqindexbuilder.h"
class DPCReqIndexBuilder : public AbstractDCReqIndexBuilder
{
public:
    DPCReqIndexBuilder(AbstractDCIdxCtrl *indexCtrl, IDCIdxBuilder *indexBuilder)
    {
        setIndexCtrl(indexCtrl);
        setIndexBuilder(indexBuilder);
    }
    virtual IDartsIndex *prevIndex() const override
    {
        auto index = indexCtrl()->index();
        auto attemptIndex = index->attemptIndex();
        auto roundIndex = index->roundIndex();
        if(attemptIndex > 0)
            attemptIndex--;
        else
            roundIndex--;
        auto reqIndex = indexBuilder()->index(index);
        reqIndex->setAttemptIndex(attemptIndex);
        reqIndex->setRoundIndex(roundIndex);
        return reqIndex;
    }
};
#endif // DPCREQINDEXBUILDER_H
