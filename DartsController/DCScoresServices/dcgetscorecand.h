#ifndef DCGETSCORECAND_H
#define DCGETSCORECAND_H
#include "DartsController/DCScoresSLAs/idcgetscorecand.h"
class DCGetScoreCand : public IDCGetScoreCand
{
public:
    virtual int scoreCandidate(const int &modelIndex, const int &scoreCandidate, IDCScoresService *scoresService) const override
    {
        auto tuple = getPlayerTupleByIndex(modelIndex,scoresService);
        return calcCandidate(tuple,scoreCandidate);
    }
private:
    DCContext::DCScoreModel getPlayerTupleByIndex(const int &modelIndex, IDCScoresService *scoresService) const
    {
        auto tuples = scoresService->scoreModels();
        return tuples.at(modelIndex);
    }
    int calcCandidate(const DCContext::DCScoreModel tuple, const int &scoreCandidate) const
    {
        auto score = tuple.totalScore;
        auto totalScoreCandidate = score - scoreCandidate;
        if(totalScoreCandidate < 0)
            return score;
        return totalScoreCandidate;
    }
};
#endif // DSCSCORECANDIDATESERVICE_H
