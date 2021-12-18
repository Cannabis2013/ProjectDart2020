#include "dartsidxbuilder.h"
#include "IndexesDbServices/dartsindex.h"
#include "TournamentModels/tnmvalues.h"
#include "IndexesDbSLAs/idartsindex.h"
DartsIdxBuilder::Index *DartsIdxBuilder::create(const Functor &vals) const
{
    auto idx = new DartsIndex;
    idx->setTotalTurns(vals.totalTurns);
    idx->setTurnIndex(vals.turnIndex);
    idx->setRoundIndex(vals.roundIndex);
    idx->setSetIndex(vals.setIndex);
    idx->setAttemptIndex(vals.attemptIndex);
    return idx;
}
