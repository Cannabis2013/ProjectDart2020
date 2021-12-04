#ifndef GETSCOREFROMDPCINPUT_H
#define GETSCOREFROMDPCINPUT_H
#include "DartsController/DCScoresSLAs/absdccalcscore.h"
class GetScoreFromDPCInput : public AbsDCCalcScore
{
public:
    enum PointKeyCodes{
        SingleModifer = 0x2A,
        DoubleModifier = 0x2B,
        TrippleModifier = 0x2C,
        BullModifier,
        BullsEyeModifier
    };
    GetScoreFromDPCInput(AbsDCIdxCtrl *indexController, AbsDCPlayersCtx *scoresContext):
    AbsDCCalcScore(indexController,scoresContext){}
    virtual int calc(DCInput &input) const override
    {
        auto multiplier = createPointMultiplier(input.modKeyCode);
        return calculateScore(input.point,multiplier);
    }
    virtual int calc(const int &scoreCandidate) const override
    {
        auto setIndex = idxCtrl()->index().setIndex;
        auto scoreModel = scoresContext()->players().at(setIndex);
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
    DCPlayer scoreModel(const int &modelIndex) const
    {
        auto scoreModels = scoresContext()->players();
        return scoreModels.at(modelIndex);
    }
    int calcCandidate(const DCPlayer scoreModel, const int &scoreCandidate) const
    {
        auto score = scoreModel.remScore;
        auto totalScoreCandidate = score - scoreCandidate;
        if(totalScoreCandidate < 0)
            return score;
        return totalScoreCandidate;
    }
};
#endif // POINTSCORECALCULATOR_H
