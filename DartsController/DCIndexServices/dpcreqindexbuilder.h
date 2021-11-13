#ifndef DPCREQINDEXBUILDER_H
#define DPCREQINDEXBUILDER_H
#include "DartsController/DCIndexSLAs/idcreqinputindexbuilder.h"
class DPCReqIndexBuilder : public IDCReqInputIndexBuilder
{
public:
    virtual IDartsIndex *index(IDartsIndex *index, const IDCIndexBuilder *indexBuilder) const override
    {
        auto attemptIndex = index->attemptIndex();
        auto roundIndex = index->roundIndex();
        if(attemptIndex > 0)
            attemptIndex--;
        else
            roundIndex--;
        auto reqIndex = indexBuilder->index(index);
        reqIndex->setAttemptIndex(attemptIndex);
        reqIndex->setRoundIndex(roundIndex);
        return reqIndex;
    }
};
#endif // DPCREQINDEXBUILDER_H
