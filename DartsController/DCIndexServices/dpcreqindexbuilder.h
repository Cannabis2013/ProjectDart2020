#ifndef DPCREQINDEXBUILDER_H
#define DPCREQINDEXBUILDER_H

#include "DartsController/DCIndexSLAs/idcreqinputindexbuilder.h"

class DPCReqIndexBuilder : public IDCReqInputIndexBuilder
{
public:
    virtual DCIndex indexes(const DCIndex &index) const override
    {
        auto reqIndex = index;
        if(reqIndex.attemptIndex > 0)
            reqIndex.attemptIndex--;
        else
            reqIndex.roundIndex--;
        return reqIndex;
    }
};

#endif // DPCREQINDEXBUILDER_H
