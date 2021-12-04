#ifndef DPCINPUTVALIDATOR_H
#define DPCINPUTVALIDATOR_H
#include "DartsController/DCInputSLAs/abstractdcinputevaluator.h"
class DPCInputEvaluator : public AbstractDCInputEvaluator
{
    Q_OBJECT
public:
    enum KeyMappings{
        SingleModifer = 0x2A,
        DoubleModifier = 0x2B,
        TrippleModifier = 0x2C
    };
    DPCInputEvaluator(IDCMetaContext *metaInfo, AbsDCPlayersCtx *plaScoresCtx):
        AbstractDCInputEvaluator(metaInfo,plaScoresCtx){}
    void evaluate(DCInput &input, const int &scoreCand) override
    {
        if(!plaScoresCtx()->status(input.playerName))
        {
            if(input.modKeyCode == DoubleModifier)
            {
                input.remScore = scoreCand;
                input.inGame = true;
            }
            else
            {
                input.score = 0;
            }
        }
        else if(scoreCand >= minimumAllowedScore)
        {
            input.remScore = scoreCand;
        }
        else if(scoreCand == 0 && (input.modKeyCode == DoubleModifier || input.score == _bullsEye))
        {
            input.remScore = 0;
            metaInfo()->get().winnerName = input.playerName;
            metaInfo()->get().status = metaInfo()->WinnerDeclared;
        }
        else
        {
            input.score = 0;
        }
    }
private:
    const int _bullsEye = 50;
    const int minimumAllowedScore = 2;
};
#endif // POINTVALIDATOR_H
