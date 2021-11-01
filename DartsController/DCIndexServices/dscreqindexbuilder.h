#ifndef DSCREQINDEXBUILDER_H
#define DSCREQINDEXBUILDER_H
#include <DartsController/DCIndexSLAs/idcreqinputindexbuilder.h>
class DSCReqIndexBuilder : public IDCReqInputIndexBuilder
{
public:
    virtual DCIndex index(const DCIndex &index) const override
    {
        DCIndex reqIndex = index;
        reqIndex.roundIndex--;
        return reqIndex;
    }
};
#endif // DSCREQINDEXBUILDER_H
