#ifndef DPCREQINDEXBUILDER_H
#define DPCREQINDEXBUILDER_H

#include "DartsController/DCIndexSLAs/idcreqinputindexbuilder.h"

class DPCReqIndexBuilder : public IDCReqInputIndexBuilder
{
public:
    virtual DCIndex indexes(const IDCIndexController *indexService) const override
    {
        auto attemptIndex = indexService->attemptIndex();
        auto setIndex = indexService->setIndex();
        auto roundIndex = indexService->roundIndex();
        if(attemptIndex > 0)
            return createIndex(roundIndex,setIndex,--attemptIndex);
        return createIndex(--roundIndex,setIndex,attemptIndex);
    }
private:
    DCIndex createIndex(const int &roundIndex, const int &setIndex, const int &attemptIndex) const
    {
        DCIndex index;
        index.roundIndex = roundIndex;
        index.setIndex = setIndex;
        index.attemptIndex = attemptIndex;
        return index;
    }
};

#endif // DPCREQINDEXBUILDER_H
