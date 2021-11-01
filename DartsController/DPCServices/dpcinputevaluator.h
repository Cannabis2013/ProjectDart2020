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
    static DPCInputEvaluator* createInstance()
    {
        return new DPCInputEvaluator;
    }
    virtual void evaluateInput(DCInput input, IDCMetaInfo *metaInfo, AbstractDartsController *controller,
                               const IDartsStatusCodes *statusCodes, IDCPlayerController *playerController) override
    {
        if(!playerController->status(input.playerId))
        {
            if(input.modKeyCode == DoubleModifier)
            {
                input.remainingScore = input.remainingScoreCand;
                input.inGame = playerController->updatePlayerStatus(input.playerId,true);
            }
            else
            {
                input.score = 0;
                controller->persistInput(input);
                return;
            }
        }
        if(input.remainingScoreCand >= minimumAllowedScore)
        {
            input.remainingScore = input.remainingScoreCand;
            controller->persistInput(input);
        }
        else if(input.remainingScoreCand == 0 && (input.modKeyCode == DoubleModifier || input.score == _bullsEye))
        {
            input.remainingScore = 0;
            metaInfo->get().winnerId = input.playerId;
            metaInfo->get().winnerName = input.playerName;
            metaInfo->get().status = statusCodes->winnerFound();
            controller->persistInput(input);
        }
        else
        {
            input.score = 0;
            controller->persistInput(input);
            return;
        }
    }
private:
    const int _bullsEye = 50;
    const int minimumAllowedScore = 2;
};
#endif // POINTVALIDATOR_H
