#ifndef DCINDEXBUILDER_H
#define DCINDEXBUILDER_H
#include "ModelsContext/ModelsSLAs/imodel.h"
#include <DartsModelsContext/IndexesSLAs/idcindexbuilder.h>
#include "DartsModelsContext/IndexesDbServices/dartsindex.h"
class DCIndexBuilder : public IDCIndexBuilder
{
public:
    IDartsIndex *index() const override
    {
        auto model = new DartsIndex;
        model->setRoundIndex(1);
        return model;
    }
    IDartsIndex *index(IDartsIndex *other) const override
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
