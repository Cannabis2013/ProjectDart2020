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
    void evaluate(AbstractDartsInput *input, const int &scoreCand, IDCMetaCtx *metaInfo, AbstractDartsController *controller,
                  const IDartsStatusCodes *statusCodes, IDCPlayerCtx *playerController) override
    {
        if(!playerController->status(input->playerId()))
        {
            if(input->modKeyCode() == DoubleModifier)
            {
                input->setRemainingScore(scoreCand);
                input->setInGame(true);
                controller->addInputToModelsContext(input);
                return;
            }
            else
            {
                input->setScore(0);
                controller->addInputToModelsContext(input);
                return;
            }
        }
        if(scoreCand >= minimumAllowedScore)
        {
            input->setRemainingScore(scoreCand);
            controller->addInputToModelsContext(input);
        }
        else if(scoreCand == 0 && (input->modKeyCode() == DoubleModifier || input->score() == _bullsEye))
        {
            input->setRemainingScore(0);
            metaInfo->get().winnerId = input->playerId();
            metaInfo->get().winnerName = input->playerName();
            metaInfo->get().status = statusCodes->winnerFound();
            controller->addInputToModelsContext(input);
        }
        else
        {
            input->setScore(0);
            controller->addInputToModelsContext(input);
            return;
        }
    }
private:
    const int _bullsEye = 50;
    const int minimumAllowedScore = 2;
};
#endif // POINTVALIDATOR_H
