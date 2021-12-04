#ifndef DSCCALCSCORE_H
#define DSCCALCSCORE_H
#include "DartsController/DCScoresSLAs/absdccalcscore.h"
class DSCCalcScore : public AbsDCCalcScore
{
public:
    DSCCalcScore(AbsDCIdxCtrl *indexController, AbsDCPlayersCtx *scoresContext):
    AbsDCCalcScore(indexController,scoresContext){}
    virtual int calc(DCInput &inputModel) const override
    {
        return inputModel.score;
    }
    virtual int calc(const int &scoreCandidate) const override
    {
        auto index = idxCtrl()->index();
        auto scoreModel = scoresContext()->players().at(index.setIndex);
        return calcCandidate(scoreModel,scoreCandidate);
    }
private:
    int calcCandidate(const DCPlayer scoreModel, const int &scoreCandidate) const
    {
        auto score = scoreModel.remScore;
        auto totalScoreCandidate = score - scoreCandidate;
        if(totalScoreCandidate < 0)
            return score;
        return totalScoreCandidate;
    }
};
#endif // GETSCOREFROMDSCINPUT_H
