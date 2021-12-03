#ifndef GETSCOREFROMDSCINPUT_H
#define GETSCOREFROMDSCINPUT_H
#include "DartsController/DCScoresSLAs/idccalcscore.h"
class GetScoreFromDSCInput : public IDCCalcScore
{
public:
    virtual int calc(DCIptVals &inputModel) const override
    {
        return inputModel.score;
    }
    virtual int calc(const DCIndex &index, const int &scoreCandidate, AbstractDCScoresCtx *scoresService) const override
    {
        auto scoreModel = getScoreModel(index.setIndex,scoresService);
        return calcCandidate(scoreModel,scoreCandidate);
    }
private:
    DCScoreModel getScoreModel(const int &modelIndex, AbstractDCScoresCtx *scoresService) const
    {
        auto scoreModels = scoresService->scores();
        return scoreModels.at(modelIndex);
    }
    int calcCandidate(const DCScoreModel scoreModel, const int &scoreCandidate) const
    {
        auto score = scoreModel.remScore;
        auto totalScoreCandidate = score - scoreCandidate;
        if(totalScoreCandidate < 0)
            return score;
        return totalScoreCandidate;
    }
};
#endif // GETSCOREFROMDSCINPUT_H
