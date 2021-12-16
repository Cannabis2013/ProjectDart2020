#ifndef DARTSIDXBUILDER_H
#define DARTSIDXBUILDER_H
#include "DartsModelsContext//TournamentModels/tnmvalues.h"
#include "DartsModelsContext/IndexesDbServices/dartsindex.h"
#include <DartsModelsContext/IndexesSLAs/idartsidxbuilder.h>
class DartsIdxBuilder : public IDartsIdxBuilder<IDartsIndex,TnmVals>
{
public:
    virtual Index *create(const Functor &vals) const override
    {
        auto idx = new DartsIndex;
        idx->setTotalTurns(vals.totalTurns);
        idx->setTurnIndex(vals.turnIndex);
        idx->setRoundIndex(vals.roundIndex);
        idx->setSetIndex(vals.setIndex);
        idx->setAttemptIndex(vals.attemptIndex);
        return idx;
    }
};
#endif // DARTSIDXBUILDER_H
