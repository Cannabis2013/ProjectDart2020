#ifndef DCINDEXBUILDER_H
#define DCINDEXBUILDER_H
#include "ModelsContext/ModelsSLAs/imodel.h"
#include <DartsModelsContext/IndexesSLAs/idcidxbuilder.h>
#include "DartsModelsContext/IndexesDbServices/dartsindex.h"
class DCIndexBuilder : public IDCIdxBuilder
{
public:
    IDartsIndex *index() const override
    {
        return createDefaultIndex();
    }
    IDartsIndex *index(IDartsIndex *other) const override
    {
        if(other == nullptr)
            return createDefaultIndex();
        return copyIndex(other);
    }
private:
    IDartsIndex *createDefaultIndex() const
    {
        auto model = new DartsIndex;
        model->setRoundIndex(1);
        return model;
    }
    IDartsIndex *copyIndex(IDartsIndex *other) const
    {
        auto index = new DartsIndex;
        index->setTotalTurns(other->totalTurns());
        index->setTurnIndex(other->turnIndex());
        index->setRoundIndex(other->roundIndex());
        index->setSetIndex(other->setIndex());
        index->setAttemptIndex(other->attemptIndex());
        return index;
    }
};
#endif // DARTSINDEXESBUILDER_H
