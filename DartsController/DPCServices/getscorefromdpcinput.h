#ifndef GETSCOREFROMDPCINPUT_H
#define GETSCOREFROMDPCINPUT_H
#include "DartsController/DCScoresSLAs/idccalcscore.h"
class GetScoreFromDPCInput : public IDCCalcScore
{
public:
    enum PointKeyCodes{
        SingleModifer = 0x2A,
        DoubleModifier = 0x2B,
        TrippleModifier = 0x2C,
        BullModifier,
        BullsEyeModifier
    };
    virtual int calc(DCIptVals &input) const override
    {
        auto multiplier = createPointMultiplier(input.modKeyCode);
        return calculateScore(input.point,multiplier);
    }
    virtual int calc(const DCIndex &idx, const int &scoreCandidate, AbstractDCScoresCtx *scoresService) const override
    {
        auto scoreModel = this->scoreModel(idx.setIndex,scoresService);
        return calcCandidate(scoreModel,scoreCandidate);
    }
private:
    int createPointMultiplier(const int &code) const
    {
        auto pointMultiplier = code == PointKeyCodes::TrippleModifier ? 3 :
                               code == PointKeyCodes::DoubleModifier ? 2 :
                               code == PointKeyCodes::SingleModifer ? 1 : 0;
        return pointMultiplier;
    }
    int calculateScore(const int &point, const int &multiplier) const
    {
        return point*multiplier;
    }
    DCScoreModel scoreModel(const int &modelIndex, AbstractDCScoresCtx *scoresService) const
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
#endif // POINTSCORECALCULATOR_H
