#ifndef DCGETSCORECAND_H
#define DCGETSCORECAND_H
#include "DartsController/DCScoresSLAs/idcgetscorecand.h"
class DCGetScoreCand : public IDCGetScoreCand
{
public:
    virtual int calc(const DCIndex &index, const int &scoreCandidate, IDCScoreModels *scoresService) const override
    {
        auto scoreModel = this->scoreModel(index.setIndex,scoresService);
        return calcCandidate(scoreModel,scoreCandidate);
    }
private:
    DCScoreModel scoreModel(const int &modelIndex, IDCScoreModels *scoresService) const
    {
        auto scoreModels = scoresService->scores();
        return scoreModels.at(modelIndex);
    }
    int calcCandidate(const DCScoreModel scoreModel, const int &scoreCandidate) const
    {
        auto score = scoreModel.remainingScore;
        auto totalScoreCandidate = score - scoreCandidate;
        if(totalScoreCandidate < 0)
            return score;
        return totalScoreCandidate;
    }
};
#endif // DSCSCORECANDIDATESERVICE_H
