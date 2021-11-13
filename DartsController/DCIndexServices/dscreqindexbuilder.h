#ifndef DSCREQINDEXBUILDER_H
#define DSCREQINDEXBUILDER_H
#include <DartsController/DCIndexSLAs/idcreqinputindexbuilder.h>
#include "DartsModelsContext/IndexesDbServices/dartsindex.h"
class DSCReqIndexBuilder : public IDCReqInputIndexBuilder
{
public:
    virtual IDartsIndex *index(IDartsIndex *index, const IDCIndexBuilder *indexBuilder) const override
    {
        auto reqIndex = indexBuilder->index(index);
        reqIndex->setRoundIndex(index->roundIndex() - 1);
        return reqIndex;
    }
};
#endif // DSCREQINDEXBUILDER_H
