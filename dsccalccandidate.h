#ifndef DSCCALCCANDIDATE_H
#define DSCCALCCANDIDATE_H

#include "idsccalccandidate.h"

class DSCCalcCandidate : public IDSCCalcCandidate
{
public:
    virtual int scoreCandidate(const int &modelIndex, const int &scoreCandidate, IDCScoresService *scoresService) const override
    {
        auto tuple = getPlayerTupleByIndex(modelIndex,scoresService);
        return calcCandidate(tuple,scoreCandidate);
    }
private:
    DCContext::DCPTuple getPlayerTupleByIndex(const int &modelIndex, IDCScoresService *scoresService) const
    {
        auto tuples = scoresService->tuples();
        return tuples.at(modelIndex);
    }
    int calcCandidate(const DCContext::DCPTuple tuple, const int &scoreCandidate) const
    {
        auto score = tuple.totalScore;
        auto totalScoreCandidate = score - scoreCandidate;
        if(totalScoreCandidate < 0)
            return score;
        return totalScoreCandidate;
    }
};


#endif // DSCSCORECANDIDATESERVICE_H
