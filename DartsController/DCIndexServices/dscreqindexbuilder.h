#ifndef DSCREQINDEXBUILDER_H
#define DSCREQINDEXBUILDER_H
#include <DartsController/DCIndexSLAs/abstractdcreqindexbuilder.h>
#include "DartsModelsContext/IndexesDbServices/dartsindex.h"
class DSCReqIndexBuilder : public AbstractDCReqIndexBuilder
{
public:
    DSCReqIndexBuilder(AbstractDCIdxCtrl *indexCtrl, IDCIdxBuilder *indexBuilder)
    {
        setIndexCtrl(indexCtrl);
        setIndexBuilder(indexBuilder);
    }
    virtual IDartsIndex *prevIndex() const override
    {
        auto index = indexCtrl()->index();
        auto reqIndex = indexBuilder()->index(index);
        reqIndex->setRoundIndex(index->roundIndex() - 1);
        return reqIndex;
    }
};
#endif // DSCREQINDEXBUILDER_H
